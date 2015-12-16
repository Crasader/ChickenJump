#include "PauseLayer.h"

#include <UIListView.h>
#include <UIButton.h>

#include "GameLayer.h"
#include "BackButton.h"
#include "MainMenuLayer.h"
#include "SoundManager.h"

using namespace cocos2d;
using namespace cocos2d::ui;

static const std::string imageBtnMenu = "btn_menu.png";
static const std::string imageBtnResume = "btn_resume.png";
static const std::string imageBtnRestart = "btn_restart.png";
static const std::string imageBtnSoundOn = "btn_soundon_big.png";
static const std::string imageBtnSoundOff = "btn_soundoff_big.png";
static const std::string imageBtnMusicOn = "btn_musicon_big.png";
static const std::string imageBtnMusicOff = "btn_musicoff_big.png";

//static Vec2 normalizedPosition = Vec2(0.01, 0.1);

static Button* _btnResume;
static Button* _btnRestart;
static Button* _btnMenu;
static Button* _btnSoundToggle;
static Button* _btnMusicToggle;

bool PauseLayer::init()
{
    if ( !LayerColor::initWithColor(Color4B(0, 0, 0, 128)) ) {
        return false;
    }

    _origin = Director::getInstance()->getVisibleOrigin();
    _visibleSize = Director::getInstance()->getVisibleSize();

    this->setContentSize(Size(_visibleSize.width, _visibleSize.height));
    this->setPosition(0, 0);
    
    createMenus();
    createAdLayout();

    return true;
}

void PauseLayer::createMenus() {
    ListView* lv = ListView::create();
    
    addResumeButton();
    addRestartButton();
    addMenuButton();
    addSoundButton();
    addMusicButton();
    
    if (_btnResume) { lv->pushBackCustomItem(_btnResume); }
    if (_btnRestart) { lv->pushBackCustomItem(_btnRestart); }
    if (_btnMenu) { lv->pushBackCustomItem(_btnMenu); }
    if (_btnMusicToggle) { lv->pushBackCustomItem(_btnMusicToggle); }
    if (_btnSoundToggle) { lv->pushBackCustomItem(_btnSoundToggle); }
    
    lv->setGravity(ui::ListView::Gravity::CENTER_HORIZONTAL);
    lv->setItemsMargin(10);
    lv->setSize(Size(_btnMenu->getContentSize().width,
                     _btnMenu->getContentSize().height * 5 + 40)); // including margin gap (10*4)
    // lv->setBackGroundColorType(ui::Layout::BackGroundColorType::SOLID);
    // lv->setBackGroundColor(Color3B(128, 128, 128));
    lv->setPosition(Size(_visibleSize.width * 0.01,
                         (_visibleSize.height - lv->getContentSize().height) * 0.5));
    lv->setBounceEnabled(false);
    this->addChild(lv);
}

void PauseLayer::createAdLayout() {
    Layout* l = Layout::create();
    l->setContentSize(Size(_visibleSize.width * 0.75, _visibleSize.height * 0.75));
    l->setPosition(Vec2((_visibleSize.width - l->getContentSize().width) * 0.5,
                        (_visibleSize.height - l->getContentSize().height) * 0.5));
    l->setBackGroundColorType(cocos2d::ui::Layout::BackGroundColorType::SOLID);
    l->setBackGroundColor(Color3B::GRAY);
    l->setBackGroundColorOpacity(128);

    this->addChild(l);
}

void PauseLayer::addResumeButton() {
    _btnResume = Button::create(imageBtnResume, imageBtnResume);
    if (not _btnResume) { return; }
    
    _btnResume->addTouchEventListener(CC_CALLBACK_1(GameLayer::resumeClicked, GameLayer::getInstance()));
}

void PauseLayer::addRestartButton() {
    _btnRestart = Button::create(imageBtnRestart, imageBtnRestart);
    if (not _btnRestart) { return; }

    _btnRestart->addTouchEventListener(CC_CALLBACK_2(PauseLayer::restartClicked, this));
}

void PauseLayer::addMenuButton() {
    _btnMenu = Button::create(imageBtnMenu, imageBtnMenu);
    if (not _btnMenu) { return; }
    _btnMenu->addTouchEventListener(CC_CALLBACK_2(PauseLayer::menuClicked, this));
}

void PauseLayer::addSoundButton() {
    if (SoundManager::IsSoundActive()) {
        _btnSoundToggle = Button::create(imageBtnSoundOn, imageBtnSoundOn);
    }
    else {
        _btnSoundToggle = Button::create(imageBtnSoundOff, imageBtnSoundOff);
    }
    if (not _btnSoundToggle) { return; }
    _btnSoundToggle->addTouchEventListener(CC_CALLBACK_2(PauseLayer::toggleSound, this));
}

void PauseLayer::addMusicButton() {
    if (SoundManager::IsMusicActive()) {
        _btnMusicToggle = Button::create(imageBtnMusicOn, imageBtnMusicOn);
    }
    else {
        _btnMusicToggle = Button::create(imageBtnMusicOff, imageBtnMusicOff);
    }
    if (not _btnMusicToggle) { return; }
    _btnMusicToggle->addTouchEventListener(CC_CALLBACK_2(PauseLayer::toggleMusic, this));
}

// Click Events
void PauseLayer::menuClicked(const Ref* ref, const cocos2d::ui::Widget::TouchEventType& eEventType) {
    if (eEventType != ui::Widget::TouchEventType::ENDED) { return; }
    
    BackButton<MainMenuLayer>* mainMenu = new BackButton<MainMenuLayer>();
    if (not mainMenu) { return; }
    mainMenu->goBack(this);
}

void PauseLayer::restartClicked(const Ref* ref, const cocos2d::ui::Widget::TouchEventType& eEventType) {
    if (eEventType != ui::Widget::TouchEventType::ENDED) { return; }

//    auto scene = GameLayer::createScene(stage);
//    Director::getInstance()->replaceScene(TransitionFade::create(TRANSITION_TIME, scene));
}

void PauseLayer::toggleSound(const Ref* ref, const cocos2d::ui::Widget::TouchEventType& eEventType) {
    if (eEventType != ui::Widget::TouchEventType::ENDED) { return; }
    
    SoundManager::ToggleSound();
    if (SoundManager::IsSoundActive()) {
        _btnSoundToggle->loadTextures(imageBtnSoundOn, imageBtnSoundOn);
    }
    else {
        _btnSoundToggle->loadTextures(imageBtnSoundOff, imageBtnSoundOff);
    }
}

void PauseLayer::toggleMusic(const Ref* ref, const cocos2d::ui::Widget::TouchEventType& eEventType) {
    if (eEventType != ui::Widget::TouchEventType::ENDED) { return; }
    
    SoundManager::ToggleMusic();
    if (SoundManager::IsMusicActive()) {
        _btnMusicToggle->loadTextures(imageBtnMusicOn, imageBtnMusicOn);
    }
    else {
        _btnMusicToggle->loadTextures(imageBtnMusicOff, imageBtnMusicOff);
    }
}




