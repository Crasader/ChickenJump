#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"

using namespace CocosDenshion;

USING_NS_CC;

// audio
#define BACKGROUND_MUSIC_SFX  "background-music-aac.mp3"
#define PEW_PEW_SFX           "pew-pew-lei.mp3"

// Enum for collision detection
enum class PhysicsCategory {
    None = 0,
    Monster = (1 << 0),    // 1
    Projectile = (1 << 1), // 2
    All = PhysicsCategory::Monster | PhysicsCategory::Projectile // 3
};

Scene* HelloWorld::createScene()
{
    // 'scene' is an autorelease object
//    auto scene = Scene::create();
    auto scene = Scene::createWithPhysics();
    scene->getPhysicsWorld()->setGravity(Vec2(0,0));
//    scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);    // enable debug drawing
    
    // 'layer' is an autorelease object
    auto layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    // 1
    if ( !Layer::init() )
    {
        return false;
    }
    
    // 2. origin & window size
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    Size winSize = Director::getInstance()->getVisibleSize();

    // 3. create background
    auto background = DrawNode::create();
    background->drawSolidRect(origin, winSize, Color4F(0.6,0.6,0.6,1.0));
    this->addChild(background);
    
    // 4. create player sprite
    _player = Sprite::create("player.png");
    _player->setPosition(Vec2(winSize.width * 0.1, winSize.height * 0.5));
    this->addChild(_player);
    
    // create monsters
    srand((unsigned int)time(nullptr));     // seeds the random number generator
    this->schedule(schedule_selector(HelloWorld::addMonster), 1.5);
    
    // touch event listening
    auto eventListener = EventListenerTouchOneByOne::create();
    eventListener->onTouchBegan = CC_CALLBACK_2(HelloWorld::onTouchBegan, this);
    this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(eventListener, _player);
    
    // collision listner
    auto contactListener = EventListenerPhysicsContact::create();
    contactListener->onContactBegin = CC_CALLBACK_1(HelloWorld::onContactBegan, this);
    this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(contactListener, this);
    
    // background audio
    SimpleAudioEngine::getInstance()->playBackgroundMusic(BACKGROUND_MUSIC_SFX, true);
    
    return true;
}

void HelloWorld::addMonster(float dt)
{
    auto monster = Sprite::create("monster.png");

    auto monsterSize = monster->getContentSize();
    
    {
        // draw physics body around monster sprite
        auto physicsBody = PhysicsBody::createBox(Size(monsterSize.width , monsterSize.height), PhysicsMaterial(0.1f, 1.0f, 0.0f));

        // physics engine will not apply forces to the monster. Instead, it will be controled through the MoveTo actions
        physicsBody->setDynamic(true);
        
        physicsBody->setCategoryBitmask((int)PhysicsCategory::Monster);         // set object’s type
        physicsBody->setCollisionBitmask((int)PhysicsCategory::None);           //
        physicsBody->setContactTestBitmask((int)PhysicsCategory::Projectile);   // obj type with which collisions should generate notifications
        
        monster->setPhysicsBody(physicsBody);
    }
    
    // 1. determine starting position of a monster
    auto selfContentSize = this->getContentSize();
    int minY = monsterSize.height/2;
    int maxY = selfContentSize.height - monsterSize.height/2;
    int rangeY = maxY - minY;
    int randomY = (rand() % rangeY) + minY;
    
    monster->setPosition(Vec2(selfContentSize.width + monsterSize.width/2, randomY));
    this->addChild(monster);
    
    // 2. set random speed of monster
    int minDuration = 2.0;
    int maxDuration = 4.0;
    int rangeDuration = maxDuration - minDuration;
    int randDuration = (rand() % rangeDuration) + minDuration;
    
    //3. monster action (move left to right)
    auto actionMove = MoveTo::create(randDuration, Vec2(-monsterSize.width/2, randomY));
    auto actionRemove = RemoveSelf::create();
    monster->runAction(Sequence::create(actionMove, actionRemove, nullptr));
}

bool HelloWorld::onTouchBegan(Touch *touch, Event *unused_event)
{
    // 1. - Just an example for how to get the  _player object
    //auto node = unused_event->getCurrentTarget();
    
    // 2. get touch locaiton
    Vec2 touchLocation = touch->getLocation();
    Vec2 offset = touchLocation - _player->getPosition();

    // 3. unreal touch locaiton
    if (offset.x < 0) {
        return true;
    }
    
    // 4. create bullet sprite
    auto projectile = Sprite::create("projectile.png");
    projectile->setPosition(_player->getPosition());
    
    {
        // draw physics body around projectile sprite (same as monster)
        auto projectileSize = projectile->getContentSize();
        auto physicsBody = PhysicsBody::createCircle(projectileSize.width/2 );
        physicsBody->setDynamic(true);
        physicsBody->setCategoryBitmask((int)PhysicsCategory::Projectile);
        physicsBody->setCollisionBitmask((int)PhysicsCategory::None);
        physicsBody->setContactTestBitmask((int)PhysicsCategory::Monster);
        projectile->setPhysicsBody(physicsBody);
    }
    
    this->addChild(projectile);
    
    // 5. call normalize() to convert the offset into a unit vector, which is a vector of length 1.
    //    Multiplying that by 1000 gives a vector of length 1000 that points in the direction of the user’s tap.
    //    Why 1000? That length should be enough to extend past the edge of your screen at this resolution
    offset.normalize();
    auto shootAmount = offset * 1000;
    
    // 6. calculate end destination
    auto realDest = shootAmount + projectile->getPosition();
    
    // 7. projectile move action
    auto actionMove = MoveTo::create(2.0f, realDest);
    auto actionRemove = RemoveSelf::create();
    projectile->runAction(Sequence::create(actionMove,actionRemove, nullptr));
    
    // audio
    SimpleAudioEngine::getInstance()->playEffect(PEW_PEW_SFX);
    
    return true;
}

bool HelloWorld::onContactBegan(PhysicsContact &contact)
{
    auto nodeA = contact.getShapeA()->getBody()->getNode();
    auto nodeB = contact.getShapeB()->getBody()->getNode();
    
    nodeA->removeFromParent();
    nodeB->removeFromParent();
    return true;
}


void HelloWorld::menuCloseCallback(Ref* pSender)
{
    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}
