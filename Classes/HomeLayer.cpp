#include "HomeLayer.h"
#include "Constants.h"
#include "MainMenuLayer.h"
#include "SimpleAudioEngine.h"
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
        explosion->setTexture(TextureCache::getInstance()->addImage("snowflake.png"));
        explosion->setPosition(_visibleSize.width * 0.5, _visibleSize.height);
        this->addChild(explosion, BackgroundLayer::layerTouch);
    }
    
    {
        float currentSoundSettings = UserDefault::getInstance()->getFloatForKey(VOLUME, 1.0f);
        MenuItem* mute = MenuItemImage::create("mute.png", "mute.png");
        MenuItem* unmute = MenuItemImage::create("unmute.png", "unmute.png");
        MenuItemToggle* muteToggleItem = MenuItemToggle::createWithCallback(CC_CALLBACK_1(HomeLayer::toggleSound, this), mute, unmute, NULL);
        Menu* muteToggleMenu = Menu::create(muteToggleItem, NULL);
        muteToggleMenu->setPosition(_visibleSize.width * 0.5, mute->getContentSize().height * 0.5);
        muteToggleItem->setSelectedIndex(currentSoundSettings);

        this->addChild(muteToggleMenu, BackgroundLayer::layerTouch);
        CocosDenshion::SimpleAudioEngine::getInstance()->setEffectsVolume(currentSoundSettings);
    }

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
    _flyingChicken4 = new FloatingChicken();
    
    Vec2 initialPosition1 = Vec2(_visibleSize.width * -0.20, 0.0);
    Vec2 initialPosition2 = Vec2(_visibleSize.width * 0.60, 0.0);
    Vec2 initialPosition4 = Vec2(_visibleSize.width * 0.70, 0.0);

    _flyingChicken1->createFloatingChicken(this, initialPosition1, AnimationType::fly_lefttoright_high);
    _flyingChicken2->createFloatingChicken(this, initialPosition2, AnimationType::fly_lefttoright_mid);
    _flyingChicken4->createFloatingChicken(this, initialPosition4, AnimationType::fly_righttoleft_mid);
}

void HomeLayer::addGround() {
    auto ground = Sprite::create("home_ground.png");
    if (not ground) { return; }
    ground->setPosition(Point(_visibleSize.width * 0.5 + _origin.x, _visibleSize.height * 0.5 + _origin.y));
    this->addChild(ground, BackgroundLayer::layerTouch);
}

void HomeLayer::addLogo() {
    auto logo = Sprite::create("logo.png");
    if (not logo) { return; }
    logo->setColor(Color3B(255, 208, 66));
    logo->setPosition(Point(_visibleSize.width * 0.5 + _origin.x, _visibleSize.height * 0.7 + _origin.y));
    this->addChild(logo, BackgroundLayer::layerTouch);
}

void HomeLayer::addPlayMenu() {
    auto playItem = MenuItemImage::create("btn_play.png", "btn_playclicked.png",
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

void HomeLayer::toggleSound(Ref* ref) {
    CocosDenshion::SimpleAudioEngine* audioEngine = CocosDenshion::SimpleAudioEngine::getInstance();
    
    audioEngine->setEffectsVolume(not audioEngine->getEffectsVolume());
    UserDefault::getInstance()->setFloatForKey(VOLUME, audioEngine->getEffectsVolume());
}

void HomeLayer::update(float dt) {
    if (_flyingChicken1) { _flyingChicken1->update(dt); }
    if (_flyingChicken2) { _flyingChicken2->update(dt); }
    if (_flyingChicken4) { _flyingChicken4->update(dt); }
}









