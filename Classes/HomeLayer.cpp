#include "HomeLayer.h"
#include "Constants.h"
#include "MainMenuLayer.h"
#include "StageStatus.h"

using namespace cocos2d;

Scene* HomeLayer::createScene()
{
    auto scene = Scene::createWithPhysics();
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
    
    // Create StageStatus if its first time
    initStage();
    
    // Add flying chickens
    addFlyingChickens();
    

    this->scheduleUpdate();

    return true;
}

void HomeLayer::addBackground() {
    auto background = Sprite::create("home_bg.png");
    if (not background) { retain(); }
    background->setPosition(Point(_visibleSize.width / 2 + _origin.x, _visibleSize.height / 2 + _origin.y));
    this->addChild(background, BackgroundLayer::layerBackground);
}

void HomeLayer::addFlyingChickens() {
    _flyingChicken1 = new FloatingChicken();
    _flyingChicken2 = new FloatingChicken();
    _flyingChicken3 = new FloatingChicken();
    _flyingChicken4 = new FloatingChicken();
    
    Vec2 initialPosition1 = Vec2(_visibleSize.width * -0.20, 0.0);
    Vec2 initialPosition2 = Vec2(_visibleSize.width * 0.60, 0.0);
    Vec2 initialPosition3 = Vec2(_visibleSize.width * 0.30, 0.0);
    Vec2 initialPosition4 = Vec2(_visibleSize.width * 0.70, 0.0);

    _flyingChicken1->createFloatingChicken(this, initialPosition1, 1, ParabolaSize::high);
    _flyingChicken2->createFloatingChicken(this, initialPosition2, 1, ParabolaSize::mid);
    _flyingChicken3->createFloatingChicken(this, initialPosition3, 1, ParabolaSize::flat);
    _flyingChicken4->createFloatingChicken(this, initialPosition4, -1, ParabolaSize::mid);
}

void HomeLayer::addGround() {
    auto ground = Sprite::create("home_ground.png");
    if (not ground) { return; }
    ground->setPosition(Point(_visibleSize.width / 2 + _origin.x, _visibleSize.height / 2 + _origin.y));
    this->addChild(ground, BackgroundLayer::layerTouch);
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

void HomeLayer::initStage() {
    UserDefault* ud = UserDefault::getInstance();
    if (ud->getBoolForKey(FIRST_TIME, true)) {
        StageStatus::createFreshStages();
        
        // Set default value FIRST_TIME to false
        ud->setBoolForKey(FIRST_TIME, false);
        ud->flush();
    }
}

void HomeLayer::update(float dt) {
    if (_flyingChicken1) { _flyingChicken1->update(dt); }
    if (_flyingChicken2) { _flyingChicken2->update(dt); }
    if (_flyingChicken3) { _flyingChicken3->update(dt); }
    if (_flyingChicken4) { _flyingChicken4->update(dt); }
}









