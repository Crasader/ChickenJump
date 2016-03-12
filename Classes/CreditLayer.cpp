#include "CreditLayer.h"

#include <UIListView.h>
#include <UIText.h>

#include "Constants.h"
#include "HomeLayer.h"

using namespace cocos2d;
using namespace ui;

static const std::string imageHomeBackground = "home_bg.png";
static const std::string imageGroundBackground = "home_ground.png";
static const std::string imageBtnBack = "btn_back.png";
static const std::string imageBtnBackClicked = "btn_backclicked.png";

Scene* CreditLayer::createScene()
{
    auto scene = Scene::create();
    auto layer = CreditLayer::create();
    scene->addChild(layer);
    
    // add Score HUD
    {
        CreditHUD* creditHUD = CreditHUD::create();
        scene->addChild(creditHUD);
        layer->_creditHUD = creditHUD;
    }
    
    return scene;
}


bool CreditLayer::init()
{
    if ( !LayerColor::initWithColor(Color4B(0, 0, 0, 192)) ) {
        return false;
    }

    _origin = Director::getInstance()->getVisibleOrigin();
    _visibleSize = Director::getInstance()->getVisibleSize();

    // Background
    addBackground();

    // Ground
    addGround();
    
    // Back Button
    addBackButton();
    
    
    return true;
}

void CreditLayer::addBackground() {
    auto background = Sprite::create(imageHomeBackground);
    if (not background) { retain(); }
    background->setPosition(Point(_visibleSize.width * 0.5, _visibleSize.height * 0.5));
    this->addChild(background, BackgroundLayer::layerBackground);
}

void CreditLayer::addGround() {
    auto ground = Sprite::create(imageGroundBackground);
    if (not ground) { return; }
    ground->setPosition(Point(_visibleSize.width * 0.5, _visibleSize.height * 0.5));
    this->addChild(ground, BackgroundLayer::layerTouch);
}

void CreditLayer::addBackButton() {
    auto backItem = MenuItemImage::create(imageBtnBack, imageBtnBackClicked,
                                          CC_CALLBACK_1(CreditLayer::backButtonClicked, this));
    if (not backItem) { return; }
    backItem->setPosition(Point(_visibleSize.width * 0.04, _visibleSize.height * 0.12));
    auto menu = Menu::create(backItem, NULL);
    menu->setPosition(Point::ZERO);
    this->addChild(menu, BackgroundLayer::layerTouch);
}

void CreditLayer::backButtonClicked(cocos2d::Ref const* sender)
{
    auto scene = HomeLayer::createScene();
    Director::getInstance()->replaceScene(TransitionFade::create(TRANSITION_TIME, scene));
}



//
// Credit HUD
//
bool CreditHUD::init()
{
    if ( !LayerColor::initWithColor(Color4B(0, 0, 0, 128)) ) {
        return false;
    }
    
    _origin = Director::getInstance()->getVisibleOrigin();
    _visibleSize = Director::getInstance()->getVisibleSize();
    
    this->setContentSize(Size(_visibleSize.width * 0.6, _visibleSize.height));
    this->setPosition(Vec2(_visibleSize.width * 0.2, 0));
    
    {
        std::string sixeyes       = "SixEyes Presents";
        std::string chickenjump   = "Chicken Jump";
        std::string developedby   = "- Developed by -";
        std::string developer_one = "Asish Biswas";
        std::string developer_two = "Farid Belhadi";
        
        auto label1 = Text::create(sixeyes, font, _visibleSize.height * CREDIT_FONT_SIZE_SMALL);
//        auto label2 = Text::create(presents, font, _visibleSize.height * SCORE_FONT_SIZE);
        auto label3 = Text::create(chickenjump, font, _visibleSize.height * CREDIT_FONT_SIZE_BIG);
        auto label4 = Text::create(developedby, font, _visibleSize.height * CREDIT_FONT_SIZE_SMALL);
        auto label5 = Text::create(developer_two, font, _visibleSize.height * CREDIT_FONT_SIZE_MID);
        auto label6 = Text::create(developer_one, font, _visibleSize.height * CREDIT_FONT_SIZE_MID);
        auto gap = Text::create(" ", font, _visibleSize.height * CREDIT_FONT_SIZE_SMALL);
        

        if (not label1 or not label3 or not label4 or not label5 or not label6) { return false; }
        label1->setColor(Color3B::WHITE);
//        label2->setColor(Color3B::WHITE);
        label3->setColor(Color3B::ORANGE);
        label4->setColor(Color3B::WHITE);
        label5->setColor(Color3B::GRAY);
        label6->setColor(Color3B::GRAY);
        
        ListView* lv = ListView::create();
        lv->pushBackCustomItem(label1);
//        lv->pushBackCustomItem(label2);
        lv->pushBackCustomItem(label3);
        lv->pushBackCustomItem(gap);
        
        lv->pushBackCustomItem(label4);
        lv->pushBackCustomItem(label5);
        lv->pushBackCustomItem(label6);
        
        lv->setGravity(ui::ListView::Gravity::CENTER_HORIZONTAL);
        lv->setItemsMargin(10);
        lv->setSize(Size(label3->getContentSize().width,
                         label3->getContentSize().height * 6 + 50));
        lv->setBackGroundColorOpacity(100);
        
        lv->setPosition(Vec2(_visibleSize.width * 0.3 - lv->getContentSize().width * 0.5, _visibleSize.height * 0));
        lv->setBounceEnabled(false);
        
        this->addChild(lv, BackgroundLayer::layerChicken);
    }
    
    
    return true;
}





