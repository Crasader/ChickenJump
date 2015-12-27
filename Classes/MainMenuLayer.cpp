#include "MainMenuLayer.h"

#include "Constants.h"
#include "GameLayer.h"
#include "Stage.h"
#include "StageStatus.h"

#include <UILayout.h>
#include <UIPageView.h>
#include <UIListView.h>

#include <UIButton.h>
#include <UIWidget.h>

using namespace cocos2d;

static Vec2 normalizedPosition = Vec2(-0.45, -0.0);

const std::string imageHomeBackground = "home_bg.png";

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
    if ( !Layer::init() ) {
        return false;
    }
    
    _origin = Director::getInstance()->getVisibleOrigin();
    _visibleSize = Director::getInstance()->getVisibleSize();
    
    // Add background
    addBackground();
    
    // Select Stage Label
    addHeaderLabel();
    
    // Stages
    addStages();
    
    addBackButton();
    
    return true;
}

void MainMenuLayer::addBackButton()     {
    _backButton = new BackButton<HomeLayer>();
    _backButton->createBackButton(this);
    _backButton->setPosition(Vec2(_visibleSize.width * 0.04, _visibleSize.height * 0.15));
}

void MainMenuLayer::addBackground() {
    auto background = Sprite::create(imageHomeBackground);
    if (not background) { return; }
    background->setPosition(Point(_visibleSize.width / 2 + _origin.x, _visibleSize.height / 2 + _origin.y));
    this->addChild(background);
}

void MainMenuLayer::addHeaderLabel()     {
    Label* selectLavel = Label::createWithTTF("Select Stage", font, _visibleSize.height * SCORE_FONT_SIZE);
    if (selectLavel) {
        selectLavel->setColor(Color3B::WHITE);
        selectLavel->setPosition(_visibleSize.width * 0.5, _visibleSize.height * 0.85);
        this->addChild(selectLavel);
    }
}

void MainMenuLayer::addStages() {
    // Page 1
    std::vector<Stage> stages = StageStatus::getStage();
    
    Vector<Button*> menuItems;
    for (uint8_t i = 0; i < stages.size(); ++i) {
        auto btn = Button::create(stages.at(i).isUnlocked() ? stages.at(i).getImageFile() : stages.at(i).getLockedImageFile(),
                                  stages.at(i).getClickedImageFile());
        btn->addTouchEventListener(CC_CALLBACK_1(MainMenuLayer::menuSelectSgate, this, stages.at(i)));
        
        if (not stages.at(i).isUnlocked()) {
            btn->setEnabled(false);
        }
        menuItems.pushBack(btn);
    }
    
    ListView* page1menuList;
    ListView* menuList1;
    ListView* menuList2;
    int horizontalMargin = 40;
    int verticalMargin = 20;
    {
        {
            menuList1 = ListView::create();
            menuList1->setGravity(ui::ListView::Gravity::CENTER_HORIZONTAL);
            menuList1->setDirection(cocos2d::ui::ScrollView::Direction::HORIZONTAL);
            menuList1->setItemsMargin(horizontalMargin);
            menuList1->setSize(Size(menuItems.at(0)->getContentSize().width * 3 + (horizontalMargin*2), menuItems.at(0)->getContentSize().height));
            
            menuList1->pushBackCustomItem(menuItems.at(0));
            menuList1->pushBackCustomItem(menuItems.at(1));
            menuList1->pushBackCustomItem(menuItems.at(2));
        }
        {
            menuList2 = ListView::create();
            menuList2->setGravity(ui::ListView::Gravity::CENTER_HORIZONTAL);
            menuList2->setDirection(cocos2d::ui::ScrollView::Direction::HORIZONTAL);
            menuList2->setItemsMargin(horizontalMargin);
            menuList2->setSize(Size(menuItems.at(0)->getContentSize().width * 3 + (horizontalMargin*2), menuItems.at(0)->getContentSize().height));
            
            menuList2->pushBackCustomItem(menuItems.at(3));
            menuList2->pushBackCustomItem(menuItems.at(4));
            menuList2->pushBackCustomItem(menuItems.at(5));
        }

        page1menuList = ListView::create();
        page1menuList->setGravity(ui::ListView::Gravity::CENTER_VERTICAL);
        page1menuList->setDirection(cocos2d::ui::ScrollView::Direction::VERTICAL);
        page1menuList->setItemsMargin(verticalMargin);
        page1menuList->setSize(Size(menuList1->getContentSize().width, menuList1->getContentSize().height * 2 + verticalMargin));
        page1menuList->setPosition(Vec2((_visibleSize.width - page1menuList->getContentSize().width) * 0.5, 0));
        page1menuList->pushBackCustomItem(menuList1);
        page1menuList->pushBackCustomItem(menuList2);
    }
    
    // Page 2
    ListView* page2menuList;
    {
        page2menuList = ListView::create();
        page2menuList->setGravity(ui::ListView::Gravity::CENTER_HORIZONTAL);
        page2menuList->setDirection(cocos2d::ui::ScrollView::Direction::HORIZONTAL);
        page2menuList->setItemsMargin(horizontalMargin);
        page2menuList->setSize(Size(menuItems.at(6)->getContentSize().width * 3 + (horizontalMargin*2), menuItems.at(0)->getContentSize().height * 2 + verticalMargin));
        page2menuList->setPosition(Vec2((_visibleSize.width - page2menuList->getContentSize().width) * 0.5, 0));
        page2menuList->pushBackCustomItem(menuItems.at(6));
    }
    
    Layout* page1 = Layout::create();
    page1->addChild(page1menuList);
//    page1->setBackGroundImage("home_bg.png");
    
    Layout* page2 = Layout::create();
    page2->addChild(page2menuList);
//    page2->setBackGroundImage("home_bg.png");
    
    PageView* pageView = PageView::create();
//    pageView->setBackGroundImage("home_bg.png");
    pageView->setContentSize(Size(_visibleSize.width, _visibleSize.height * 0.6));
    pageView->setAnchorPoint(Vec2(0.5f, 0.5f));
    pageView->setPosition(Vec2(_visibleSize.width/2, _visibleSize.height/2));
    pageView->insertPage(page1, 0);
    pageView->insertPage(page2, 1);
    
    this->addChild(pageView);
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

void MainMenuLayer::gotoGamePlayLayer(cocos2d::Ref* sender, Stage& stage)
{
    auto scene = GameLayer::createScene(stage);
    Director::getInstance()->replaceScene(TransitionFade::create(TRANSITION_TIME, scene));
}


