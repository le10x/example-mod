#include <Geode/Geode.hpp>
#include <Geode/modify/PauseLayer.hpp>

using namespace geode::prelude;

class $modify(MyPauseLayer, PauseLayer) {
    bool init() {
        if (!PauseLayer::init()) return false;

        // Creamos el sprite usando la imagen que subiste
        auto buttonSprite = CCSprite::createWithSpriteFrameName("my_button.png");
        
        // Si por alguna razón la imagen no carga, usamos una por defecto para que no crashee
        if (!buttonSprite) {
            buttonSprite = CCSprite::createWithSpriteFrameName("GJ_playBtn_001.png");
        }

        auto myButton = CCMenuItemSpriteExtra::create(
            buttonSprite,
            this,
            menu_selector(MyPauseLayer::onMyButtonClick)
        );

        // Agregamos el botón al menú izquierdo
        if (auto leftMenu = this->getChildByID("left-button-menu")) {
            myButton->setID("test-button-saludo"_spr);
            leftMenu->addChild(myButton);
            leftMenu->updateLayout();
        }

        return true;
    }

    void onMyButtonClick(CCObject* sender) {
        FLAlertLayer::create(
            "Prueba", 
            "Hello World", 
            "OK"
        )->show();
    }
};
