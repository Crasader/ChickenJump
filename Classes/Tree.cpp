#include "Tree.h"
#include "Constants.h"

Tree::Tree(void){
    _origin = Director::getInstance()->getVisibleOrigin();
    _visibleSize = Director::getInstance()->getVisibleSize();
}

void Tree::spawn(cocos2d::Layer* layer) {
    /* Make TREE_SPAWN_FREQUENCY a bit bigger,
       So that we get some space to move our spawaning position */
    
    int treeType = CCRANDOM_0_1() * 3 + 1;
    if (treeType == 3) {
        treeType = 1;  // handle boundary condition
    }
    
    _sprite = Sprite::create(String::createWithFormat("tree%i.png", treeType)->getCString());
//    _sprite->setAnchorPoint(Vec2(0, 0));
    
    int randDelayWidth = CCRANDOM_0_1() * 4 + 1;
    _sprite->setPosition(Vec2(_origin.x + _visibleSize.width + _sprite->getContentSize().width * randDelayWidth, _origin.y + (_visibleSize.height / 7) * 2 ));
        
    auto action = MoveBy::create(TREE_SPEED * _visibleSize.width, Point(- _visibleSize.width * 1.5, 0));
    
    // MoveTo works as: goto the destination within the time given.
    // So speed depends on the distance it needs to cover.
    // In order to make the distance same for each Cloud we drag the Cloud upto the (-randDelayWidth * contentWidth) distance.
//    auto action = MoveTo::create(TREE_SPEED * _visibleSize.width, Point(-_sprite->getContentSize().width * (6 - random), _sprite->getPositionY()));
    _sprite->runAction(action);
    
    layer->addChild(_sprite);
}