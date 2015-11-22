#include "MainMenuLayer.h"

#include "Constants.h"
#include "GameLayer.h"

using namespace cocos2d;

Scene* MainMenuLayer::createScene()
{
    auto scene = Scene::create();
    
    MainMenuLayer *layer = MainMenuLayer::create();

    scene->addChild(layer);

    return scene;
}

// on "init" you need to initialize your instance
bool MainMenuLayer::init()
{
    // 1. super init first
    if ( !Layer::init() ) {
        return false;
    }
    
    // 2. origin & window size
    _origin = Director::getInstance()->getVisibleOrigin();
    _visibleSize = Director::getInstance()->getVisibleSize();
    
    // Add background
    {
        auto background = Sprite::create("bg.png");
        background->setPosition(Point(_visibleSize.width / 2 + _origin.x, _visibleSize.height / 2 + _origin.y));
        this->addChild(background);
    }
    
    // Play Menu Item
    {
        Label* selectLevel = Label::createWithTTF("Select Level", font, _visibleSize.height * SCORE_FONT_SIZE);
        if (selectLevel) {
            selectLevel->setColor(Color3B::WHITE);
            selectLevel->setPosition(_visibleSize.width * 0.5, _visibleSize.height * 0.85);
            this->addChild(selectLevel);
        }
    }
    
    // Select Levels
    {
        MenuItem* france = MenuItemImage::create("france.png", "france.png", CC_CALLBACK_1(MainMenuLayer::menuSelectFrance, this));
        MenuItem* england = MenuItemImage::create("england.png", "england.png", CC_CALLBACK_1(MainMenuLayer::menuSelectEngland, this));
        MenuItem* spain = MenuItemImage::create("spain.png", "spain.png", CC_CALLBACK_1(MainMenuLayer::menuSelectSpain, this));
        MenuItem* italy = MenuItemImage::create("italy.png", "italy.png", CC_CALLBACK_1(MainMenuLayer::menuSelectItaly, this));
        MenuItem* germany = MenuItemImage::create("germany.png", "germany.png", CC_CALLBACK_1(MainMenuLayer::menuSelectGermany, this));
        MenuItem* netherlands = MenuItemImage::create("netherlands.png", "netherlands.png", CC_CALLBACK_1(MainMenuLayer::menuSelectNetherlands, this));
        
        Menu* menu = Menu::create(france, england, spain, NULL);
        Menu* menu2 = Menu::create(italy, germany, netherlands, NULL);

        menu->alignItemsHorizontallyWithPadding(25);
        menu2->alignItemsHorizontallyWithPadding(25);
        
        menu->setPosition(_visibleSize.width * 0.5, _visibleSize.height * 0.6);
        menu2->setPosition(_visibleSize.width * 0.5, _visibleSize.height * 0.3);

        this->addChild(menu);
        this->addChild(menu2);
    }
    
    
    return true;
}

void MainMenuLayer::gotoGamePlayLayer(cocos2d::Ref* sender)
{
    auto scene = GameLayer::createScene();
    Director::getInstance()->replaceScene(TransitionFade::create(TRANSITION_TIME, scene));
}



static Size smallResource  = Size(480, 320); // "iphone"
static Size mediumResource = Size(1024, 768); // "ipad"
static Size largeResource  = Size(2048, 1536); // "ipadhd"
static Size designResolution = Size(480, 320);

void MainMenuLayer::menuSelectFrance(cocos2d::Ref* sender) {
    selectLevel("france");
    gotoGamePlayLayer(this);
}

void MainMenuLayer::menuSelectEngland(cocos2d::Ref* sender) {
    selectLevel("england");
    gotoGamePlayLayer(this);
}

void MainMenuLayer::menuSelectSpain(cocos2d::Ref* sender) {
    selectLevel("spain");
    gotoGamePlayLayer(this);
}

void MainMenuLayer::menuSelectItaly(cocos2d::Ref* sender) {
    selectLevel("italy");
    gotoGamePlayLayer(this);
}

void MainMenuLayer::menuSelectGermany(cocos2d::Ref *sender) {
    selectLevel("germany");
    gotoGamePlayLayer(this);
}

void MainMenuLayer::menuSelectNetherlands(cocos2d::Ref *sender) {
    selectLevel("netherlands");
    gotoGamePlayLayer(this);
}

void MainMenuLayer::selectLevel(std::string level) {
    Size screenSize = Director::getInstance()->getOpenGLView()->getFrameSize();
    std::vector<std::string> searchPaths;
    
    if (screenSize.height > mediumResource.height) {
        searchPaths.push_back("resource_hd2");
        searchPaths.push_back("resource_hd2/" + level);
    }
    else if (screenSize.width > smallResource.width) {
        searchPaths.push_back("resource_hd");
        searchPaths.push_back("resource_hd/" + level);
    }
    else {
        searchPaths.push_back("resource_sd");
        searchPaths.push_back("resource_sd/" + level);
    }
    auto fileUtils = FileUtils::getInstance();
    fileUtils->setSearchPaths(searchPaths);
    
}



