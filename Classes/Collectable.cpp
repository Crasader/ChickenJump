#include "Collectable.h"

#include "Constants.h"

Collectable::Collectable(void){
    _origin = Director::getInstance()->getVisibleOrigin();
    _visibleSize = Director::getInstance()->getVisibleSize();
}

void Collectable::spawn(cocos2d::Layer* layer, std::vector<Sprite*>& collectables, int pattern) {
    if (not layer) { return; }
    
    const float distanceBetweenEggs = 0.001;
    int numberOfEggs = 0;
    int degree = 0;
    float radius = 0.0;
    
    switch (pattern) {
        case 0:
            return;
        case 1:
            numberOfEggs = 5;
            degree = 45;
            radius = 0.075;
            break;
        case 2:
            numberOfEggs = 7;
            degree = 30;
            radius = 0.15;
            break;
        case 3:
            numberOfEggs = 3;
            degree = 90;
            radius = 0.05;
            break;
            
        default:
            return;
    }
    
    int eggType = CCRANDOM_0_1() * 4 + 1;
//    if (eggType == 3) {
//        eggType = 1;  // handle boundary condition
//    }
    
    int heightRange = _visibleSize.height * 0.25;
    int minHeight = (_visibleSize.height * 0.4);
    int minPosY = CCRANDOM_0_1() * heightRange + minHeight;
    
    float positionX = _visibleSize.width;
    float positionY;
    for (int i = 0; i < numberOfEggs; ++i) {
        Sprite* collectable = Sprite::create(String::createWithFormat("egg%i.png", eggType)->getCString());
        
        positionX += _visibleSize.width * distanceBetweenEggs; // distance between eggs
        positionY = (_visibleSize.width * radius) * sin(degree2radian(i * degree)); // y = radius * sin(angle) // bigger radius = higher parabola
        collectable->setPosition(Vec2(positionX, minPosY + positionY));
        
        auto body = PhysicsBody::createCircle(collectable->getContentSize().width / 2, PhysicsMaterial(0.1f, 1.0f, 0.0f));
        body->setCategoryBitmask(CATEGORY_BITMASK_EGG);
        // eggBody->setCollisionBitmask(1);
        body->setContactTestBitmask(CATEGORY_BITMASK_CHICKEN);
        body->setDynamic(false);
        collectable->setPhysicsBody(body);
        
        layer->addChild(collectable, BackgroundLayer::layerChicken);
        collectables.push_back(collectable);
        
        positionX += collectable->getContentSize().width * 1.5; // distance must be atleast 1.5 egg width
    }
}









