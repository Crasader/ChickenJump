#include "GameOverLayer.h"

#include "Constants.h"
#include "MainMenuLayer.h"
#include "StageStat.h"

using namespace cocos2d;

unsigned int _score = 0;
bool _isStageClear = false;

Scene* GameOverLayer::createScene(unsigned int score, bool isStageClear)
{
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
        background->setPosition(Point(_visibleSize.width / 2 + _origin.x, _visibleSize.height / 2 + _origin.y));
        this->addChild(background);
    }

    // HighScore Label
    {
        UserDefault* d = UserDefault::getInstance();
        auto highScore = d->getIntegerForKey("HIGHSCORE", 0);
        if (_score > highScore) {
            highScore = _score;
            d->setIntegerForKey("HIGHSCORE", highScore);
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
        auto playItem = MenuItemImage::create("retry.png", "retryclicked.png",
                                              CC_CALLBACK_1(GameOverLayer::gotoGamePlayLayer, this));
        playItem->setPosition(Point(_visibleSize.width / 2 + _origin.x, _visibleSize.height * 0.42 + _origin.y));
        auto menu = Menu::create(playItem, NULL);
        menu->setPosition(Point::ZERO);
        this->addChild(menu);
    }

    
    return true;
}

void GameOverLayer::gotoGamePlayLayer(cocos2d::Ref* sender)
{
    auto scene = MainMenuLayer::createScene();
    Director::getInstance()->replaceScene(TransitionFade::create(TRANSITION_TIME, scene));
}












