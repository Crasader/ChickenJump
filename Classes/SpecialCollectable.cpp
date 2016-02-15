#include "SpecialCollectable.h"

#include "Constants.h"
#include "Stage.h"

using namespace cocos2d;

static int totalNumberOfCollectables = 20;
static int currentCollectableIndex = 0;

SpecialCollectable::SpecialCollectable(Stage const& stage){
    _origin = Director::getInstance()->getVisibleOrigin();
    _visibleSize = Director::getInstance()->getVisibleSize();
    
    initPatterns(stage.getDifficulty());
    random_shuffle(_specialCollectableTypes.begin(), _specialCollectableTypes.end());
}

void SpecialCollectable::populatePatterns(int difficultyLevel, int life, int floatingBomb, int invisibility, int magnetEffect) {
    // Floating Bomb: 8
    for (int i = 0; i < floatingBomb; ++i) {
        _specialCollectableTypes.push_back(CATEGORY_BITMASK_COLLECT_BOMB);
    }
    
    // Life: 16
    for (int i = 0; i < life; ++i) {
        _specialCollectableTypes.push_back(CATEGORY_BITMASK_COLLECT_LIFE);
    }
    
    // Invisibility: 32
    for (int i = 0; i < invisibility; ++i) {
        _specialCollectableTypes.push_back(CATEGORY_BITMASK_INVISIBILITY);
    }
    
    // Magnet Effect: 128
    for (int i = 0; i < magnetEffect; ++i) {
        _specialCollectableTypes.push_back(CATEGORY_BITMASK_MAGNET);
    }
}

void SpecialCollectable::initPatterns(int difficultyLevel) {
    switch (difficultyLevel) {
        case 1:    // no special collectables
            break;
        case 2:    // no special collectables
            break;
        case 3:    // introducint "life"
            populatePatterns(difficultyLevel, totalNumberOfCollectables * 1.0, 0, 0, 0);
            break;
        case 4:    // life + floating bomb (50% each)
            populatePatterns(difficultyLevel, totalNumberOfCollectables * 0.5, totalNumberOfCollectables * 0.5, 0, 0);
            break;
        case 5:    // life(33%) + floating bomb(33%) + invisibility(0) + magnet effect(33%)
            populatePatterns(difficultyLevel, totalNumberOfCollectables * 0.33, totalNumberOfCollectables * 0.33, 0, totalNumberOfCollectables * 0.33);            
            break;
        case 6:   // life(33%) + floating bomb(33%) + invisibility(33%) + magnet effect(0)
            populatePatterns(difficultyLevel, totalNumberOfCollectables * 0.33, totalNumberOfCollectables * 0.33, totalNumberOfCollectables * 0.33, 0);
            break;
        case 7:    // Infinite Stage (life + floating bomb + invisibility + magnet effect (25% each))
            populatePatterns(difficultyLevel, totalNumberOfCollectables * 0.25, totalNumberOfCollectables * 0.25, totalNumberOfCollectables * 0.25, totalNumberOfCollectables * 0.25);
            break;
        default:
            break;
    }
}

void SpecialCollectable::spawn(cocos2d::Layer* layer, std::vector<Sprite*>& specialCollectables) {
    if (not layer) { return; }
    if (_specialCollectableTypes.empty()) { return; }
    
    int type = _specialCollectableTypes.at(currentCollectableIndex++ % _specialCollectableTypes.size());

    Sprite* bonusCollectable = Sprite::create(String::createWithFormat("specialcollectable%i.png", type)->getCString());
    if (not bonusCollectable) { return; }
    
    bonusCollectable->setAnchorPoint(Vec2(0.5f, 1.0f));
    bonusCollectable->setTag(type); // used as type:: 8:flying_bomb 16:life
    
    int positionX = RandomHelper::random_int((int)(_visibleSize.width * 0.65), (int)(_visibleSize.width * 0.80));
    int positionY = _visibleSize.height + bonusCollectable->getContentSize().height;
    bonusCollectable->setPosition(Vec2(positionX, positionY));
    
    auto body = PhysicsBody::createCircle(bonusCollectable->getContentSize().width * 0.5, PhysicsMaterial(0.1, 1.0, 0.0));
    body->setCategoryBitmask(type); // set collectable type as category_bitmask (8:flying_bomb 16:life)
    // body->setCollisionBitmask(1);
    body->setContactTestBitmask(CATEGORY_BITMASK_CHICKEN);
    body->setDynamic(false);
    if (type == CATEGORY_BITMASK_COLLECT_LIFE) {
        // push up the p_body for floating balloon (life) with tail
        body->setPositionOffset(Vec2(0, bonusCollectable->getContentSize().height * 0.25));
    }
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









