#include "GameOverLayer.h"

#include "Constants.h"
#include "MainMenuLayer.h"
#include "Stage.h"
#include "StageStatus.h"

using namespace cocos2d;

unsigned int _score = 0;
bool _isStageClear = false;
static Stage _stage;

void GameOverLayer::prepare(unsigned int score, Stage& stage, bool isStageClear)
{
    _stage = stage;
    _score = score;
    _isStageClear = isStageClear;
    
    addHighscoreLabel();
    addScoreLabel();
    addRetryMenu();
    saveStatsAndUnlockNextStage();
}

// on "init" you need to initialize your instance
bool GameOverLayer::init()
{
    if ( !LayerColor::initWithColor(Color4B(0, 0, 0, 128)) ) {
        return false;
    }
    
    // 2. origin & window size
    _origin = Director::getInstance()->getVisibleOrigin();
    _visibleSize = Director::getInstance()->getVisibleSize();
    
    this->setContentSize(Size(_visibleSize.width, _visibleSize.height));
    this->setPosition(0, 0);

    // Background
//    {
//        auto background = Sprite::create("blank.png");
//        if (not background) { return false; }
//        background->setPosition(Point(_visibleSize.width / 2 + _origin.x, _visibleSize.height / 2 + _origin.y));
//        this->addChild(background);
//    }
    
    // Save StageStat and unlock next stage

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

void GameOverLayer::addRetryMenu() {
    auto retryItem = MenuItemImage::create("btn_menu.png", "btn_menu.png",
                                           CC_CALLBACK_1(GameOverLayer::gotoMainMenuLayer, this));
    if (not retryItem) { return; }
    retryItem->setPosition(Point(_visibleSize.width / 2 + _origin.x, _visibleSize.height * 0.42 + _origin.y));
    auto menu = Menu::create(retryItem, NULL);
    menu->setPosition(Point::ZERO);
    this->addChild(menu);
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

void GameOverLayer::gotoMainMenuLayer(cocos2d::Ref* sender)
{
    auto scene = MainMenuLayer::createScene();
    Director::getInstance()->replaceScene(TransitionFade::create(TRANSITION_TIME, scene));
}












