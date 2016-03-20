#include "PauseHUD.h"

#include <UIListView.h>

#include "GameLayer.h"
#include "BackButton.h"
#include "MainMenuLayer.h"
#include "SoundManager.h"

#include "SonarFrameworks.h"

using namespace cocos2d;
using namespace cocos2d::ui;

static const std::string imageBtnMainMenu = "btn_menu.png";
static const std::string imageBtnResume = "btn_resume.png";
static const std::string imageBtnRestart = "btn_restart.png";
static const std::string imageBtnSoundOn = "btn_soundon_big.png";
static const std::string imageBtnSoundOff = "btn_soundoff_big.png";
static const std::string imageBtnMusicOn = "btn_musicon_big.png";
static const std::string imageBtnMusicOff = "btn_musicoff_big.png";

bool PauseHUD::init()
{
    if ( !LayerColor::initWithColor(Color4B(0, 0, 0, 128)) ) {
        return false;
    }
    
    // No need to proceed if GameLayer is not present
    if (not GameLayer::getInstance()) { return false; }

    _origin = Director::getInstance()->getVisibleOrigin();
    _visibleSize = Director::getInstance()->getVisibleSize();

    this->setContentSize(Size(_visibleSize.width, _visibleSize.height));
    this->setPosition(0, 0);
    
    createMenus();

    return true;
}

void PauseHUD::createMenus() {
    ListView* lv = ListView::create();
    
    addResumeButton();
    addRestartButton();
    addMainMenuButton();
    addSoundButton();
    addMusicButton();
    
    if (_btnResume) { lv->pushBackCustomItem(_btnResume); }
    if (_btnRestart) { lv->pushBackCustomItem(_btnRestart); }
    if (_btnMainMenu) { lv->pushBackCustomItem(_btnMainMenu); }
    if (_btnMusicToggle) { lv->pushBackCustomItem(_btnMusicToggle); }
    if (_btnSoundToggle) { lv->pushBackCustomItem(_btnSoundToggle); }
    
    lv->setGravity(ui::ListView::Gravity::CENTER_HORIZONTAL);
    lv->setItemsMargin(20);
    lv->setSize(Size(_btnMainMenu->getContentSize().width,
                     _btnMainMenu->getContentSize().height * 5 + 80)); // including margin gap (20*4)
    // lv->setBackGroundColorType(ui::Layout::BackGroundColorType::SOLID);
    // lv->setBackGroundColor(Color3B(128, 128, 128));
    lv->setPosition(Size(_visibleSize.width * 0.01,
                         (_visibleSize.height - lv->getContentSize().height) * 0.5));
    lv->setBounceEnabled(false);
    this->addChild(lv);
}

void PauseHUD::addResumeButton() {
    _btnResume = Button::create(imageBtnResume, imageBtnResume);
    if (not _btnResume) { return; }
    
    _btnResume->addTouchEventListener(CC_CALLBACK_1(GameLayer::resumeClicked, GameLayer::getInstance()));
}

void PauseHUD::addRestartButton() {
    _btnRestart = Button::create(imageBtnRestart, imageBtnRestart);
    if (not _btnRestart) { return; }

    _btnRestart->addTouchEventListener(CC_CALLBACK_2(PauseHUD::restartClicked, this));
}

void PauseHUD::addMainMenuButton() {
    _btnMainMenu = Button::create(imageBtnMainMenu, imageBtnMainMenu);
    if (not _btnMainMenu) { return; }
    _btnMainMenu->addTouchEventListener(CC_CALLBACK_2(PauseHUD::mainMenuClicked, this));
}

void PauseHUD::addSoundButton() {
    if (SoundManager::IsSoundActive()) {
        _btnSoundToggle = Button::create(imageBtnSoundOn, imageBtnSoundOn);
    }
    else {
        _btnSoundToggle = Button::create(imageBtnSoundOff, imageBtnSoundOff);
    }
    if (not _btnSoundToggle) { return; }
    _btnSoundToggle->addTouchEventListener(CC_CALLBACK_2(PauseHUD::toggleSound, this));
}

void PauseHUD::addMusicButton() {
    if (SoundManager::IsMusicActive()) {
        _btnMusicToggle = Button::create(imageBtnMusicOn, imageBtnMusicOn);
    }
    else {
        _btnMusicToggle = Button::create(imageBtnMusicOff, imageBtnMusicOff);
    }
    if (not _btnMusicToggle) { return; }
    _btnMusicToggle->addTouchEventListener(CC_CALLBACK_2(PauseHUD::toggleMusic, this));
}

// Click Events
void PauseHUD::mainMenuClicked(Ref const* ref, cocos2d::ui::Widget::TouchEventType const& eEventType) {
    if (eEventType != ui::Widget::TouchEventType::ENDED) { return; }
    
    {
        // Sonar Framework - Hide CenterBannerAd (typically 300x250)
        SonarCocosHelper::AdMob::hideBannerAd();
    }

    BackButton<MainMenuLayer>* mainMenu = new BackButton<MainMenuLayer>();
    if (not mainMenu) { return; }
    mainMenu->goBack(this);
}

void PauseHUD::restartClicked(Ref const* ref, cocos2d::ui::Widget::TouchEventType const& eEventType) {
    if (eEventType != ui::Widget::TouchEventType::ENDED) { return; }
    
    {
        // Sonar Framework - Hide CenterBannerAd (typically 300x250)
        SonarCocosHelper::AdMob::hideBannerAd();
    }

    auto scene = GameLayer::createScene(GameLayer::getInstance()->getStage());
    if (not scene) {
        return;
    }
    
    auto d = Director::getInstance();
    if (d->isPaused()) {
        d->resume();
    }
    d->replaceScene(TransitionFade::create(TRANSITION_TIME, scene));
}

void PauseHUD::toggleSound(Ref const* ref, cocos2d::ui::Widget::TouchEventType const& eEventType) {
    if (eEventType != ui::Widget::TouchEventType::ENDED) { return; }
    
    SoundManager::ToggleSound();
    if (SoundManager::IsSoundActive()) {
        _btnSoundToggle->loadTextures(imageBtnSoundOn, imageBtnSoundOn);
    }
    else {
        _btnSoundToggle->loadTextures(imageBtnSoundOff, imageBtnSoundOff);
    }
}

void PauseHUD::toggleMusic(Ref const* ref, cocos2d::ui::Widget::TouchEventType const& eEventType) {
    if (eEventType != ui::Widget::TouchEventType::ENDED) { return; }
    
    SoundManager::ToggleMusic(SoundManager::gameplayMusic);
    if (SoundManager::IsMusicActive()) {
        _btnMusicToggle->loadTextures(imageBtnMusicOn, imageBtnMusicOn);
    }
    else {
        _btnMusicToggle->loadTextures(imageBtnMusicOff, imageBtnMusicOff);
    }
}




