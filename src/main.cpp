#include <Geode/Geode.hpp>
#include <Geode/modify/PauseLayer.hpp>

using namespace geode::prelude;

class $modify(MyPauseLayer, PauseLayer) {
    bool init() {
        if (!PauseLayer::init()) return false;

        // Crear el botón con tu imagen
        auto buttonSprite = CCSprite::createWithSpriteFrameName("my_button.png");
        
        auto myButton = CCMenuItemSpriteExtra::create(
            buttonSprite,
            this,
            menu_selector(MyPauseLayer::onMyButtonClick)
        );

        // Intentar ponerlo en el menú de la izquierda
        if (auto leftMenu = this->getChildByID("left-button-menu")) {
            myButton->setID("hello-world-button"_spr);
            leftMenu->addChild(myButton);
            leftMenu->updateLayout(); 
        }

        return true;
    }

    void onMyButtonClick(CCObject* sender) {
        FLAlertLayer::create(
            "Prueba",           // Título
            "Hello World",      // Mensaje
            "OK"                // Botón
        )->show();
    }
};
