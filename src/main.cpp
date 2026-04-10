#include <Geode/Geode.hpp>
#include <Geode/modify/PauseLayer.hpp>

using namespace geode::prelude;

class $modify(MyPauseLayer, PauseLayer) {
    
    void onToggleTwoPlayer(CCObject* sender) {
        auto levelSettings = PlayLayer::get()->m_levelSettings;
        
        // Alternamos el valor
        levelSettings->m_twoPlayerMode = !levelSettings->m_twoPlayerMode;

        // Actualizamos el texto del botón para que el usuario vea el cambio
        auto btn = static_cast<ButtonSprite*>(static_cast<CCMenuItemSpriteExtra*>(sender)->getNormalImage());
        std::string label = levelSettings->m_twoPlayerMode ? "2 Player: [X]" : "2 Player: [ ]";
        btn->setString(label.c_str());
        
        // Mensaje rápido en pantalla
        Notification::create(
            levelSettings->m_twoPlayerMode ? "2 Player Mode Enabled" : "2 Player Mode Disabled",
            NotificationIcon::Info
        )->show();
    }

    bool init(bool unfocused) {
        if (!PauseLayer::init(unfocused)) return false;

        if (!Mod::get()->getSettingValue<bool>("show-button")) return true;

        auto levelSettings = PlayLayer::get()->m_levelSettings;

        // Texto dinámico dependiendo del estado actual
        std::string labelText = levelSettings->m_twoPlayerMode ? "2 Player: [X]" : "2 Player: [ ]";

        auto buttonSprite = ButtonSprite::create(labelText.c_str(), "goldFont.fnt", "GJ_button_04.png", 0.6f);
        
        auto myButton = CCMenuItemSpriteExtra::create(
            buttonSprite,
            this,
            menu_selector(MyPauseLayer::onToggleTwoPlayer)
        );
        myButton->setID("two-player-toggle"_spr);

        if (auto leftMenu = this->getChildByID("left-button-menu")) {
            leftMenu->addChild(myButton);
            leftMenu->updateLayout();
        }

        return true;
    }
};
