#include <Geode/Geode.hpp>
#include <Geode/modify/PauseLayer.hpp>
#include <Geode/modify/PlayLayer.hpp>

using namespace geode::prelude;

bool g_originalTwoPlayerState = false;

class $modify(MyPlayLayer, PlayLayer) {
    bool init(GJGameLevel* level, bool useReplay, bool dontSave) {
        if (!PlayLayer::init(level, useReplay, dontSave)) return false;
        g_originalTwoPlayerState = m_levelSettings->m_twoPlayerMode;
        return true;
    }

    void resetLevel() {
        PlayLayer::resetLevel();
        if (Mod::get()->getSettingValue<bool>("reset-on-death")) {
            m_levelSettings->m_twoPlayerMode = g_originalTwoPlayerState;
        }
    }

    void onQuit() {
        m_levelSettings->m_twoPlayerMode = g_originalTwoPlayerState;
        PlayLayer::onQuit();
    }
};

class $modify(MyPauseLayer, PauseLayer) {
    void onToggleTwoPlayer(CCObject* sender) {
        auto levelSettings = PlayLayer::get()->m_levelSettings;
        auto toggler = static_cast<CCMenuItemToggler*>(sender);
        levelSettings->m_twoPlayerMode = !toggler->isToggled();
    }

    bool init(bool unfocused) {
        if (!PauseLayer::init(unfocused)) return false;

        auto levelSettings = PlayLayer::get()->m_levelSettings;

        // Toggler reducido un 25% (de 0.9f a 0.67f aprox)
        auto toggler = CCMenuItemToggler::createWithStandardSprites(
            this,
            menu_selector(MyPauseLayer::onToggleTwoPlayer),
            0.67f 
        );
        toggler->toggle(levelSettings->m_twoPlayerMode);

        // Texto "2-Player Mode" reducido un 25% (de 0.4f a 0.3f)
        auto label = CCLabelBMFont::create("2-Player Mode", "bigFont.fnt");
        label->setScale(0.3f);
        label->setAnchorPoint({0, 0.5});
        label->setPosition({20, 0}); // Espacio después del check

        auto menu = CCMenu::create();
        menu->addChild(toggler);
        menu->addChild(label);
        
        // Movido 2mm (aprox +7 unidades) a la derecha y arriba: 
        // X: 35 -> 42 | Y: 30 -> 37
        menu->setPosition({42, 37});
        menu->setID("two-player-menu"_spr);

        this->addChild(menu);

        return true;
    }
};
