#include "SpecialCollectable.h"

#include "Constants.h"

using namespace cocos2d;

// 8:flying_bomb 16:life // 2:egg 4:pizza 8:scrolling_bomb
static const int pattern[] = {8, 16, 8, 8, 16, 8, 8, 16, 8, 16, 16, 8, 8, 16, 8, 16, 8, 8, 8, 16};
static std::vector<int> collectableType(pattern, pattern + sizeof(pattern) / sizeof(int));
static int currentTypeIndex = 0;

SpecialCollectable::SpecialCollectable(void){
    _origin = Director::getInstance()->getVisibleOrigin();
    _visibleSize = Director::getInstance()->getVisibleSize();
    
    random_shuffle(collectableType.begin(), collectableType.end());
}

void SpecialCollectable::spawn(cocos2d::Layer* layer, std::vector<Sprite*>& specialCollectables) {
    if (not layer) { return; }
    
    int type = collectableType.at(currentTypeIndex++ % collectableType.size());

    Sprite* bonusCollectable = Sprite::create(String::createWithFormat("specialcollectable%i.png", type)->getCString());
    if (not bonusCollectable) { return; }
    
    bonusCollectable->setAnchorPoint(Vec2(0.5f, 1.0f));
    bonusCollectable->setTag(type); // used as type:: 8:flying_bomb 16:life
    
    int positionX = RandomHelper::random_int((int)(_visibleSize.width * 0.65), (int)(_visibleSize.width * 0.80));
    int positionY = _visibleSize.height + bonusCollectable->getContentSize().height;
    bonusCollectable->setPosition(Vec2(positionX, positionY));
    
    auto body = PhysicsBody::createCircle(bonusCollectable->getContentSize().width / 2, PhysicsMaterial(0.1f, 1.0f, 0.0f));
    body->setCategoryBitmask(type); // set collectable type as category_bitmask (8:flying_bomb 16:life)
    // body->setCollisionBitmask(1);
    body->setContactTestBitmask(CATEGORY_BITMASK_CHICKEN);
    body->setDynamic(false);
    bonusCollectable->setPhysicsBody(body);
    
    layer->addChild(bonusCollectable, BackgroundLayer::layerChicken);
    
    {   // Swinging animation
        auto easeSwing = Sequence::create(EaseInOut::create(RotateTo::create(0.8f, -10), 2),
                                          EaseInOut::create(RotateTo::create(0.8f, 10), 2),
                                          nullptr);
        Action* _floatAnimation = RepeatForever::create( (ActionInterval*) easeSwing );
        bonusCollectable->runAction(_floatAnimation);
    }

    specialCollectables.push_back(bonusCollectable);
}









