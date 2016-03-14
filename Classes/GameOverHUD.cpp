#include "GameOverHUD.h"

#include "Constants.h"
#include "GameLayer.h"
#include "MainMenuLayer.h"
#include "SoundManager.h"
#include "Stage.h"
#include "StageStatus.h"

using namespace cocos2d;
using namespace ui;

static const std::string imageBtnMainMenu = "btn_menu.png";
static const std::string imageBtnNextStage = "btn_nextstage.png";
static const std::string imageBtnRestart = "btn_restart.png";
static const std::string imageEmptyStar = "star_empty.png";
static const std::string imageExplosion = "snowflake.png";
static const std::string imageScoreBoard = "scoreboard.png";
static const std::string imageTimer = "timer.png";

void GameOverHUD::setup(Stage const& stage, int const collectedEggs, int const totalEggs, int const collectedPizzas, int const totalPizzas, int const timeTaken, float const stageCompletionPercentage)
{
    _stage = stage;
    bool isStageClear = (stage.getName() != StageStatus::infinite) ? stageCompletionPercentage >= 100 : true;
    
    // EGG Percentage
    float eggPercent = 0;
    if (collectedEggs) {
        eggPercent = (collectedEggs * 100) / totalEggs;
    }
    
    // Calculate time bonus
    int timeSaved = 0;
    int stageTimeLimit = getStageTimeLimit(stage.getName());
    
    if (isStageClear and stageTimeLimit - timeTaken > 0) {
        
        // calculate time bonus only if the stage is cleared
        timeSaved = stageTimeLimit - timeTaken;
        if (timeSaved > MAX_TIME_BONUS) {
            timeSaved = MAX_TIME_BONUS; // 15 is the max time bonus
        }
    }
    
    // Calculate the STAR //
    int score = 0;
    int star = 0;
    bool isNewHighscore = false;

    {
        // SCORE and STAR calculation
        score = (stage.getName() == StageStatus::infinite) ? collectedEggs : (eggPercent + timeSaved);
        
        isNewHighscore = (score > stage.getHighScore()) and isStageClear ? true : false;
        _stage.setScore(score);
        
        star = calculateStar(stage.getName(), score);
        if (star > stage.getStar()) {
            _stage.setStar(star);
        }
    }

    
    prepare(score, collectedEggs, totalEggs, timeTaken, star, isNewHighscore, isStageClear);
    
    // Save and Unlock next stage
    try {
        StageStatus::saveStage(_stage);
        if (star) {
            StageStatus::unlockNextStage(_stage);
            
            if (_btnMainMenu) {
                _btnMainMenu->loadTextureNormal(imageBtnNextStage);
                _btnMainMenu->loadTexturePressed(imageBtnNextStage);
            }
        }
    }
    catch(...) {
        CCLOG("Coulnd't store stage info from GameOver");
    }
}

bool GameOverHUD::init()
{
    if ( !LayerColor::initWithColor(Color4B(0, 0, 0, 0)) ) {
        return false;
    }
    
    _origin = Director::getInstance()->getVisibleOrigin();
    _visibleSize = Director::getInstance()->getVisibleSize();
    
    this->setContentSize(Size(_visibleSize.width, _visibleSize.height));
    this->setPosition(0, 0);
    
    addScoreBoard();
    addResultSummaryLabel();
    addStars();
    addEggsLabel();
    addTimerLogoAndLabel();
    addScoreLabel();
    addHighscoreLabel();

    addMainMenu();
    addRestartButton();
    
    return true;
}

void GameOverHUD::addScoreBoard() {
    _scoreBoard = Sprite::create(imageScoreBoard);
    if (not _scoreBoard) { return; }
    _scoreBoard->setPosition(Vec2(_visibleSize.width * 0.5, _visibleSize.height * 0.5));
    this->addChild(_scoreBoard, BackgroundLayer::layerBackground);
}

void GameOverHUD::addResultSummaryLabel() {
    _resultSummaryLabel = Label::createWithTTF("", font, _visibleSize.height * SCORE_FONT_SIZE_SMALL);
    if (not _resultSummaryLabel) { return; }
    _resultSummaryLabel->setPosition(_visibleSize.width * 0.5, _visibleSize.height * 0.9);
    this->addChild(_resultSummaryLabel, BackgroundLayer::layerChicken);
}

void GameOverHUD::addStars() {
    float baseHeightForStars = 0.675;

    _star1 = Sprite::create(imageEmptyStar);
    if (_star1) {
        _star1->setPosition(_visibleSize.width * 0.5 - _star1->getContentSize().width * 1.25, _visibleSize.height * baseHeightForStars);
        this->addChild(_star1, BackgroundLayer::layerChicken);
        _stars.push_back(_star1);
    }
    
    _star2 = Sprite::create(imageEmptyStar);
    if (_star2) {
        _star2->setPosition(_visibleSize.width * 0.5, _visibleSize.height * (baseHeightForStars + 0.05));
        this->addChild(_star2, BackgroundLayer::layerChicken);
        _stars.push_back(_star2);
    }
    
    _star3 = Sprite::create(imageEmptyStar);
    if (_star3) {
        _star3->setPosition(_visibleSize.width * 0.5 + _star1->getContentSize().width * 1.25, _visibleSize.height * baseHeightForStars);
        this->addChild(_star3, BackgroundLayer::layerChicken);
        _stars.push_back(_star3);
    }
}

void GameOverHUD::addEggsLabel() {
    _eggsLabel = Label::createWithTTF("", font, _visibleSize.height * SCORE_FONT_SIZE_SMALL);
    if (not _eggsLabel) { return; }
    _eggsLabel->setPosition(_visibleSize.width * 0.5, _visibleSize.height * 0.5);
    this->addChild(_eggsLabel, BackgroundLayer::layerChicken);
}

void GameOverHUD::addTimerLogoAndLabel() {
    // Timer Sprite
    _timerSprite = Sprite::create(imageTimer);
    if (_timerSprite) {
        _timerSprite->setPosition(Vec2(_visibleSize.width * 0.45, _visibleSize.height * 0.41));
        this->addChild(_timerSprite, BackgroundLayer::layerBackground);
    }
    
    // Timer Label
    _timeLabel = Label::createWithTTF("", font, _visibleSize.height * SCORE_FONT_SIZE_SMALL);
    if (_timeLabel) {
        _timeLabel->setColor(Color3B::WHITE);
        _timeLabel->setPosition(_visibleSize.width * 0.54, _visibleSize.height * 0.4);
        this->addChild(_timeLabel, BackgroundLayer::layerChicken);
    }
}

void GameOverHUD::addScoreLabel() {
    _scoreLabel = Label::createWithTTF("", font, _visibleSize.height * SCORE_FONT_SIZE_SMALL);
    if (not _scoreLabel) { return; }
    _scoreLabel->setColor(Color3B::WHITE);
    _scoreLabel->setPosition(_visibleSize.width * 0.5, _visibleSize.height * 0.31);
    this->addChild(_scoreLabel, BackgroundLayer::layerChicken);
}

void GameOverHUD::addHighscoreLabel() {
    _highscoreLabel = Label::createWithTTF("", font, _visibleSize.height * SCORE_FONT_SIZE_EXTRA_SMALL);
    if (not _highscoreLabel) { return; }
    _highscoreLabel->setColor(Color3B::WHITE);
    _highscoreLabel->setPosition(_visibleSize.width * 0.5, _visibleSize.height * 0.23);
    this->addChild(_highscoreLabel, BackgroundLayer::layerChicken);
}

void GameOverHUD::addMainMenu() {
    _btnMainMenu = Button::create(imageBtnMainMenu, imageBtnMainMenu);
    if (not _btnMainMenu) { return; }
    _btnMainMenu->addTouchEventListener(CC_CALLBACK_2(GameOverHUD::mainMenuClicked, this));
    _btnMainMenu->setPosition(Point(_visibleSize.width * 0.5 + _btnMainMenu->getContentSize().width * 0.8,
                                    _visibleSize.height * 0.12));
    _btnMainMenu->setTouchEnabled(false); // Will be active after Star's appearance
    this->addChild(_btnMainMenu, BackgroundLayer::layerChicken);
}

void GameOverHUD::addRestartButton() {
    _btnRestart = Button::create(imageBtnRestart, imageBtnRestart);
    if (not _btnRestart) { return; }
    _btnRestart->addTouchEventListener(CC_CALLBACK_2(GameOverHUD::restartClicked, this));
    _btnRestart->setPosition(Vec2(_visibleSize.width * 0.5 - _btnRestart->getContentSize().width * 0.8,
                                  _visibleSize.height * 0.12));
    _btnRestart->setTouchEnabled(false); // Will be active after Star's appearance
    this->addChild(_btnRestart, BackgroundLayer::layerChicken);
}

void GameOverHUD::addChickenBannerInsteadOfStars(Vec2 const& position) {
    for (auto s: _stars) {
        s->setVisible(false);
    }
    
    // Replace Stars with banner
    Sprite* banner = Sprite::create("banner_chicken.png");
    banner->setPosition(position.x, position.y);
    this->addChild(banner, BackgroundLayer::layerChicken);

}

int GameOverHUD::getStageTimeLimit(std::string const& stageName) {
    if (stageName == StageStatus::england) {
        return 95; // 1:35
    }
    if (stageName == StageStatus::italy) {
        return 75; // 1:15
    }
    if (stageName == StageStatus::france) {
        return 100; // 1:40
    }
    if (stageName == StageStatus::germany) {
        return 95; // 1:35
    }
    if (stageName == StageStatus::spain) {
        return 90; // 1:30
    }
    if (stageName == StageStatus::netherlands) {
        return 95; // 1:35
    }
    return 0;
}

int GameOverHUD::calculateStar(std::string const& stageName, int score) {
    int max(0), mid(0), min(0);
    
    if (stageName == StageStatus::england) {
        max = 75;
        mid = 65;
        min = 60;
    }
    else if (stageName == StageStatus::italy) {
        max = 80;
        mid = 70;
        min = 60;
    }
    else if (stageName == StageStatus::france) {
        max = 75;
        mid = 62;
        min = 50;
    }
    else if (stageName == StageStatus::germany) {
        max = 65;
        mid = 55;
        min = 45;
    }
    else if (stageName == StageStatus::spain) {
        max = 90;
        mid = 80;
        min = 70;
    }
    else if (stageName == StageStatus::netherlands) {
        max = 80;
        mid = 70;
        min = 60;
    }
    
    if (score >= max) {
        return 3;
    }
    if (score >= mid) {
        return 2;
    }
    if (score >= min) {
        return 1;
    }
    return 0;
}

void GameOverHUD::prepare(int score, int collectedEggs, int totalEggs, int timeTaken, int star, bool isNewHighscore, bool isStageClear) {
    if (not isStageClear) {
        // Failed
        if (_resultSummaryLabel) {
            _resultSummaryLabel->setString("Failed !");
            _resultSummaryLabel->setColor(Color3B::WHITE);
        }
        
        if (_eggsLabel)      { _eggsLabel->setVisible(false); }
        if (_timeLabel)      { _timeLabel->setVisible(false); }
        if (_timerSprite)    { _timerSprite->setVisible(false); }
        if (_scoreLabel)     { _scoreLabel->setVisible(false); }
        if (_highscoreLabel) { _highscoreLabel->setVisible(false); }

        addChickenBannerInsteadOfStars(Vec2(_visibleSize.width * 0.5, _visibleSize.height * 0.6));
        
        if(_btnMainMenu) _btnMainMenu->setTouchEnabled(true);
        if(_btnRestart) _btnRestart->setTouchEnabled(true);
        
        return;
    }
    
    // EGGS
    if (_eggsLabel) {
        std::string str = String::createWithFormat("Eggs: %d/%d", collectedEggs, totalEggs)->getCString();
        _eggsLabel->setString(str);
    }
    
    // TIME
    if (_timeLabel) {
        time_t seconds(timeTaken);
        struct tm* time = gmtime(&seconds);
        std::string timeStr = String::createWithFormat("%d:%02d s", time->tm_min, time->tm_sec)->getCString();
        _timeLabel->setString(timeStr);
    }
    
    // SCORE
    if (_scoreLabel) {
        std::string str = String::createWithFormat("Score: %d", score)->getCString();
        _scoreLabel->setString(str);
    }
    
    // HIGHSCORE
    if (_highscoreLabel) {
        std::string str = String::createWithFormat("Highscore: %d", _stage.getHighScore())->getCString();
        if (isNewHighscore) {
            _highscoreLabel->setColor(Color3B::ORANGE);
            str = String::createWithFormat("New Highscore: %d", _stage.getHighScore())->getCString();
            addFirework();
        }

        _highscoreLabel->setString(str);
    }
    
    // STAR
    if (_stage.getName() != StageStatus::infinite) {

        // Summary
        if (_resultSummaryLabel) {
            _resultSummaryLabel->setString("Stage Clear");
            _resultSummaryLabel->setColor(Color3B::ORANGE);
        }
        
        // Star Animation
        Vector<FiniteTimeAction*> actions;
        for (int i = 0; i < star and i < _stars.size(); ++i) {
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
        // Hide empty stars
        addChickenBannerInsteadOfStars(Vec2(_visibleSize.width * 0.5, _visibleSize.height * 0.75));
        
        if(_btnMainMenu) _btnMainMenu->setTouchEnabled(true);
        if(_btnRestart) _btnRestart->setTouchEnabled(true);
        
        // No need to write Summary for infinite stage
        if (_resultSummaryLabel) { _resultSummaryLabel->setString(""); }
    }

}

void GameOverHUD::addFirework() {
    // Explosion Effect
    Vec2 position = Vec2(_visibleSize.width * 0.5, _visibleSize.height * 0.23);

    ParticleExplosion* explosion1 = ParticleExplosion::createWithTotalParticles(100);
    explosion1->setTexture(Director::getInstance()->getTextureCache()->addImage(imageExplosion));
    explosion1->setStartColor(Color4F::YELLOW);
    explosion1->setEndColor(Color4F::YELLOW);
    explosion1->setScale(0.75);
    explosion1->setSpeed(5);
    explosion1->setPosition(position);
    this->addChild(explosion1, BackgroundLayer::layerTouch);
    
    //SoundManager::Play(SoundManager::soundExplosion);    // play bomb sound
}

void GameOverHUD::mainMenuClicked(Ref const* ref, cocos2d::ui::Widget::TouchEventType const& eEventType) {
    if (eEventType != ui::Widget::TouchEventType::ENDED) { return; }

    auto d = Director::getInstance();
    if (d->isPaused()) {
        d->resume();
    }
    
    BackButton<MainMenuLayer>* mainMenu = new BackButton<MainMenuLayer>();
    if (not mainMenu) { return; }
    mainMenu->goBack(this);
}

void GameOverHUD::restartClicked(const Ref* ref, const cocos2d::ui::Widget::TouchEventType& eEventType) {
    if (eEventType != ui::Widget::TouchEventType::ENDED) { return; }

    auto scene = GameLayer::createScene(_stage);
    if (not scene) {
        return;
    }
    
    auto d = Director::getInstance();
    if (d->isPaused()) {
        d->resume();
    }
    d->replaceScene(TransitionFade::create(TRANSITION_TIME, scene));

}














