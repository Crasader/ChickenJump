#include "GameOverLayer.h"

#include "Constants.h"
#include "GameLayer.h"
#include "MainMenuLayer.h"
#include "SoundManager.h"
#include "Stage.h"
#include "StageStatus.h"

using namespace cocos2d;
using namespace ui;

static const std::string imageBtnMainMenu = "btn_menu.png";
static const std::string imageBtnRestart = "btn_restart.png";
static const std::string imageEmptyStar = "star_empty.png";
static const std::string imageExplosion = "explosion.png";
static const std::string imageScoreBoard = "scoreboard.png";
static const std::string imageTimer = "timer.png";

void GameOverLayer::setup(Stage const& stage, int const collectedEggs, int const totalEggs, int const collectedPizzas, int const totalPizzas, int const timeTaken, float const stageCompletionPercentage)
{
    int score = 0;
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
    
    // SCORE
    score = (stage.getName() == StageStatus::infinite) ? collectedEggs : eggPercent + timeSaved;
    
    bool isNewHighscore = score > stage.getHighScore() and isStageClear ? true : false;
    _stage.setScore(score);
    
    // Calculate the STAR //
    int star = calculateStar(stage.getName(), score);
    _stage.setStar(star);
    
    prepare(score, totalEggs, collectedPizzas, totalPizzas, timeTaken, isNewHighscore, isStageClear);
    
    // Save and Unlock next stage
    try {
        StageStatus::saveStage(_stage);
        if (star and isStageClear) {
            StageStatus::unlockNextStage(_stage);
        }
    }
    catch(...) {
        CCLOG("Coulnd't store stage info from GameOver");
    }

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
        _timerSprite->setPosition(Vec2(_visibleSize.width * 0.42, _visibleSize.height * 0.31));
        this->addChild(_timerSprite, BackgroundLayer::layerBackground);
    }
    
    // Timer Label
    _timeLabel = Label::createWithTTF("", font, _visibleSize.height * SCORE_FONT_SIZE);
    if (_timeLabel) {
        _timeLabel->setColor(Color3B::WHITE);
        _timeLabel->setPosition(_visibleSize.width * 0.56, _visibleSize.height * 0.3);
        this->addChild(_timeLabel, BackgroundLayer::layerChicken);
    }
}

void GameOverLayer::addMainMenu() {
    _btnMainMenu = Button::create(imageBtnMainMenu, imageBtnMainMenu);
    if (not _btnMainMenu) { return; }
    _btnMainMenu->addTouchEventListener(CC_CALLBACK_2(GameOverLayer::mainMenuClicked, this));
    _btnMainMenu->setPosition(Point(_visibleSize.width * 0.5 + _btnMainMenu->getContentSize().width * 0.70,
                                    _visibleSize.height * 0.15));
    _btnMainMenu->setTouchEnabled(false); // Will be active after Star's appearance
    this->addChild(_btnMainMenu, BackgroundLayer::layerChicken);
}

void GameOverLayer::addRestartButton() {
    _btnRestart = Button::create(imageBtnRestart, imageBtnRestart);
    if (not _btnRestart) { return; }
    _btnRestart->addTouchEventListener(CC_CALLBACK_2(GameOverLayer::restartClicked, this));
    _btnRestart->setPosition(Vec2(_visibleSize.width * 0.5 - _btnRestart->getContentSize().width * 0.70,
                                  _visibleSize.height * 0.15));
    _btnRestart->setTouchEnabled(false); // Will be active after Star's appearance
    this->addChild(_btnRestart, BackgroundLayer::layerChicken);
}

int GameOverLayer::getStageTimeLimit(std::string const& stageName) {
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

int GameOverLayer::calculateStar(std::string const& stageName, int score) {
    int max(0), mid(0), min(0);
    
    if (stageName == StageStatus::england) {
        max = 75;
        mid = 65;
        min = 60;
    }
    if (stageName == StageStatus::italy) {
        max = 80;
        mid = 70;
        min = 60;
    }
    if (stageName == StageStatus::france) {
        max = 75;
        mid = 62;
        min = 50;
    }
    if (stageName == StageStatus::germany) {
        max = 65;
        mid = 55;
        min = 45;
    }
    if (stageName == StageStatus::spain) {
        max = 90;
        mid = 80;
        min = 70;
    }
    if (stageName == StageStatus::netherlands) {
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

void GameOverLayer::celebrateHighscore() {
    showHighscoreBanner();
    addFirework();
}

void GameOverLayer::prepare(int score, int totalEggs, int collectedPizzas, int totalPizzas, unsigned int timeTaken, bool isNewHighscore, bool isStageClear) {
    // HIGHSCORE
    if (_highScoreLabel) {
        std::string highScoreStr = String::createWithFormat("HighScore: %d", _stage.getHighScore())->getCString();
        _highScoreLabel->setString(highScoreStr);
    }

    // SCORE
    // TODO: FIX SCORE STRING
    if (_scoreLabel) {
        std::string scoreStr = String::createWithFormat("Score: [%d](%d)", score, totalEggs)->getCString();
        _scoreLabel->setString(scoreStr);
    }
    
    // TIME
    if (_timeLabel) {
        time_t seconds(timeTaken);
        struct tm* time = gmtime(&seconds);
        std::string timeStr = String::createWithFormat("%d:%02d s", time->tm_min, time->tm_sec)->getCString();
        _timeLabel->setString(timeStr);
    }
    
    // STAR
    if (_stage.getName() != StageStatus::infinite and isStageClear) {
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
        Sprite* banner = Sprite::create((_stage.getName() == StageStatus::infinite) ? "banner_chicken.png" : "banner_you_lose.png");
        banner->setPosition(_visibleSize.width * 0.5, _visibleSize.height * 0.8);
        this->addChild(banner, BackgroundLayer::layerChicken);

        if (_stage.getName() != StageStatus::infinite) {
            return; // no need to check highscore anymore
        }
    }
    
    // NEW HIGHSCORE
    if (isNewHighscore and (_stage.getStar() or _stage.getName() == StageStatus::infinite)) {
        celebrateHighscore();
    }
}

void GameOverLayer::showHighscoreBanner() {
    Sprite* banner = Sprite::create("banner_highscore.png");
    if (not banner) { return; }
    
    banner->setPosition(Vec2(_visibleSize.width * 0.5, _visibleSize.height + banner->getContentSize().height));
    this->addChild(banner, BackgroundLayer::layerChicken);
    
    auto moveIn = MoveTo::create(1, Vec2(_visibleSize.width * 0.5, _visibleSize.height * 0.6));
    auto moveOut = MoveTo::create(1, Vec2(_visibleSize.width * 0.5, _visibleSize.height + banner->getContentSize().height));

    auto seq = Sequence::create(moveIn, DelayTime::create(3), moveOut, NULL);
    banner->runAction(seq);
}

void GameOverLayer::addFirework() {
    // Explosion Effect
    int xOne = RandomHelper::random_real(_visibleSize.width * 0.3, _visibleSize.width * 0.7);
    int yOne = RandomHelper::random_real(_visibleSize.height * 0.3, _visibleSize.height * 0.7);

    ParticleExplosion* explosion1 = ParticleExplosion::createWithTotalParticles(100);
    explosion1->setTexture(Director::getInstance()->getTextureCache()->addImage(imageExplosion));
    explosion1->setStartColor(Color4F::YELLOW);
    explosion1->setEndColor(Color4F::YELLOW);
    explosion1->setScale(0.75);
    explosion1->setSpeed(5);
    explosion1->setPosition(Vec2(xOne, yOne));
    this->addChild(explosion1, BackgroundLayer::layerTouch);
    
    int xTwo = RandomHelper::random_real(_visibleSize.width * 0.3, _visibleSize.width * 0.7);
    int yTwo = RandomHelper::random_real(_visibleSize.height * 0.3, _visibleSize.height * 0.7);
    
    ParticleExplosion* explosion2 = ParticleExplosion::createWithTotalParticles(66);
    explosion2->setTexture(Director::getInstance()->getTextureCache()->addImage(imageExplosion));
    explosion2->setStartColor(Color4F::YELLOW);
    explosion2->setEndColor(Color4F::YELLOW);
    explosion2->setScale(0.75);
    explosion2->setSpeed(5);
    explosion2->setPosition(Vec2(xTwo, yTwo));
    this->addChild(explosion2, BackgroundLayer::layerTouch);
    
    int xThree = RandomHelper::random_real(_visibleSize.width * 0.3, _visibleSize.width * 0.7);
    int yThree = RandomHelper::random_real(_visibleSize.height * 0.3, _visibleSize.height * 0.7);
    
    ParticleExplosion* explosion3 = ParticleExplosion::createWithTotalParticles(66);
    explosion3->setTexture(Director::getInstance()->getTextureCache()->addImage(imageExplosion));
    explosion3->setStartColor(Color4F::YELLOW);
    explosion3->setEndColor(Color4F::YELLOW);
    explosion3->setScale(0.75);
    explosion3->setSpeed(5);
    explosion3->setPosition(Vec2(xThree, yThree));
    this->addChild(explosion3, BackgroundLayer::layerTouch);
    
    //SoundManager::Play(SoundManager::soundExplosion);    // play bomb sound
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














