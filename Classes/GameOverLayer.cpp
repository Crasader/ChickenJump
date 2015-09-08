#include "GameOverLayer.h"

#include "Constants.h"
#include "GameLayer.h"

using namespace cocos2d;

unsigned int _score;

Scene* GameOverLayer::createScene(unsigned int score)
{
    _score = score;
    
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    GameOverLayer *layer = GameOverLayer::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
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
        Label* highScoreLabel = Label::createWithTTF(highScoreStr, "Marker Felt.ttf", _visibleSize.height * SCORE_FONT_SIZE);
        if (highScoreLabel) {
            highScoreLabel->setColor(Color3B::WHITE);
            highScoreLabel->setPosition(_visibleSize.width / 2 + _origin.x, _visibleSize.height * 0.88 + _origin.y);
            this->addChild(highScoreLabel, BackgroundLayer::layerChicken);
        }
    }

    // Score Label
    {
        std::string scoreStr = String::createWithFormat("Score: %d", _score)->getCString();
        Label* scoreLabel = Label::createWithTTF(scoreStr, "Marker Felt.ttf", _visibleSize.height * SCORE_FONT_SIZE);
        if (scoreLabel) {
            scoreLabel->setColor(Color3B::WHITE);
            scoreLabel->setPosition(_visibleSize.width / 2 + _origin.x, _visibleSize.height * 0.7 + _origin.y);
            this->addChild(scoreLabel, BackgroundLayer::layerChicken);
        }
    }

    // Play Menu Item
    {
        auto playItem = MenuItemImage::create("retry.png", "retryclicked.png",
                                              CC_CALLBACK_1(GameOverLayer::gotoGamePlayLayer, this));
        playItem->setPosition(Point(_visibleSize.width / 2 + _origin.x, _visibleSize.height * 0.42 + _origin.y));
        auto menu = Menu::create(playItem, NULL);
        menu->setPosition(Point::ZERO);
        this->addChild(menu);
    }
    
    // Country toggle
    {
        MenuItem* france = MenuItemImage::create("france.png", "france.png");
        MenuItem* england = MenuItemImage::create("england.png", "england.png");
        MenuItemToggle* countryToggleItem = MenuItemToggle::createWithCallback(CC_CALLBACK_1(GameOverLayer::toggleCountry, this), france, england, NULL);
        Menu* countryToggleMenu = Menu::create(countryToggleItem, NULL);
        countryToggleMenu->setPosition(Vec2(_visibleSize.width / 2, countryToggleItem->getContentSize().height + 10));
        this->addChild(countryToggleMenu);
        
        toggleCountry(this);
    }

    
    return true;
}

void GameOverLayer::gotoGamePlayLayer(cocos2d::Ref* sender)
{
    auto scene = GameLayer::createScene();
    Director::getInstance()->replaceScene(TransitionFade::create(TRANSITION_TIME, scene));
}

static Size smallResource  = Size(480, 320); // "iphone"
static Size mediumResource = Size(1024, 768); // "ipad"
static Size largeResource  = Size(2048, 1536); // "ipadhd"
static Size designResolution = Size(480, 320);

void GameOverLayer::toggleCountry(cocos2d::Ref* sender) {
    _countryFrance = !_countryFrance;
    CCLOG("Country Selected: %s", _countryFrance? "France":"England");
    
    // Handling different screen size
    {
        Size screenSize = Director::getInstance()->getOpenGLView()->getFrameSize();
        std::vector<std::string> searchPaths;
        if (screenSize.height > mediumResource.height) {
            CCLOG("MainMenu:path: ipadhd");
            if (_countryFrance) {
                searchPaths.push_back("ipadhd");
                searchPaths.push_back("ipadhd/france");
            }
            else {
                searchPaths.push_back("ipadhd");
                searchPaths.push_back("ipadhd/england");
            }
        }
        else if (screenSize.width > smallResource.width) {
            CCLOG("MainMenu:path: ipad");
            if (_countryFrance) {
                searchPaths.push_back("ipad");
                searchPaths.push_back("ipad/france");
            }
            else {
                searchPaths.push_back("ipad");
                searchPaths.push_back("ipad/england");
            }        }
        else {
            CCLOG("MainMenu:path: iphone");
            if (_countryFrance) {
                searchPaths.push_back("iphone");
                searchPaths.push_back("iphone/france");
            }
            else {
                searchPaths.push_back("iphone");
                searchPaths.push_back("iphone/england");
            }
        }
        auto fileUtils = FileUtils::getInstance();
        fileUtils->setSearchPaths(searchPaths);
    }
    
}













