#include "SettingsMenuLayer.h"

#include "Constants.h"
#include "GameLayer.h"
#include "SimpleAudioEngine.h"

using namespace cocos2d;

Vec2 normalizedPosition = Vec2(0.5, 0.1);

bool SettingsMenuLayer::init()
{
    if ( !LayerColor::initWithColor(Color4B(0, 0, 0, 0)) ) {
        return false;
    }

    _origin = Director::getInstance()->getVisibleOrigin();
    _visibleSize = Director::getInstance()->getVisibleSize();
    _isCollapsed = true;    // start with collupsed menus

    // set SettingsHUD's size and position
    this->setContentSize(Size(_visibleSize.width * 0.08, _visibleSize.height));
    this->setPosition(0, 0);
    
    addSettingsAndAllSubMenues();
    
    return true;
}

void SettingsMenuLayer::addSettingsAndAllSubMenues() {
    // add settings toggle button
    auto settings = MenuItemImage::create(imageBtnSettings, imageBtnSettingsClicked, CC_CALLBACK_1(SettingsMenuLayer::settingsClicked, this));
    _settingsMenu = Menu::create(settings, nullptr);
    _settingsMenu->setNormalizedPosition(normalizedPosition);
    this->addChild(_settingsMenu, BackgroundLayer::layerTouch);
    
    
    // add sound button
    float currentSoundSettings = UserDefault::getInstance()->getFloatForKey(VOLUME, 1.0f);
    MenuItem* mute = MenuItemImage::create("btn_mute.png", "btn_mute.png");
    MenuItem* unmute = MenuItemImage::create("btn_unmute.png", "btn_unmute.png");
    MenuItemToggle* muteToggleItem = MenuItemToggle::createWithCallback(CC_CALLBACK_1(SettingsMenuLayer::toggleSound, this), mute, unmute, NULL);
    muteToggleItem->setSelectedIndex(currentSoundSettings);
    _muteToggleMenu = Menu::create(muteToggleItem, NULL);
    _muteToggleMenu->setNormalizedPosition(Vec2(normalizedPosition.x, normalizedPosition.y + (settings->getContentSize().height / _visibleSize.height)));
    _muteToggleMenu->setVisible(false);  // make it invisible in the beginning
    
    
    this->addChild(_muteToggleMenu, BackgroundLayer::layerTouch);
    CocosDenshion::SimpleAudioEngine::getInstance()->setEffectsVolume(currentSoundSettings);
}

void SettingsMenuLayer::settingsClicked(Ref* ref) {
    _muteToggleMenu->setVisible(_isCollapsed);
    _isCollapsed = not _isCollapsed;
}

void SettingsMenuLayer::toggleSound(Ref* ref) {
    CocosDenshion::SimpleAudioEngine* audioEngine = CocosDenshion::SimpleAudioEngine::getInstance();
    
    audioEngine->setEffectsVolume(not audioEngine->getEffectsVolume());
    UserDefault::getInstance()->setFloatForKey(VOLUME, audioEngine->getEffectsVolume());
}



