#include "GameOverLayer.h"

#include "Constants.h"
#include "MainMenuLayer.h"
#include "Stage.h"
#include "StageStatus.h"
#include <UIButton.h>

using namespace cocos2d;
using namespace ui;

static unsigned int _score = 0;
static bool _isStageClear = false;
static Stage _stage;

static Button* _btnMainMenu;
static const std::string imageBtnMainMenu = "btn_menu.png";

void GameOverLayer::prepare(unsigned int score, Stage const& stage, bool isStageClear)
{
    _stage = stage;
    _score = score;
    _isStageClear = isStageClear;
    
    addHighscoreLabel();
    addScoreLabel();
    addMainMenu();
    saveStatsAndUnlockNextStage();
    if (isStageClear) {
        updateDifficultyLevel();
    }
}

bool GameOverLayer::init()
{
    if ( !LayerColor::initWithColor(Color4B(0, 0, 0, 128)) ) {
        return false;
    }
    
    _origin = Director::getInstance()->getVisibleOrigin();
    _visibleSize = Director::getInstance()->getVisibleSize();
    
    this->setContentSize(Size(_visibleSize.width, _visibleSize.height));
    this->setPosition(0, 0);

    return true;
}

void GameOverLayer::addHighscoreLabel() {
    UserDefault* d = UserDefault::getInstance();
    auto highScore = d->getIntegerForKey(HIGHSCORE, 0);
    if (_score > highScore) {
        highScore = _score;
        d->setIntegerForKey(HIGHSCORE, highScore);
        d->flush();
    }
    std::string highScoreStr = String::createWithFormat("HighScore: %d", highScore)->getCString();
    Label* highScoreLabel = Label::createWithTTF(highScoreStr, font, _visibleSize.height * SCORE_FONT_SIZE);
    if (not highScoreLabel) { return; }
    highScoreLabel->setColor(Color3B::WHITE);
    highScoreLabel->setPosition(_visibleSize.width / 2 + _origin.x, _visibleSize.height * 0.88 + _origin.y);
    this->addChild(highScoreLabel, BackgroundLayer::layerChicken);
}

void GameOverLayer::addScoreLabel() {
    std::string scoreStr = String::createWithFormat("Score: %d", _score)->getCString();
    Label* scoreLabel = Label::createWithTTF(scoreStr, font, _visibleSize.height * SCORE_FONT_SIZE);
    if (not scoreLabel) { return; }
    scoreLabel->setColor(Color3B::WHITE);
    scoreLabel->setPosition(_visibleSize.width / 2 + _origin.x, _visibleSize.height * 0.7 + _origin.y);
    this->addChild(scoreLabel, BackgroundLayer::layerChicken);
}

void GameOverLayer::addMainMenu() {
    _btnMainMenu = Button::create(imageBtnMainMenu, imageBtnMainMenu);
    if (not _btnMainMenu) { return; }
    _btnMainMenu->addTouchEventListener(CC_CALLBACK_2(GameOverLayer::mainMenuClicked, this));
    _btnMainMenu->setPosition(Point(_visibleSize.width / 2 + _origin.x, _visibleSize.height * 0.42 + _origin.y));
    this->addChild(_btnMainMenu);
}

void GameOverLayer::saveStatsAndUnlockNextStage() {
    try {
        Stage ss(_stage.getName(),
                 _stage.getImageFile(),
                 _stage.getClickedImageFile(),
                 _stage.getLockedImageFile(),
                 _stage.getScore(),
                 _stage.getStar(),
                 _stage.isUnlocked(),
                 _stage.isPlayed());
        
        StageStatus::saveStage(ss);

        if (_isStageClear) { StageStatus::unlockNextStage(ss); }
    }
    catch(...) {
        CCLOG("Coulnd't store stage info from GameOver");
    }
}

void GameOverLayer::mainMenuClicked(const Ref* ref, const cocos2d::ui::Widget::TouchEventType& eEventType) {
    if (eEventType != ui::Widget::TouchEventType::ENDED) { return; }

    auto d = Director::getInstance();
    if (d->isPaused()) {
        d->resume();
    }
    
    BackButton<MainMenuLayer>* mainMenu = new BackButton<MainMenuLayer>();
    if (not mainMenu) { return; }
    mainMenu->goBack(this);
}

void GameOverLayer::updateDifficultyLevel() {
    int currentDifficulty = UserDefault::getInstance()->getIntegerForKey(DIFFICULTY, 1);
    if (currentDifficulty + 1 <= DIFFICULTY_MAX) {
        UserDefault::getInstance()->setIntegerForKey(DIFFICULTY, currentDifficulty + 1);
        UserDefault::getInstance()->flush();
    }
}












