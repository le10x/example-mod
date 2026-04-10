#include <Geode/Geode.hpp>
#include <Geode/modify/PauseLayer.hpp>

using namespace geode::prelude;

class $modify(MyPauseLayer, PauseLayer) {
    // La función debe estar dentro de la clase modificada para usar menu_selector
    void onMyButtonClick(CCObject* sender) {
        FLAlertLayer::create("Geode", "Hello", "OK")->show();
    }

    bool init() override {
        if (!PauseLayer::init()) return false;

        auto buttonSprite = CCSprite::createWithSpriteFrameName("GJ_playBtn_001.png");
        buttonSprite->setScale(0.5f);
        
        // El tercer parámetro debe referenciar a la función de la clase
        auto myButton = CCMenuItemSpriteExtra::create(
            buttonSprite,
            this,
            menu_selector(MyPauseLayer::onMyButtonClick)
        );
    
        if (auto leftMenu = this->getChildByID("left-button-menu")) {
            myButton->setID("test-button"_spr);
            leftMenu->addChild(myButton);
            leftMenu->updateLayout(); 
        }

        return true;
    }
};
