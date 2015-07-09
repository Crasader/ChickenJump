#include "Scene_GameLayer.h"
#include "Sprite_Player.h"


GameLayer::~GameLayer() {
    
}

Scene* GameLayer::scene()
{
    CCLOG("GameLayer::createScene");
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
//    scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL); // enable debug drawing; works when Scene is created with physics
    
    // 'layer' is an autorelease object
    GameLayer *layer = GameLayer::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool GameLayer::init()
{
    CCLOG("GameLayer::init");
    // 1. super init first
    if ( !Layer::init() ) {
        return false;
    }
    
//    // 2. origin & window size
//    Vec2 origin = Director::getInstance()->getVisibleOrigin();
//    Size winSize = Director::getInstance()->getVisibleSize();
    
    //set screen size
    _screenSize = Director::getInstance()->getWinSize();
    
    createGameScreen();
    
    resetGame();
    
    //listen for touches
    auto listener = EventListenerTouchOneByOne::create();
    listener->setSwallowTouches(true);
    listener->onTouchBegan = CC_CALLBACK_2(GameLayer::onTouchBegan, this);
    listener->onTouchEnded = CC_CALLBACK_2(GameLayer::onTouchEnded, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
    
    //create main loop
    this->scheduleUpdate();
    
    return true;
}

void GameLayer::resetGame() {
    CCLOG("GameLayer::resetGame");
    _speedIncreaseInterval = 15;
    _speedIncreaseTimer = 0;
    
    _running = true;
}

void GameLayer::update(float dt) {
    if(!_running) return;
    
    if(_player->getPositionY() < -_player->getHeight() ||
        _player->getPositionX() < -_player->getWidth() * 0.5f) {
        
        _running = false;
    }
    
    _player->update(dt);
    
    _terrain->move(_player->getVector().x);
    
    if(_player->getState() != kPlayerDying) _terrain->checkCollision(_player);
    
    _player->place();
    
    if(_player->getNextPosition().y > _screenSize.height * 0.6f) {
        _gameBatchNode->setPositionY( (_screenSize.height * 0.6f - _player->getNextPosition().y) * 0.8f);
    } else {
        _gameBatchNode->setPositionY( 0 );
    }
    
    // update paralax
    if (_player->getVector().x > 0) {
        // First, we move the _background sprite, which contains the cityscape texture repeated three times along the x axis,
        // and we move it at one-fourth of the speed of the _player sprite.
        _background->setPositionX(_background->getPosition().x - _player->getVector().x * 0.25f);
        
        // Second, the _background sprite scrolls to the left, and as soon as the first cityscape texture is off the screen,
        // we shift the entire _background container to the right at precisely the spot where the second cityscape texture would appear if allowed to continue.
        // We get this value by subtracting where the sprite would be from the total width of the sprite
        float diffx;
        
        if (_background->getPositionX() < -_background->getContentSize().width) {
            diffx = fabs(_background->getPositionX()) - _background->getContentSize().width;
            _background->setPositionX(-diffx);
        }
        
        // A similar process(like background) is repeated for the _foreground sprite. only the speed is of foreground is four times of the player
        _foreground->setPositionX(_foreground->getPosition().x - _player->getVector().x * 4);
        
        if (_foreground->getPositionX() < -_foreground->getContentSize().width * 4) {
            diffx = fabs(_foreground->getPositionX()) - _foreground->getContentSize().width * 4;
            _foreground->setPositionX(-diffx);
        }
        
        // our cloud appears behind the citiscape (farther away from the player), so moves at an even lower rate
        for (auto cloud : _clouds) {
            cloud->setPositionX(cloud->getPositionX() - _player->getVector().x * 0.15f);
            if (cloud->getPositionX() + cloud->boundingBox().size.width * 0.5f < 0 )
                cloud->setPositionX(_screenSize.width + cloud->boundingBox().size.width * 0.5f);
        }
    }
    
}

bool GameLayer::onTouchBegan(Touch* touch, Event* event) {
    CCLOG("GameLayer::onTouchBegan");
    if(!_running) {
        if(_player->getState() == kPlayerDying) {
            _terrain->reset();
            _player->reset();
            resetGame();
        }
        
        return true;
    }
    
    if(!_terrain->getStartTerrain()) {
        _terrain->setStartTerrain ( true );
        return true;
    }
    
    if(touch) {
        if (_player->getState() == kPlayerFalling) {
            _player->setFloating ( _player->getFloating() ? false : true );
        } else {
            if (_player->getState() !=  kPlayerDying) _player->setJumping(true);
        }
        return true;
    }
    
    return false;
}

void GameLayer::onTouchEnded(Touch* touch, Event* event) {
    _player->setJumping(false);
}

void GameLayer::createGameScreen() {
    CCLOG("GameLayer::createGameScreen");
    auto bg = Sprite::create("bg.png");
    bg->setPosition(Vec2(_screenSize.width * 0.5f, _screenSize.height * 0.5f));
    this->addChild(bg, kBackground);
    
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("sprite_sheet.plist");
    _gameBatchNode = SpriteBatchNode::create("sprite_sheet.png", 200);
    this->addChild(_gameBatchNode, kMiddleground);
    
    _background = Sprite::createWithSpriteFrameName("background.png");
    _background->setAnchorPoint(Vec2(0,0));
    _gameBatchNode->addChild(_background, kBackground);
    
    auto repeat = Sprite::createWithSpriteFrameName("background.png");
    repeat->setAnchorPoint(Vec2(0,0));
    repeat->setPosition(Vec2(repeat->getContentSize().width - 1, 0));
    _background->addChild(repeat, kBackground);
    
    repeat = Sprite::createWithSpriteFrameName("background.png");
    repeat->setAnchorPoint(Vec2(0,0));
    repeat->setPosition(Vec2(2 * (repeat->getContentSize().width - 1), 0));
    _background->addChild(repeat, kBackground);
    
    _foreground = Sprite::createWithSpriteFrameName("lamp.png");
    _foreground->setAnchorPoint(Vec2(0,0));
    _gameBatchNode->addChild(_foreground, kForeground);
    
    repeat = Sprite::createWithSpriteFrameName("lamp.png");
    repeat->setAnchorPoint(Vec2(0,0));
    repeat->setPosition(Vec2(repeat->getContentSize().width * 4, 0));
    _foreground->addChild(repeat, kBackground);
    
    repeat = Sprite::createWithSpriteFrameName("lamp.png");
    repeat->setAnchorPoint(Vec2(0,0));
    repeat->setPosition(Vec2(repeat->getContentSize().width * 8, 0));
    _foreground->addChild(repeat, kBackground);
    
    
    //add clouds
    _clouds = Vector<Sprite*>(4);
    float cloud_y;
    for (int i = 0; i < 4; i++) {
        cloud_y = i % 2 == 0 ? _screenSize.height * 0.7f : _screenSize.height * 0.8f;
        auto cloud = Sprite::createWithSpriteFrameName("cloud.png");
        cloud->setPosition(Vec2 (_screenSize.width * 0.15f + i * _screenSize.width * 0.25f,  cloud_y));
        _gameBatchNode->addChild(cloud, kBackground);
        _clouds.pushBack(cloud);
    }
    
    
    _terrain = GameTerrain::create();
    _gameBatchNode->addChild(_terrain, kMiddleground);
    
    _player = Player::create();
    _gameBatchNode->addChild(_player, kBackground);
    
}




