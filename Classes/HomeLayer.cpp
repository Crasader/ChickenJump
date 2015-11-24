#include "HomeLayer.h"
#include "Constants.h"
#include "MainMenuLayer.h"

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

void HomeLayer::gotoMainMenuLayer(cocos2d::Ref* sender)
{
    auto scene = MainMenuLayer::createScene();
    Director::getInstance()->replaceScene(TransitionFade::create(TRANSITION_TIME, scene));
}
