#include "GameOverLayer.h"

#include "Constants.h"
#include "MainMenuLayer.h"
#include "Stage.h"
#include "StageStatus.h"

using namespace cocos2d;

unsigned int _score = 0;
bool _isStageClear = false;
Stage _stage;

Scene* GameOverLayer::createScene(unsigned int score, Stage& stage, bool isStageClear)
{
    _stage = stage;
    _score = score;
    _isStageClear = isStageClear;
    
    auto scene = Scene::create();
    
    GameOverLayer *layer = GameOverLayer::create();

    scene->addChild(layer);

    return scene;
}

// on "init" you need to initialize your instance
bool GameOverLayer::init()
{
    // 1. super init first
    if ( !Layer::init() ) {
        return false;
    }
    
    // 2. origin & window size
    _origin = Director::getInstance()->getVisibleOrigin();
    _visibleSize = Director::getInstance()->getVisibleSize();
    
    
    // Background
    {
        auto background = Sprite::create("blank.png");
        if (not background) { retain(); }
        background->setPosition(Point(_visibleSize.width / 2 + _origin.x, _visibleSize.height / 2 + _origin.y));
        this->addChild(background);
    }

    // HighScore Label
    {
        UserDefault* d = UserDefault::getInstance();
        auto highScore = d->getIntegerForKey(HIGHSCORE, 0);
        if (_score > highScore) {
            highScore = _score;
            d->setIntegerForKey(HIGHSCORE, highScore);
            d->flush();
        }
        std::string highScoreStr = String::createWithFormat("HighScore: %d", highScore)->getCString();
        Label* highScoreLabel = Label::createWithTTF(highScoreStr, font, _visibleSize.height * SCORE_FONT_SIZE);
        if (highScoreLabel) {
            highScoreLabel->setColor(Color3B::WHITE);
            highScoreLabel->setPosition(_visibleSize.width / 2 + _origin.x, _visibleSize.height * 0.88 + _origin.y);
            this->addChild(highScoreLabel, BackgroundLayer::layerChicken);
        }        
    }

    // Score Label
    {
        std::string scoreStr = String::createWithFormat("Score: %d", _score)->getCString();
        Label* scoreLabel = Label::createWithTTF(scoreStr, font, _visibleSize.height * SCORE_FONT_SIZE);
        if (scoreLabel) {
            scoreLabel->setColor(Color3B::WHITE);
            scoreLabel->setPosition(_visibleSize.width / 2 + _origin.x, _visibleSize.height * 0.7 + _origin.y);
            this->addChild(scoreLabel, BackgroundLayer::layerChicken);
        }
    }

    // Retry Menu Item
    {
        auto retryItem = MenuItemImage::create("retry.png", "retryclicked.png",
                                               CC_CALLBACK_1(GameOverLayer::gotoMainMenuLayer, this));
        if (not retryItem) { retain(); }
        retryItem->setPosition(Point(_visibleSize.width / 2 + _origin.x, _visibleSize.height * 0.42 + _origin.y));
        auto menu = Menu::create(retryItem, NULL);
        menu->setPosition(Point::ZERO);
        this->addChild(menu);
    }
    
    // Save StageStat and unlock next stage
    {
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

    return true;
}

void GameOverLayer::gotoMainMenuLayer(cocos2d::Ref* sender)
{
    auto scene = MainMenuLayer::createScene();
    Director::getInstance()->replaceScene(TransitionFade::create(TRANSITION_TIME, scene));
}












