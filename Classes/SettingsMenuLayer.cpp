#include "SettingsMenuLayer.h"

#include <UIListView.h>
#include <UIButton.h>

#include "Constants.h"
#include "GameLayer.h"
#include "SoundManager.h"

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
    
    createMenues();
    
    return true;
}

void SettingsMenuLayer::createMenues() {
    ListView* lv = ListView::create();
    
    _btnSettings = Button::create(imageBtnSettings, "");
    if (not _btnSettings) { return; }
    
    _btnSettings->addTouchEventListener(CC_CALLBACK_2(SettingsMenuLayer::settingsClicked, this));
    
    addSoundButton();
    addMusicButton();
    
    if (_btnMusicToggle) { lv->pushBackCustomItem(_btnMusicToggle); }
    if (_btnSoundToggle) { lv->pushBackCustomItem(_btnSoundToggle); }
    lv->pushBackCustomItem(_btnSettings);
    
    lv->setGravity(ui::ListView::Gravity::CENTER_HORIZONTAL);
    lv->setItemsMargin(10);
    lv->setSize(Size(_btnSettings->getContentSize().width,
                     _btnSettings->getContentSize().height * 3));
    
    // lv->setBackGroundColorType(ui::Layout::BackGroundColorType::SOLID);
    // lv->setBackGroundColor(Color3B::GREEN);
    lv->setNormalizedPosition(normalizedPosition);
    lv->setBounceEnabled(false);
    this->addChild(lv);
}

void SettingsMenuLayer::addSoundButton() {
    if (SoundManager::IsSoundActive()) {
        _btnSoundToggle = Button::create(imageBtnSoundOn, "");
    }
    else {
        _btnSoundToggle = Button::create(imageBtnSoundOff, "");
    }
    if (not _btnSoundToggle) { return; }
    _btnSoundToggle->addTouchEventListener(CC_CALLBACK_2(SettingsMenuLayer::toggleSound, this));
    _btnSoundToggle->setVisible(false);  // make it invisible at the beginning
}

void SettingsMenuLayer::addMusicButton() {
    if (SoundManager::IsMusicActive()) {
        _btnMusicToggle = Button::create(imageBtnMusicOn, "");
    }
    else {
        _btnMusicToggle = Button::create(imageBtnMusicOff, "");
    }
    if (not _btnMusicToggle) { return; }
    _btnMusicToggle->addTouchEventListener(CC_CALLBACK_2(SettingsMenuLayer::toggleMusic, this));
    _btnMusicToggle->setVisible(false);  // make it invisible at the beginning
}

void SettingsMenuLayer::settingsClicked(const Ref* ref, const ui::Widget::TouchEventType& eEventType) {
    if (eEventType != ui::Widget::TouchEventType::ENDED) { return; }

    if (_btnSoundToggle) { _btnSoundToggle->setVisible(_isCollapsed); }
    if (_btnMusicToggle) { _btnMusicToggle->setVisible(_isCollapsed); }
    _isCollapsed = not _isCollapsed;
}

void SettingsMenuLayer::toggleSound(const Ref* ref, const cocos2d::ui::Widget::TouchEventType& eEventType) {
    if (eEventType != ui::Widget::TouchEventType::ENDED) { return; }

    SoundManager::ToggleSound();
    if (SoundManager::IsSoundActive()) {
        _btnSoundToggle->loadTextures(imageBtnSoundOn, "");
    }
    else {
        _btnSoundToggle->loadTextures(imageBtnSoundOff, "");
    }
}

void SettingsMenuLayer::toggleMusic(const Ref* ref, const cocos2d::ui::Widget::TouchEventType& eEventType) {
    if (eEventType != ui::Widget::TouchEventType::ENDED) { return; }

    SoundManager::ToggleMusic();
    if (SoundManager::IsMusicActive()) {
        _btnMusicToggle->loadTextures(imageBtnMusicOn, "");
    }
    else {
        _btnMusicToggle->loadTextures(imageBtnMusicOff, "");
    }
}



