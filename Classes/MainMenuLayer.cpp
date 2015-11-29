#include "MainMenuLayer.h"

#include "Constants.h"
#include "GameLayer.h"
#include "Stage.h"
#include "StageStatus.h"

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
    addBackground();
    
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
        std::vector<Stage> stages = StageStatus::getStage();
        
        Vector<MenuItem*> menuItems;
        for (uint8_t i = 0; i < stages.size(); ++i) {
            auto menuItem = MenuItemImage::create(stages.at(i).getImageFile(), stages.at(i).getImageFile(),
                                                  CC_CALLBACK_1(MainMenuLayer::menuSelectSgate, this, stages.at(i)));
            if (not stages.at(i).isUnlocked()) {
                menuItem->setOpacity(90);
                menuItem->setEnabled(false);
            }
            menuItems.pushBack(menuItem);
        }

        Menu* menu = Menu::createWithArray(menuItems);
        menu->alignItemsInColumns(3, 3, NULL);
        this->addChild(menu);
    }

    return true;
}

void MainMenuLayer::addBackground() {
    auto background = Sprite::create("home_bg.png");
    if (not background) { return; }
    background->setPosition(Point(_visibleSize.width / 2 + _origin.x, _visibleSize.height / 2 + _origin.y));
    this->addChild(background);
}

void MainMenuLayer::gotoGamePlayLayer(cocos2d::Ref* sender, Stage& stage)
{
    auto scene = GameLayer::createScene(stage);
    Director::getInstance()->replaceScene(TransitionFade::create(TRANSITION_TIME, scene));
}


static Size smallResource  = Size(480, 320); // "small"
static Size mediumResource = Size(1024, 768); // "mid"
static Size largeResource  = Size(2048, 1536); // "big"
static Size designResolution = Size(480, 320);

void MainMenuLayer::menuSelectSgate(cocos2d::Ref* sender, Stage& stage) {
    selectLevel(stage.getName());
    gotoGamePlayLayer(this, stage);
}

void MainMenuLayer::selectLevel(std::string stage) {
    Size screenSize = Director::getInstance()->getOpenGLView()->getFrameSize();
    std::vector<std::string> searchPaths;
    
    if (screenSize.height > mediumResource.height) {
        searchPaths.push_back("resource_hd2");
        searchPaths.push_back("resource_hd2/" + stage);
    }
    else if (screenSize.width > smallResource.width) {
        searchPaths.push_back("resource_hd");
        searchPaths.push_back("resource_hd/" + stage);
    }
    else {
        searchPaths.push_back("resource_sd");
        searchPaths.push_back("resource_sd/" + stage);
    }
    FileUtils::getInstance()->setSearchPaths(searchPaths);
    
}



