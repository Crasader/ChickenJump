#include "Cloud.h"

#include "Constants.h"

Cloud::Cloud(void){
    _origin = Director::getInstance()->getVisibleOrigin();
    _visibleSize = Director::getInstance()->getVisibleSize();
}

void Cloud::spawn(cocos2d::Layer* layer) {
    if (not layer) { return; }

    /* Make TREE_SPAWN_FREQUENCY a bit bigger,
       So that we get some space to move our spawaning position */

    int cloudType = CCRANDOM_0_1() * 3 + 1;
    if (cloudType == 3) {
        cloudType = 1;  // handle boundary condition
    }
    
    _cloud = Sprite::create(String::createWithFormat("cloud%i.png", cloudType)->getCString());
    _cloud->setAnchorPoint(Vec2(0, 0));
    
    int maxDelayWidth = 3;
    int randDelayWidth = CCRANDOM_0_1() * maxDelayWidth + 1; // range=1~4
    int posX = _visibleSize.width + _cloud->getContentSize().width * randDelayWidth;

    int heightRange = _visibleSize.height / 4 - _cloud->getContentSize().height;
    int minHeight = (_visibleSize.height / 4) * 3;
    int posY = CCRANDOM_0_1() * heightRange + minHeight;
    _cloud->setPosition(Vec2(posX,  posY));
        
//    auto action = MoveBy::create(CLOUD_SPEED * _visibleSize.width, Point(- _visibleSize.width * 1.5, 0));
    
    // MoveTo works as: goto the destination within the time given.
    // So speed depends on the distance it needs to cover.
    // In order to make the distance same for each Cloud we drag the Cloud upto the (-randDelayWidth * contentWidth) distance.
    auto action = MoveTo::create(CLOUD_SPEED * _visibleSize.width,
                                 Point(-_cloud->getContentSize().width * ((maxDelayWidth + 1) - randDelayWidth), _cloud->getPositionY()));
    _cloud->runAction(action);
    
    layer->addChild(_cloud, BackgroundLayer::layerBackground);
}