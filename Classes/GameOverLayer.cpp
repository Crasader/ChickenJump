#include "GameOverLayer.h"

#include "Constants.h"
#include "MainMenuLayer.h"
#include "Stage.h"
#include "StageStatus.h"
#include "SoundManager.h"

using namespace cocos2d;
using namespace ui;

static Stage _stage;

static const std::string imageBtnMainMenu = "btn_menu.png";
static const std::string imageScoreBoard = "scoreboard.png";

void GameOverLayer::setup(Stage const& stage, unsigned int score, bool isStageClear)
{
    _stage = stage;
    _stage.setScore(score);
    // CALCULATE THE STAR //
    _stage.setStar(2);
    
    _isStageClear = isStageClear;
    
    prepare();
    saveStatsAndUnlockNextStage();
}

bool GameOverLayer::init()
{
    if ( !LayerColor::initWithColor(Color4B(0, 0, 0, 0)) ) {
        return false;
    }
    
    _origin = Director::getInstance()->getVisibleOrigin();
    _visibleSize = Director::getInstance()->getVisibleSize();
    
    _isStageClear = false;
    
    this->setContentSize(Size(_visibleSize.width, _visibleSize.height));
    this->setPosition(0, 0);
    
    addScoreBoard();
    addHighscoreLabel();
    addScoreLabel();
    addMainMenu();
    addStars();

    return true;
}

void GameOverLayer::addHighscoreLabel() {
    _highScoreLabel = Label::createWithTTF("", font, _visibleSize.height * SCORE_FONT_SIZE);
    if (not _highScoreLabel) { return; }
    _highScoreLabel->setColor(Color3B::WHITE);
    _highScoreLabel->setPosition(_visibleSize.width * 0.5, _visibleSize.height * 0.55);
    this->addChild(_highScoreLabel, BackgroundLayer::layerChicken);
}

void GameOverLayer::addMainMenu() {
    _btnMainMenu = Button::create(imageBtnMainMenu, imageBtnMainMenu);
    if (not _btnMainMenu) { return; }
    _btnMainMenu->addTouchEventListener(CC_CALLBACK_2(GameOverLayer::mainMenuClicked, this));
    _btnMainMenu->setPosition(Point(_visibleSize.width * 0.5, _visibleSize.height * 0.25));
    _btnMainMenu->setTouchEnabled(false); // Will be active after Star's appearance
    this->addChild(_btnMainMenu, BackgroundLayer::layerChicken);
}

void GameOverLayer::addScoreBoard() {
    _scoreBoard = Sprite::create(imageScoreBoard);
    if (not _scoreBoard) { return; }
    _scoreBoard->setPosition(Vec2(_visibleSize.width * 0.5, _visibleSize.height * 0.5));
    this->addChild(_scoreBoard, BackgroundLayer::layerBackground);
}

void GameOverLayer::addScoreLabel() {
    _scoreLabel = Label::createWithTTF("", font, _visibleSize.height * SCORE_FONT_SIZE);
    if (not _scoreLabel) { return; }
    _scoreLabel->setColor(Color3B::WHITE);
    _scoreLabel->setPosition(_visibleSize.width * 0.5, _visibleSize.height * 0.4);
    this->addChild(_scoreLabel, BackgroundLayer::layerChicken);
}

void GameOverLayer::addStars() {
    _star1 = Sprite::create("star_empty.png");
    if (_star1) {
        _star1->setPosition(_visibleSize.width * 0.5 - _star1->getContentSize().width * 1.25, _visibleSize.height * 0.75);
        this->addChild(_star1, BackgroundLayer::layerChicken);
        _stars.push_back(_star1);
    }

    _star2 = Sprite::create("star_empty.png");
    if (_star2) {
        _star2->setPosition(_visibleSize.width * 0.5, _visibleSize.height * 0.8);
        this->addChild(_star2, BackgroundLayer::layerChicken);
        _stars.push_back(_star2);
    }

    _star3 = Sprite::create("star_empty.png");
    if (_star3) {
        _star3->setPosition(_visibleSize.width * 0.5 + _star1->getContentSize().width * 1.25, _visibleSize.height * 0.75);
        this->addChild(_star3, BackgroundLayer::layerChicken);
        _stars.push_back(_star3);
    }
}

void GameOverLayer::prepare() {
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
    
    // STAR
    if (_stage.getName() != StageStatus::infinite) {
        Vector<FiniteTimeAction*> actions;
        for (int i = 0; i < _stage.getStar() and i < _stars.size(); ++i) {
            actions.pushBack(DelayTime::create(1.0));
            actions.pushBack(CallFunc::create([&, i](){ _stars.at(i)->setTexture("star.png"); /* TODO:: SOUND EFFECT */ }));
        }
        actions.pushBack(CallFunc::create([=](){ _btnMainMenu->setTouchEnabled(true); }));
        
        auto seq = Sequence::create(actions);
        this->runAction(seq);
    }
}

void GameOverLayer::saveStatsAndUnlockNextStage() {
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














