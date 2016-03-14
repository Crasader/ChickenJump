#include "MainMenuLayer.h"

#include "Constants.h"
#include "GameLayer.h"
#include "Stage.h"
#include "StageStatus.h"

#include <UILayout.h>
#include <UIListView.h>

#include <UIButton.h>
#include <UIWidget.h>

using namespace cocos2d;
using namespace ui;

static Button* btnPageScrollRight;
static Button* btnPageScrollLeft;
static bool pageScrolled = false;

static PageView* pageView;

static std::string imageBtnArrowLeft = "btn_arrowleft.png";
static std::string imageBtnArrowRight = "btn_arrowright.png";
static std::string imageMenuBackground = "menu_bg.png";
static std::string imageComingSoon = "coming_soon_bg.png";

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
    
    // Page Scroll Buttons, changes image on click
    addPageNavigationButtons();
    
    return true;
}

void MainMenuLayer::addBackButton() {
    _backButton = new BackButton<HomeLayer>();
    _backButton->createBackButton(this);
    _backButton->setPosition(Vec2(_visibleSize.width * 0.04, _visibleSize.height * 0.15));
}

void MainMenuLayer::addBackground() {
    auto background = Sprite::create(imageMenuBackground);
    if (not background) { return; }
    background->setPosition(Point(_visibleSize.width / 2 + _origin.x, _visibleSize.height / 2 + _origin.y));
    this->addChild(background);
}

void MainMenuLayer::addHeaderLabel()     {
    Label* selectLavel = Label::createWithTTF("Select Stage", font, _visibleSize.height * SCORE_FONT_SIZE_BIG);
    if (selectLavel) {
        selectLavel->setColor(Color3B::WHITE);
        selectLavel->setPosition(_visibleSize.width * 0.5, _visibleSize.height * 0.9);
        this->addChild(selectLavel);
    }
}

void MainMenuLayer::addPageNavigationButtons() {
    // Scroll Right Button
    btnPageScrollRight = Button::create(imageBtnArrowRight, imageBtnArrowRight);
    if (not btnPageScrollRight) return;
    
    btnPageScrollRight->setPosition(Vec2(_visibleSize.width * 0.95, _visibleSize.height * 0.5));
    btnPageScrollRight->addTouchEventListener(CC_CALLBACK_2(MainMenuLayer::pageScrollClicked, this));
    this->addChild(btnPageScrollRight, BackgroundLayer::layerTouch);
    
    
    // Scroll Left Button
    btnPageScrollLeft = Button::create(imageBtnArrowLeft, imageBtnArrowLeft);
    if (not btnPageScrollLeft) return;
    
    btnPageScrollLeft->setPosition(Vec2(_visibleSize.width * 0.05, _visibleSize.height * 0.5));
    btnPageScrollLeft->addTouchEventListener(CC_CALLBACK_2(MainMenuLayer::pageScrollClicked, this));
    btnPageScrollLeft->setVisible(false);
    this->addChild(btnPageScrollLeft, BackgroundLayer::layerTouch);
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
    ListView* row1;
    ListView* row2;
    int horizontalMargin = 20;
    int verticalMargin = 10;
    {
        {
            row1 = ListView::create();
            row1->setGravity(ui::ListView::Gravity::CENTER_HORIZONTAL);
            row1->setDirection(cocos2d::ui::ScrollView::Direction::HORIZONTAL);
            row1->setItemsMargin(horizontalMargin);
            row1->setSize(Size(menuItems.at(0)->getContentSize().width * 3.5 + (horizontalMargin*2.5),
                               menuItems.at(0)->getContentSize().height));
            
            row1->pushBackCustomItem(menuItems.at(0));
            row1->pushBackCustomItem(menuItems.at(1));
            row1->pushBackCustomItem(menuItems.at(2));
        }
        {
            row2 = ListView::create();
            row2->setGravity(ui::ListView::Gravity::CENTER_HORIZONTAL);
            row2->setDirection(cocos2d::ui::ScrollView::Direction::HORIZONTAL);
            row2->setItemsMargin(horizontalMargin);
            row2->setSize(Size(menuItems.at(0)->getContentSize().width * 4 + (horizontalMargin*3),
                               menuItems.at(0)->getContentSize().height));
            
            row2->pushBackCustomItem(menuItems.at(3));
            row2->pushBackCustomItem(menuItems.at(4));
            row2->pushBackCustomItem(menuItems.at(5));
            row2->pushBackCustomItem(menuItems.at(6));
        }

        page1menuList = ListView::create();
        page1menuList->setGravity(ui::ListView::Gravity::RIGHT);
        page1menuList->setDirection(cocos2d::ui::ScrollView::Direction::VERTICAL);
        page1menuList->setItemsMargin(verticalMargin);
        page1menuList->setTouchEnabled(false);
        page1menuList->setSize(Size(row2->getContentSize().width,
                                    row2->getContentSize().height * 2 + verticalMargin));
        
        page1menuList->setPosition(Vec2((_visibleSize.width - page1menuList->getContentSize().width) * 0.5,
                                        (_visibleSize.height - page1menuList->getContentSize().height) * 0.5));
        
        page1menuList->pushBackCustomItem(row1);
        page1menuList->pushBackCustomItem(row2);
    }
    
    Layout* page1 = Layout::create();
    page1->addChild(page1menuList);
    page1->setTouchEnabled(false);
    
    Layout* page2 = Layout::create();
    page2->setBackGroundImage(imageComingSoon);
    page2->setTouchEnabled(false);
    
    pageView = PageView::create();
    pageView->setContentSize(Size(_visibleSize.width, _visibleSize.height));
    pageView->setAnchorPoint(Vec2(0.5f, 0.5f));
    pageView->setPosition(Vec2(_visibleSize.width * 0.5, _visibleSize.height * 0.5));
    pageView->setTouchEnabled(false);
    
    pageView->insertPage(page1, 0);
    pageView->insertPage(page2, 1);
    
    this->addChild(pageView);
}


static Size smallResource  = Size(512, 384); // "small"
static Size mediumResource = Size(1024, 768); // "mid"
static Size largeResource  = Size(2048, 1536); // "big"

void MainMenuLayer::menuSelectSgate(cocos2d::Ref const* sender, Stage const& stage) {
    selectLevel(stage.getName());
    gotoGamePlayLayer(this, stage);
}

void MainMenuLayer::selectLevel(std::string const& stage) {
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
    CCLOG("===== Path: %s (MainMenuLayer)", searchPaths.at(0).c_str());
    FileUtils::getInstance()->setSearchPaths(searchPaths);
}

void MainMenuLayer::gotoGamePlayLayer(cocos2d::Ref const* sender, Stage const& stage)
{
    auto scene = GameLayer::createScene(stage);
    Director::getInstance()->replaceScene(TransitionFade::create(TRANSITION_TIME, scene));
}

void MainMenuLayer::pageScrollClicked(Ref const* ref, cocos2d::ui::Widget::TouchEventType const& eEventType) {
    if (eEventType != ui::Widget::TouchEventType::ENDED) { return; }

    pageScrolled = not pageScrolled;
    pageView->scrollToPage(pageScrolled); // we have only two pages: 0 and 1 ;)
    
    btnPageScrollRight->setVisible(not pageScrolled);
    btnPageScrollLeft->setVisible(pageScrolled);
}








