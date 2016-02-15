#include "GameOverLayer.h"

#include "Constants.h"
#include "GameLayer.h"
#include "MainMenuLayer.h"
#include "SoundManager.h"
#include "Stage.h"
#include "StageStatus.h"

using namespace cocos2d;
using namespace ui;

static Stage _stage;

static const std::string imageBtnMainMenu = "btn_menu.png";
static const std::string imageBtnRestart = "btn_restart.png";
static const std::string imageScoreBoard = "scoreboard.png";
static const std::string imageEmptyStar = "star_empty.png";
static const std::string imageTimer = "timer.png";

void GameOverLayer::setup(Stage const& stage, unsigned int score, unsigned int timeTaken, bool isStageClear)
{
    _stage = stage;
    
    // TODO::CALCULATE THE SCORE //
    _stage.setScore(score);
    
    // TODO::CALCULATE THE STAR //
    _stage.setStar(2);
    
    prepare(timeTaken);
    saveStatsAndUnlockNextStage(isStageClear);
}

bool GameOverLayer::init()
{
    if ( !LayerColor::initWithColor(Color4B(0, 0, 0, 0)) ) {
        return false;
    }
    
    _origin = Director::getInstance()->getVisibleOrigin();
    _visibleSize = Director::getInstance()->getVisibleSize();
    
    this->setContentSize(Size(_visibleSize.width, _visibleSize.height));
    this->setPosition(0, 0);
    
    addScoreBoard();
    addHighscoreLabel();
    addScoreLabel();
    addMainMenu();
    addRestartButton();
    addStars();
    addTimerLogoAndLabel();
    
    return true;
}

void GameOverLayer::addScoreBoard() {
    _scoreBoard = Sprite::create(imageScoreBoard);
    if (not _scoreBoard) { return; }
    _scoreBoard->setPosition(Vec2(_visibleSize.width * 0.5, _visibleSize.height * 0.5));
    this->addChild(_scoreBoard, BackgroundLayer::layerBackground);
}

void GameOverLayer::addStars() {
    _star1 = Sprite::create(imageEmptyStar);
    if (_star1) {
        _star1->setPosition(_visibleSize.width * 0.5 - _star1->getContentSize().width * 1.25, _visibleSize.height * 0.8);
        this->addChild(_star1, BackgroundLayer::layerChicken);
        _stars.push_back(_star1);
    }
    
    _star2 = Sprite::create(imageEmptyStar);
    if (_star2) {
        _star2->setPosition(_visibleSize.width * 0.5, _visibleSize.height * 0.85);
        this->addChild(_star2, BackgroundLayer::layerChicken);
        _stars.push_back(_star2);
    }
    
    _star3 = Sprite::create(imageEmptyStar);
    if (_star3) {
        _star3->setPosition(_visibleSize.width * 0.5 + _star1->getContentSize().width * 1.25, _visibleSize.height * 0.8);
        this->addChild(_star3, BackgroundLayer::layerChicken);
        _stars.push_back(_star3);
    }
}

void GameOverLayer::addHighscoreLabel() {
    _highScoreLabel = Label::createWithTTF("", font, _visibleSize.height * SCORE_FONT_SIZE);
    if (not _highScoreLabel) { return; }
    _highScoreLabel->setColor(Color3B::WHITE);
    _highScoreLabel->setPosition(_visibleSize.width * 0.5, _visibleSize.height * 0.6);
    this->addChild(_highScoreLabel, BackgroundLayer::layerChicken);
}

void GameOverLayer::addScoreLabel() {
    _scoreLabel = Label::createWithTTF("", font, _visibleSize.height * SCORE_FONT_SIZE);
    if (not _scoreLabel) { return; }
    _scoreLabel->setColor(Color3B::WHITE);
    _scoreLabel->setPosition(_visibleSize.width * 0.5, _visibleSize.height * 0.45);
    this->addChild(_scoreLabel, BackgroundLayer::layerChicken);
}

void GameOverLayer::addTimerLogoAndLabel() {
    // Timer Sprite
    _timerSprite = Sprite::create(imageTimer);
    if (_timerSprite) {
        _timerSprite->setPosition(Vec2(_visibleSize.width * 0.45, _visibleSize.height * 0.31));
        this->addChild(_timerSprite, BackgroundLayer::layerBackground);
    }
    
    // Timer Label
    _timeLabel = Label::createWithTTF("", font, _visibleSize.height * SCORE_FONT_SIZE);
    if (_timeLabel) {
        _timeLabel->setColor(Color3B::WHITE);
        _timeLabel->setPosition(_visibleSize.width * 0.55, _visibleSize.height * 0.3);
        this->addChild(_timeLabel, BackgroundLayer::layerChicken);
    }
}

void GameOverLayer::addMainMenu() {
    _btnMainMenu = Button::create(imageBtnMainMenu, imageBtnMainMenu);
    if (not _btnMainMenu) { return; }
    _btnMainMenu->addTouchEventListener(CC_CALLBACK_2(GameOverLayer::mainMenuClicked, this));
    _btnMainMenu->setPosition(Point(_visibleSize.width * 0.5 - _btnMainMenu->getContentSize().width * 0.70,
                                    _visibleSize.height * 0.15));
    _btnMainMenu->setTouchEnabled(false); // Will be active after Star's appearance
    this->addChild(_btnMainMenu, BackgroundLayer::layerChicken);
}

void GameOverLayer::addRestartButton() {
    _btnRestart = Button::create(imageBtnRestart, imageBtnRestart);
    if (not _btnRestart) { return; }
    _btnRestart->addTouchEventListener(CC_CALLBACK_2(GameOverLayer::restartClicked, this));
    _btnRestart->setPosition(Vec2(_visibleSize.width * 0.5 + _btnRestart->getContentSize().width * 0.70,
                                  _visibleSize.height * 0.15));
    _btnRestart->setTouchEnabled(false); // Will be active after Star's appearance
    this->addChild(_btnRestart, BackgroundLayer::layerChicken);
}

void GameOverLayer::prepare(unsigned int timeTaken) {
    // HIGHSCORE
    if (_highScoreLabel) {
        std::string highScoreStr = String::createWithFormat("HighScore: %d", _stage.getHighScore())->getCString();
        _highScoreLabel->setString(highScoreStr);
    }

    // SCORE
    if (_scoreLabel) {
        std::string scoreStr = String::createWithFormat("Score: %d", _stage.getScore())->getCString();
        _scoreLabel->setString(scoreStr);
    }
    
    // TIME
    if (_timeLabel) {
        time_t seconds(timeTaken);
        struct tm* time = gmtime(&seconds);
        std::string timeStr = String::createWithFormat("%d:%d s", time->tm_min, time->tm_sec)->getCString();
        _timeLabel->setString(timeStr);
    }
    
    // STAR
    if (_stage.getName() != StageStatus::infinite) {
        Vector<FiniteTimeAction*> actions;
        for (int i = 0; i < _stage.getStar() and i < _stars.size(); ++i) {
            actions.pushBack(DelayTime::create(1.0));
            actions.pushBack(CallFunc::create([&, i](){ _stars.at(i)->setTexture("star.png"); /* TODO:: SOUND EFFECT */ }));
        }
        actions.pushBack(CallFunc::create([=](){
            if(_btnMainMenu) _btnMainMenu->setTouchEnabled(true);
            if(_btnRestart) _btnRestart->setTouchEnabled(true);
        }));
        
        auto seq = Sequence::create(actions);
        this->runAction(seq);
    }
    else {
        if(_btnMainMenu) _btnMainMenu->setTouchEnabled(true);
        if(_btnRestart) _btnRestart->setTouchEnabled(true);

        // Empty stars are gone ;)
        for (auto s: _stars) {
            s->setVisible(false);
        }
        
        // Replacement for Stars
        Sprite* chicken = Sprite::create("playerfly_1_red.png");
        chicken->setPosition(_visibleSize.width * 0.5, _visibleSize.height * 0.8);
        
        auto scaleBy = ScaleBy::create(0.0, 2.0);
        chicken->runAction(scaleBy);

        this->addChild(chicken, BackgroundLayer::layerChicken);
    }
}

void GameOverLayer::saveStatsAndUnlockNextStage(bool isStageClear) {
    try {
        Stage ss(_stage.getName(),
                 _stage.getImageFile(),
                 _stage.getClickedImageFile(),
                 _stage.getLockedImageFile(),
                 _stage.getDifficulty(),
                 _stage.getScore(),
                 _stage.getHighScore(),
                 _stage.getStar(),
                 _stage.isUnlocked(),
                 _stage.isPlayed());
        
        StageStatus::saveStage(ss);

        if (isStageClear) { StageStatus::unlockNextStage(ss); }
    }
    catch(...) {
        CCLOG("Coulnd't store stage info from GameOver");
    }
}

void GameOverLayer::mainMenuClicked(Ref const* ref, cocos2d::ui::Widget::TouchEventType const& eEventType) {
    if (eEventType != ui::Widget::TouchEventType::ENDED) { return; }

    auto d = Director::getInstance();
    if (d->isPaused()) {
        d->resume();
    }
    
    BackButton<MainMenuLayer>* mainMenu = new BackButton<MainMenuLayer>();
    if (not mainMenu) { return; }
    mainMenu->goBack(this);
}

void GameOverLayer::restartClicked(const Ref* ref, const cocos2d::ui::Widget::TouchEventType& eEventType) {
    if (eEventType != ui::Widget::TouchEventType::ENDED) { return; }

    auto scene = GameLayer::createScene(GameLayer::getInstance()->getStage());
    if (not scene) {
        return;
    }
    
    auto d = Director::getInstance();
    if (d->isPaused()) {
        d->resume();
    }
    Director::getInstance()->replaceScene(TransitionFade::create(TRANSITION_TIME, scene));

}














