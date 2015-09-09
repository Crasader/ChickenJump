#include "Egg.h"

#include "Constants.h"

Egg::Egg(void){
    _origin = Director::getInstance()->getVisibleOrigin();
    _visibleSize = Director::getInstance()->getVisibleSize();
}

void Egg::spawn(cocos2d::Layer* layer, std::vector<Sprite*>& eggs) {
    /* Make TREE_SPAWN_FREQUENCY a bit bigger,
       So that we get some space to move our spawaning position */
    
//    int eggType = CCRANDOM_0_1() * 3 + 1;
//    if (eggType == 3) {
//        eggType = 1;  // handle boundary condition
//    }
    
    _egg = Sprite::create(_imageFile);
//    _egg = Sprite::create(String::createWithFormat("tree%i.png", treeType)->getCString());
//    _tree->setAnchorPoint(Vec2(0, 0));

    // Static physics body
    auto eggBody = PhysicsBody::createCircle(_egg->getContentSize().width / 2, PhysicsMaterial(0.1f, 1.0f, 0.0f));
    eggBody->setCategoryBitmask(CATEGORY_BITMASK_EGG);
    // eggBody->setCollisionBitmask(1);
    eggBody->setContactTestBitmask(CATEGORY_BITMASK_CHICKEN);
    eggBody->setDynamic(false);
    _egg->setPhysicsBody(eggBody);

    
    int maxDelayWidth = 1;
    int randDelayWidth = CCRANDOM_0_1() * maxDelayWidth + 1; // range=1~4
    int posX = _visibleSize.width + _egg->getContentSize().width * randDelayWidth;
    
    int heightRange = _visibleSize.height / 2 - _egg->getContentSize().height * 2;
    int minHeight = (_visibleSize.height / 2);
    int posY = CCRANDOM_0_1() * heightRange + minHeight;
    _egg->setPosition(Vec2(posX,  posY));
    
//    auto action = MoveTo::create(EGG_SPEED * _visibleSize.width,
//                                 Point(-_egg->getContentSize().width * ((maxDelayWidth + 1) - randDelayWidth), _egg->getPositionY()));
    
    // MoveTo works as: goto the destination within the time given.
    // So speed depends on the distance it needs to cover.
    // In order to make the distance same for each Cloud we drag the Cloud upto the (-randDelayWidth * contentWidth) distance.
//    auto action = MoveTo::create(TREE_SPEED * _visibleSize.width, Point(-_tree->getContentSize().width * (6 - random), _tree->getPositionY()));
//    _egg->runAction(action);
    
    layer->addChild(_egg, BackgroundLayer::layerChicken);
    eggs.push_back(_egg);
}









