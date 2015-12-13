#include "HomeLayer.h"
#include "Constants.h"
#include "MainMenuLayer.h"
#include "SimpleAudioEngine.h"
#include "StageStatus.h"

using namespace cocos2d;

const std::string imageHomeBackground = "home_bg.png";
const std::string imageGroundBackground = "home_ground.png";
const std::string imageBtnPlay = "btn_play.png";
const std::string imageBtnPlayClicked = "btn_playclicked.png";
const std::string imageLogo = "logo.png";
const std::string imageSnowflake = "snowflake.png";

Scene* HomeLayer::createScene()
{
    auto scene = Scene::createWithPhysics();
    auto layer = HomeLayer::create();
    scene->addChild(layer);

    {   // Settings HUD
        SettingsMenuLayer* settingsHUD = SettingsMenuLayer::create();
        scene->addChild(settingsHUD);
        layer->_settingsHUD = settingsHUD;
    }

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
    
    // Logo
    addLogo();
    
    // Ground
    addGround();
    
    // Retry Menu Item
    addPlayMenu();
    
    // Create StageStatus if its first time
    initStage();
    
    // Add flying chickens
    addFlyingChickens();
    
    {
        // Snow Effect
        ParticleSnow* explosion = ParticleSnow::create();
        explosion->setTexture(TextureCache::getInstance()->addImage(imageSnowflake));
        explosion->setPosition(_visibleSize.width * 0.5, _visibleSize.height);
        this->addChild(explosion, BackgroundLayer::layerTouch);
    }
    
    this->scheduleUpdate();

    return true;
}

void HomeLayer::addBackground() {
    auto background = Sprite::create(imageHomeBackground);
    if (not background) { retain(); }
    background->setPosition(Point(_visibleSize.width / 2 + _origin.x, _visibleSize.height / 2 + _origin.y));
    this->addChild(background, BackgroundLayer::layerBackground);
}

void HomeLayer::addFlyingChickens() {
    _flyingChicken1 = new FloatingChicken();
    _flyingChicken2 = new FloatingChicken();
    _flyingChicken4 = new FloatingChicken();
    
    Vec2 initialPosition1 = Vec2(_visibleSize.width * -0.20, 0.0);
    Vec2 initialPosition2 = Vec2(_visibleSize.width * 0.60, 0.0);
    Vec2 initialPosition4 = Vec2(_visibleSize.width * 0.70, 0.0);

    _flyingChicken1->createFloatingChicken(this, initialPosition1, AnimationType::fly_lefttoright_high);
    _flyingChicken2->createFloatingChicken(this, initialPosition2, AnimationType::fly_lefttoright_mid);
    _flyingChicken4->createFloatingChicken(this, initialPosition4, AnimationType::fly_righttoleft_mid);
}

void HomeLayer::addGround() {
    auto ground = Sprite::create(imageGroundBackground);
    if (not ground) { return; }
    ground->setPosition(Point(_visibleSize.width * 0.5 + _origin.x, _visibleSize.height * 0.5 + _origin.y));
    this->addChild(ground, BackgroundLayer::layerTouch);
}

void HomeLayer::addLogo() {
    auto logo = Sprite::create(imageLogo);
    if (not logo) { return; }
    logo->setColor(Color3B(255, 208, 66));
    logo->setPosition(Point(_visibleSize.width * 0.5 + _origin.x, _visibleSize.height * 0.7 + _origin.y));
    this->addChild(logo, BackgroundLayer::layerTouch);
}

void HomeLayer::addPlayMenu() {
    auto playItem = MenuItemImage::create(imageBtnPlay, imageBtnPlayClicked,
                                          CC_CALLBACK_1(HomeLayer::gotoMainMenuLayer, this));
    if (not playItem) { return; }
    playItem->setPosition(Point(_visibleSize.width / 2 + _origin.x, _visibleSize.height * 0.30 + _origin.y));
    auto menu = Menu::create(playItem, NULL);
    menu->setPosition(Point::ZERO);
    this->addChild(menu, BackgroundLayer::layerTouch);
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
    if (_flyingChicken4) { _flyingChicken4->update(dt); }
}









