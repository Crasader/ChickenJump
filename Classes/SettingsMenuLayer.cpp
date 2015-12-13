#include "SettingsMenuLayer.h"

#include "Constants.h"
#include "GameLayer.h"
#include "SimpleAudioEngine.h"

using namespace cocos2d;

const std::string imageBtnSettings = "btn_settings.png";
const std::string imageBtnSettingsClicked = "btn_settingsclicked.png";
const std::string imageBtnMute = "btn_mute.png";
const std::string imageBtnUnMute = "btn_unmute.png";
const std::string imageBtnMuteMusic = "btn_mute_music.png";
const std::string imageBtnUnMuteMusic = "btn_unmute_music.png";

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
    
    
    // add sound toggle button
    float currentSoundSettings = UserDefault::getInstance()->getFloatForKey(SOUND, 1.0f);
    MenuItem* mute = MenuItemImage::create(imageBtnMute, imageBtnMute);
    MenuItem* unmute = MenuItemImage::create(imageBtnUnMute, imageBtnUnMute);
    MenuItemToggle* muteToggleItem = MenuItemToggle::createWithCallback(CC_CALLBACK_1(SettingsMenuLayer::toggleSound, this), mute, unmute, NULL);
    muteToggleItem->setSelectedIndex(currentSoundSettings);
    _soundToggleMenu = Menu::create(muteToggleItem, NULL);
    _soundToggleMenu->setNormalizedPosition(Vec2(normalizedPosition.x, normalizedPosition.y + (settings->getContentSize().height / _visibleSize.height)));
    _soundToggleMenu->setVisible(false);  // make it invisible in the beginning
    
    
    this->addChild(_soundToggleMenu, BackgroundLayer::layerTouch);
    CocosDenshion::SimpleAudioEngine::getInstance()->setEffectsVolume(currentSoundSettings);
}

void SettingsMenuLayer::settingsClicked(Ref* ref) {
    _soundToggleMenu->setVisible(_isCollapsed);
    _isCollapsed = not _isCollapsed;
}

void SettingsMenuLayer::toggleSound(Ref* ref) {
    CocosDenshion::SimpleAudioEngine* audioEngine = CocosDenshion::SimpleAudioEngine::getInstance();
    
    audioEngine->setEffectsVolume(not audioEngine->getEffectsVolume());
    UserDefault::getInstance()->setFloatForKey(SOUND, audioEngine->getEffectsVolume());
}

void SettingsMenuLayer::toggleMusic(Ref* ref) {
    CocosDenshion::SimpleAudioEngine* audioEngine = CocosDenshion::SimpleAudioEngine::getInstance();
    
    audioEngine->setEffectsVolume(not audioEngine->getEffectsVolume());
    UserDefault::getInstance()->setFloatForKey(SOUND, audioEngine->getEffectsVolume());
}



