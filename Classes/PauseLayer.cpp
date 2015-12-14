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

static Vec2 normalizedPosition = Vec2(0.1, 0.1);

static Button* _btnResume;
static Button* _btnRestart;
static Button* _btnMenu;
static Button* _btnSoundToggle;
static Button* _btnMusicToggle;

bool PauseLayer::init()
{
    if ( !LayerColor::initWithColor(Color4B(0, 0, 0, 190)) ) {
        return false;
    }

    _origin = Director::getInstance()->getVisibleOrigin();
    _visibleSize = Director::getInstance()->getVisibleSize();

    this->setContentSize(Size(_visibleSize.width, _visibleSize.height));
    this->setPosition(0, 0);
    
    createMenus();

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
                     _btnMenu->getContentSize().height * 6)); // including margin gap
    
    // lv->setBackGroundColorType(ui::Layout::BackGroundColorType::SOLID);
    // lv->setBackGroundColor(Color3B::GREEN);
    lv->setNormalizedPosition(normalizedPosition);
    lv->setBounceEnabled(false);
    this->addChild(lv);

}

void PauseLayer::addResumeButton() {
    _btnResume = Button::create(imageBtnResume, "");
    if (not _btnResume) { return; }
    
    _btnResume->addTouchEventListener(CC_CALLBACK_1(GameLayer::resumeClicked, GameLayer::getInstance()));
}

void PauseLayer::addRestartButton() {
    _btnRestart = Button::create(imageBtnRestart, "");
    if (not _btnRestart) { return; }

    _btnRestart->addTouchEventListener(CC_CALLBACK_2(PauseLayer::restartClicked, this));
}

void PauseLayer::addMenuButton() {
    _btnMenu = Button::create(imageBtnMenu, "");
    if (not _btnMenu) { return; }
    _btnMenu->addTouchEventListener(CC_CALLBACK_2(PauseLayer::menuClicked, this));
}

void PauseLayer::addSoundButton() {
    if (SoundManager::IsSoundActive()) {
        _btnSoundToggle = Button::create(imageBtnSoundOn, "");
    }
    else {
        _btnSoundToggle = Button::create(imageBtnSoundOff, "");
    }
    if (not _btnSoundToggle) { return; }
    _btnSoundToggle->addTouchEventListener(CC_CALLBACK_2(PauseLayer::toggleSound, this));
}

void PauseLayer::addMusicButton() {
    if (SoundManager::IsMusicActive()) {
        _btnMusicToggle = Button::create(imageBtnMusicOn, "");
    }
    else {
        _btnMusicToggle = Button::create(imageBtnMusicOff, "");
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
        _btnSoundToggle->loadTextures(imageBtnSoundOn, "");
    }
    else {
        _btnSoundToggle->loadTextures(imageBtnSoundOff, "");
    }
}

void PauseLayer::toggleMusic(const Ref* ref, const cocos2d::ui::Widget::TouchEventType& eEventType) {
    if (eEventType != ui::Widget::TouchEventType::ENDED) { return; }
    
    SoundManager::ToggleMusic();
    if (SoundManager::IsMusicActive()) {
        _btnMusicToggle->loadTextures(imageBtnMusicOn, "");
    }
    else {
        _btnMusicToggle->loadTextures(imageBtnMusicOff, "");
    }
}




