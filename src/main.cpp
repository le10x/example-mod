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
        // En Geode, isToggled() cambia después del clic, así que invertimos la lógica
        levelSettings->m_twoPlayerMode = !toggler->isToggled();
    }

    bool init(bool unfocused) {
        if (!PauseLayer::init(unfocused)) return false;

        auto levelSettings = PlayLayer::get()->m_levelSettings;
        auto leftMenu = this->getChildByID("left-button-menu");

        if (leftMenu) {
            // Contenedor para el check y el texto
            auto container = CCNode::create();
            container->setLayout(RowLayout::create()->setGap(5.f)); // Espacio entre check y texto
            container->setContentSize({60, 30});

            // Toggler (Check)
            auto toggler = CCMenuItemToggler::createWithStandardSprites(
                this,
                menu_selector(MyPauseLayer::onToggleTwoPlayer),
                0.7f
            );
            toggler->toggle(levelSettings->m_twoPlayerMode);
            toggler->setID("two-player-toggle"_spr);

            // Texto "2P"
            auto label = CCLabelBMFont::create("2P", "bigFont.fnt");
            label->setScale(0.4f);

            container->addChild(toggler);
            container->addChild(label);
            container->updateLayout();

            leftMenu->addChild(container);
            leftMenu->updateLayout();
        }

        return true;
    }
};
