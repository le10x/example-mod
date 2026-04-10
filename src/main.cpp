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
        
        // Corregimos la lógica: toggler->isToggled() devuelve el estado DESPUÉS del clic
        levelSettings->m_twoPlayerMode = !toggler->isToggled();
    }

    bool init(bool unfocused) {
        if (!PauseLayer::init(unfocused)) return false;

        auto levelSettings = PlayLayer::get()->m_levelSettings;
        auto leftMenu = this->getChildByID("left-button-menu");

        if (leftMenu) {
            // 1. Toggler (Check) - Aumentamos escala a 0.8f para que no sea tan pequeño
            auto toggler = CCMenuItemToggler::createWithStandardSprites(
                this,
                menu_selector(MyPauseLayer::onToggleTwoPlayer),
                0.8f
            );
            toggler->toggle(levelSettings->m_twoPlayerMode);
            toggler->setID("two-player-toggle"_spr);

            // 2. Texto "2P"
            auto label = CCLabelBMFont::create("2P", "bigFont.fnt");
            label->setScale(0.5f);

            // 3. Contenedor especializado (CCMenu) 
            // Usar CCMenu en lugar de CCNode hace que los clics funcionen siempre
            auto menuContainer = CCMenu::create();
            menuContainer->setLayout(RowLayout::create()->setGap(10.f)->setAutoScale(false));
            
            // Importante: Definir un tamaño para que el menú sea "cliqueable"
            menuContainer->setContentSize({80, 40});
            menuContainer->setPosition({0, 0}); // Se posicionará mediante el layout del padre

            menuContainer->addChild(toggler);
            menuContainer->addChild(label);
            menuContainer->updateLayout();

            leftMenu->addChild(menuContainer);
            leftMenu->updateLayout();
        }

        return true;
    }
};
