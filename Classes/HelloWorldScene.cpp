#include "HelloWorldScene.h"

USING_NS_CC;

Scene* HelloWorld::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
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
    
    return true;
}

void HelloWorld::addMonster(float dt)
{
    auto monster = Sprite::create("monster.png");
    
    // 1
    auto monsterContentSize = monster->getContentSize();
    auto selfContentSize = this->getContentSize();
    int minY = monsterContentSize.height/2;
    int maxY = selfContentSize.height - monsterContentSize.height/2;
    int rangeY = maxY - minY;
    int randomY = (rand() % rangeY) + minY;
    
    monster->setPosition(Vec2(selfContentSize.width + monsterContentSize.width/2, randomY));
    this->addChild(monster);
    
    // 2
    int minDuration = 2.0;
    int maxDuration = 4.0;
    int rangeDuration = maxDuration - minDuration;
    int randDuration = (rand() % rangeDuration) + minDuration;
    
    //3
    auto actionMove = MoveTo::create(randDuration, Vec2(-monsterContentSize.width/2, randomY));
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
    this->addChild(projectile);
    
    // 5. call normalize() to convert the offset into a unit vector, which is a vector of length 1.
    //    Multiplying that by 1000 gives a vector of length 1000 that points in the direction of the user’s tap.
    //    Why 1000? That length should be enough to extend past the edge of your screen at this resolution
    offset.normalize();
    auto shootAmount = offset * 1000;
    
    // 6
    auto realDest = shootAmount + projectile->getPosition();
    
    // 7
    auto actionMove = MoveTo::create(2.0f, realDest);
    auto actionRemove = RemoveSelf::create();
    projectile->runAction(Sequence::create(actionMove,actionRemove, nullptr));
    
    return true;
}


void HelloWorld::menuCloseCallback(Ref* pSender)
{
    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}
