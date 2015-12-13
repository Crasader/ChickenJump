#include "SettingsMenuLayer.h"

#include "Constants.h"
#include "GameLayer.h"
#include "SoundManager.h"

using namespace cocos2d;

const std::string imageBtnSettings = "btn_settings.png";
const std::string imageBtnSettingsClicked = "btn_settingsclicked.png";
const std::string imageBtnMute = "btn_soundoff.png";
const std::string imageBtnUnMute = "btn_soundon.png";
const std::string imageBtnMuteMusic = "btn_musicoff.png";
const std::string imageBtnUnMuteMusic = "btn_musicon.png";

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
    MenuItem* soundOff = MenuItemImage::create(imageBtnMute, imageBtnMute);
    MenuItem* soundOn = MenuItemImage::create(imageBtnUnMute, imageBtnUnMute);
    MenuItemToggle* muteToggleItem = MenuItemToggle::createWithCallback(CC_CALLBACK_1(SettingsMenuLayer::toggleSound, this), soundOff, soundOn, NULL);
    muteToggleItem->setSelectedIndex(currentSoundSettings);
    _soundToggleMenu = Menu::create(muteToggleItem, NULL);
    _soundToggleMenu->setNormalizedPosition(Vec2(normalizedPosition.x, normalizedPosition.y + (settings->getContentSize().height / _visibleSize.height)));
    _soundToggleMenu->setVisible(false);  // make it invisible in the beginning
    
    this->addChild(_soundToggleMenu, BackgroundLayer::layerTouch);
    
    // add background music toggle button
    float currentMusicSettings = UserDefault::getInstance()->getFloatForKey(MUSIC, 1.0f);
    MenuItem* musicOff = MenuItemImage::create(imageBtnMuteMusic, imageBtnMuteMusic);
    MenuItem* musicOn = MenuItemImage::create(imageBtnUnMuteMusic, imageBtnUnMuteMusic);
    MenuItemToggle* muteMusicToggleItem = MenuItemToggle::createWithCallback(CC_CALLBACK_1(SettingsMenuLayer::toggleMusic, this), musicOff, musicOn, NULL);
    muteMusicToggleItem->setSelectedIndex(currentMusicSettings);
    _musicToggleMenu = Menu::create(muteMusicToggleItem, NULL);
    _musicToggleMenu->setNormalizedPosition(Vec2(normalizedPosition.x, normalizedPosition.y + (settings->getContentSize().height / _visibleSize.height) * 2.5));
    _musicToggleMenu->setVisible(false);  // make it invisible in the beginning
    
    this->addChild(_musicToggleMenu, BackgroundLayer::layerTouch);
}

void SettingsMenuLayer::settingsClicked(Ref* ref) {
    if (_soundToggleMenu) { _soundToggleMenu->setVisible(_isCollapsed); }
    if (_musicToggleMenu) { _musicToggleMenu->setVisible(_isCollapsed); }
    _isCollapsed = not _isCollapsed;
}

void SettingsMenuLayer::toggleSound(Ref* ref) {
    SoundManager::ToggleSound();
}

void SettingsMenuLayer::toggleMusic(Ref* ref) {
    SoundManager::ToggleMusic();
}



