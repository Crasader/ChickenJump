#include "MainMenuLayer.h"

#include "Constants.h"
#include "GameLayer.h"
#include "FileOperation.h"

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
        FileOperation fo;
        std::vector<StageStat> stageStats = fo.readFile();
        
        Vector<MenuItem*> menuItems;
        for (uint8_t i = 0; i < stageStats.size(); ++i) {
            auto menuItem = MenuItemImage::create(stageStats.at(i).getImageFile(), stageStats.at(i).getImageFile(),
                                                  CC_CALLBACK_1(MainMenuLayer::menuSelectSgate, this, stageStats.at(i)));
            if (stageStats.at(i).isLocked()) {
                menuItem->setOpacity(90);
            }
            menuItems.pushBack(menuItem);
        }

        Menu* menu = Menu::createWithArray(menuItems);
        menu->alignItemsInColumns(3, 3, NULL);
        this->addChild(menu);

        
//        {   // DUBUG
//            Label* l1 = Label::createWithTTF(StringUtils::format("path: %s", fo.getFilePath().c_str()), font, _visibleSize.height * 0.04);
//            l1->setColor(Color3B::BLUE);
//            l1->setPosition(10, 10);
//            this->addChild(l1, BackgroundLayer::layerGround);
//            
//            Label* l2 = Label::createWithTTF(StringUtils::format("vsize: %lu", stageStats.size()), font, _visibleSize.height * 0.04);
//            l2->setColor(Color3B::BLUE);
//            l2->setPosition(10, 40);
//            this->addChild(l2, BackgroundLayer::layerGround);
//        }
    }

    return true;
}

void MainMenuLayer::addBackground() {
    auto background = Sprite::create("home_bg.png");
    if (not background) { return; }
    background->setPosition(Point(_visibleSize.width / 2 + _origin.x, _visibleSize.height / 2 + _origin.y));
    this->addChild(background);
}

void MainMenuLayer::gotoGamePlayLayer(cocos2d::Ref* sender, StageStat& stage)
{
    auto scene = GameLayer::createScene(stage);
    Director::getInstance()->replaceScene(TransitionFade::create(TRANSITION_TIME, scene));
}


static Size smallResource  = Size(480, 320); // "small"
static Size mediumResource = Size(1024, 768); // "mid"
static Size largeResource  = Size(2048, 1536); // "big"
static Size designResolution = Size(480, 320);

void MainMenuLayer::menuSelectSgate(cocos2d::Ref* sender, StageStat& stage) {
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



