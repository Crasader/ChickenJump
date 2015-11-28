#include "HomeLayer.h"
#include "Constants.h"
#include "MainMenuLayer.h"
#include "FileOperation.h"
#include "StageStat.h"

using namespace cocos2d;

Scene* HomeLayer::createScene()
{
    auto scene = Scene::create();
    auto layer = HomeLayer::create();
    scene->addChild(layer);

    return scene;
}

bool HomeLayer::init()
{
    if ( !Layer::init() )
    {
        return false;
    }
    
    _origin = Director::getInstance()->getVisibleOrigin();
    _visibleSize = Director::getInstance()->getVisibleSize();
    
    // Background
    addBackground();
    
    // Ground
    addGround();
    
    // Retry Menu Item
    addPlayMenu();
    
    UserDefault* ud = UserDefault::getInstance();
    if (ud->getBoolForKey(FIRST_TIME, true)) {
        writeFreshStageStats();

        // Set default value FIRST_TIME to false
        ud->setBoolForKey(FIRST_TIME, false);
        ud->flush();
    }

    {   // TEST TO SEE FILE WRITE IN ANDROID
        FileOperation fo;
        Label* label1 = Label::createWithTTF(fo.getFilePath(), font, _visibleSize.height * 0.04);
        if (label1) {
            label1->setColor(Color3B::WHITE);
            label1->setPosition(_visibleSize.width * 0.5, 20);
            this->addChild(label1, BackgroundLayer::layerChicken);
        }
        
        Label* label2 = Label::createWithTTF(StringUtils::format("===== %lu", fo.readFile().size()), font, _visibleSize.height * 0.04);
        if (label2) {
            label2->setColor(Color3B::WHITE);
            label2->setPosition(_visibleSize.width * 0.5, 40);
            this->addChild(label2, BackgroundLayer::layerChicken);
        }
        
    }

    return true;
}

void HomeLayer::addBackground() {
    auto background = Sprite::create("home_bg.png");
    if (not background) { retain(); }
    background->setPosition(Point(_visibleSize.width / 2 + _origin.x, _visibleSize.height / 2 + _origin.y));
    this->addChild(background, BackgroundLayer::layerBackground);
}

void HomeLayer::addGround() {
    auto ground = Sprite::create("home_ground.png");
    if (not ground) { return; }
    ground->setPosition(Point(_visibleSize.width / 2 + _origin.x, _visibleSize.height / 2 + _origin.y));
    this->addChild(ground, BackgroundLayer::layerGround);
}

void HomeLayer::addPlayMenu() {
    auto playItem = MenuItemImage::create("btn_play.png", "btn_playclicked.png",
                                          CC_CALLBACK_1(HomeLayer::gotoMainMenuLayer, this));
    if (not playItem) { return; }
    playItem->setPosition(Point(_visibleSize.width / 2 + _origin.x, _visibleSize.height * 0.42 + _origin.y));
    auto menu = Menu::create(playItem, NULL);
    menu->setPosition(Point::ZERO);
    this->addChild(menu, BackgroundLayer::layerChicken);
    
}

void HomeLayer::writeFreshStageStats() {
    try {
        CCLOG("Writing fresh stage stats");
        std::vector<StageStat> stageStats = { StageStat("france", "france.png", 0, 0, true),
            StageStat("germany", "germany.png", 0, 0, true),
            StageStat("england", "england.png", 0, 0, true),
            StageStat("italy", "italy.png", 0, 0, true),
            StageStat("spain", "spain.png", 0, 0, true),
            StageStat("netherlands", "netherlands.png", 0, 0, true) };
        
        // Save fresh StageStats
        FileOperation fo;
        fo.saveFile(stageStats);
    }
    catch(...) {
        CCLOG("Error while writing fresh stage stats");
    }
}

void HomeLayer::gotoMainMenuLayer(cocos2d::Ref* sender)
{
    auto scene = MainMenuLayer::createScene();
    Director::getInstance()->replaceScene(TransitionFade::create(TRANSITION_TIME, scene));
}
