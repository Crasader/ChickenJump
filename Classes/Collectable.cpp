#include "Collectable.h"

#include "Constants.h"

using namespace cocos2d;

// 2:egg 4:pizza 8:bomb
static const int pattern[] = {2, 4, 2, 2, 2, 8, 2, 2, 4, 2, 2, 2, 8, 2, 4, 2, 2, 4, 2, 2};
//static const int pattern[] = {2, 3, 2, 3};
static const std::vector<int> collectableType(pattern, pattern + sizeof(pattern) / sizeof(int));
static int currentTypeIndex = 0;

Collectable::Collectable(void){
    _origin = Director::getInstance()->getVisibleOrigin();
    _visibleSize = Director::getInstance()->getVisibleSize();
    
//    std::random_shuffle (collectableType.begin(), collectableType.end(), collectableType);
}

void Collectable::spawn(cocos2d::Layer* layer, std::vector<Sprite*>& collectables, int pattern) {
    if (not layer) { return; }
    
    int degree = 0;
    float radius = 0.0;
    
    switch (pattern) {
        case 0:
            return;
        case 1:
            degree = 45;
            radius = 0.075;
            break;
        case 2:
            degree = 30;
            radius = 0.15;
            break;
        case 3:
            degree = 90;
            radius = 0.05;
            break;
            
        default:
            return;
    }
    int numberOfCollectable = 180 / degree + 1; // 180 = half 360. we need only half of the parabola
    
    int type = collectableType.at(currentTypeIndex++ % collectableType.size());
    
    int minPosY = RandomHelper::random_int(int(_visibleSize.height * 0.4), int(_visibleSize.height * 0.65));
    
    float positionX = _visibleSize.width;
    float positionY;
    for (int i = 0; i < numberOfCollectable; ++i) {
        Sprite* collectable = Sprite::create(String::createWithFormat("collectable%i.png", type)->getCString());
        if (not collectable) { continue; }
        
        collectable->setTag(type); // used as CollectableType:: 2:egg 4:pizza 8:bomb

        positionX += collectable->getContentSize().width * 1.5; // distance must be atleast 1.5 collectable width
        positionY = (_visibleSize.width * radius) * sin(degree2radian(i * degree)); // y = radius * sin(angle) // bigger radius = higher parabola
        collectable->setPosition(Vec2(positionX, minPosY + positionY));
        
        auto body = PhysicsBody::createCircle(collectable->getContentSize().width / 2, PhysicsMaterial(0.1f, 1.0f, 0.0f));
        body->setCategoryBitmask(type);  // set collectable type as category_bitmask (2:egg 4:pizza 8:scrolling_bomb)
        // body->setCollisionBitmask(1);
        body->setContactTestBitmask(CATEGORY_BITMASK_CHICKEN);
        body->setDynamic(false);
        collectable->setPhysicsBody(body);
        
        layer->addChild(collectable, BackgroundLayer::layerGround);
        collectables.push_back(collectable);
    }
}









