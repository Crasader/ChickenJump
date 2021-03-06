#include "SettingsMenuHUD.h"

#include <UIListView.h>
#include <UIButton.h>

#include "Constants.h"
#include "GameLayer.h"
#include "SoundManager.h"

using namespace cocos2d;
using namespace ui;

static const std::string imageBtnSettings = "btn_settings.png";
static const std::string imageBtnSettingsClicked = "btn_settingsclicked.png";
static const std::string imageBtnSoundOn = "btn_soundon.png";
static const std::string imageBtnSoundOff = "btn_soundoff.png";
static const std::string imageBtnMusicOn = "btn_musicon.png";
static const std::string imageBtnMusicOff = "btn_musicoff.png";

static Vec2 normalizedPosition = Vec2(0.1, 0.05);

static Button* _btnSettings;
static Button* _btnSoundToggle;
static Button* _btnMusicToggle;

bool SettingsMenuHUD::init()
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
    
    createMenues();
    
    return true;
}

void SettingsMenuHUD::createMenues() {
    ListView* lv = ListView::create();
    
    _btnSettings = Button::create(imageBtnSettings, imageBtnSettingsClicked);
    if (not _btnSettings) { return; }
    
    _btnSettings->addTouchEventListener(CC_CALLBACK_2(SettingsMenuHUD::settingsClicked, this));
    
    addSoundButton();
    addMusicButton();
    
    if (_btnMusicToggle) { lv->pushBackCustomItem(_btnMusicToggle); }
    if (_btnSoundToggle) { lv->pushBackCustomItem(_btnSoundToggle); }
    lv->pushBackCustomItem(_btnSettings);
    
    lv->setGravity(ui::ListView::Gravity::CENTER_HORIZONTAL);
    lv->setItemsMargin(10);
    lv->setSize(Size(_btnSettings->getContentSize().width,
                     _btnSettings->getContentSize().height * 3));
    
    lv->setNormalizedPosition(normalizedPosition);
    lv->setBounceEnabled(false);
    this->addChild(lv);
}

void SettingsMenuHUD::addSoundButton() {
    if (SoundManager::IsSoundActive()) {
        _btnSoundToggle = Button::create(imageBtnSoundOn, imageBtnSoundOn);
    }
    else {
        _btnSoundToggle = Button::create(imageBtnSoundOff, imageBtnSoundOff);
    }
    if (not _btnSoundToggle) { return; }
    _btnSoundToggle->addTouchEventListener(CC_CALLBACK_2(SettingsMenuHUD::toggleSound, this));
    _btnSoundToggle->setVisible(false);  // make it invisible at the beginning
}

void SettingsMenuHUD::addMusicButton() {
    if (SoundManager::IsMusicActive()) {
        _btnMusicToggle = Button::create(imageBtnMusicOn, imageBtnMusicOn);
    }
    else {
        _btnMusicToggle = Button::create(imageBtnMusicOff, imageBtnMusicOff);
    }
    if (not _btnMusicToggle) { return; }
    _btnMusicToggle->addTouchEventListener(CC_CALLBACK_2(SettingsMenuHUD::toggleMusic, this));
    _btnMusicToggle->setVisible(false);  // make it invisible at the beginning
}

void SettingsMenuHUD::settingsClicked(const Ref* ref, const ui::Widget::TouchEventType& eEventType) {
    if (eEventType != ui::Widget::TouchEventType::ENDED) { return; }

    if (_btnSoundToggle) { _btnSoundToggle->setVisible(_isCollapsed); }
    if (_btnMusicToggle) { _btnMusicToggle->setVisible(_isCollapsed); }
    _isCollapsed = not _isCollapsed;
}

void SettingsMenuHUD::toggleSound(const Ref* ref, const cocos2d::ui::Widget::TouchEventType& eEventType) {
    if (eEventType != ui::Widget::TouchEventType::ENDED) { return; }

    SoundManager::ToggleSound();
    if (SoundManager::IsSoundActive()) {
        _btnSoundToggle->loadTextures(imageBtnSoundOn, imageBtnSoundOn);
    }
    else {
        _btnSoundToggle->loadTextures(imageBtnSoundOff, imageBtnSoundOff);
    }
}

void SettingsMenuHUD::toggleMusic(const Ref* ref, const cocos2d::ui::Widget::TouchEventType& eEventType) {
    if (eEventType != ui::Widget::TouchEventType::ENDED) { return; }

    SoundManager::ToggleMusic(SoundManager::menuMusic);
    if (SoundManager::IsMusicActive()) {
        _btnMusicToggle->loadTextures(imageBtnMusicOn, imageBtnMusicOn);
    }
    else {
        _btnMusicToggle->loadTextures(imageBtnMusicOff, imageBtnMusicOff);
    }
}



