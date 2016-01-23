#include "Collectable.h"

#include "Constants.h"

using namespace cocos2d;

static int totalNumberOfPatterns = 20;
static int currentPatternIndex = 0;

Collectable::Collectable(void){
    _origin = Director::getInstance()->getVisibleOrigin();
    _visibleSize = Director::getInstance()->getVisibleSize();
    
    // TODO: initPatterns based on Difficulty Level
    initPatterns(1);
    std::random_shuffle(_patterns.begin(), _patterns.end());
}

// 2:egg 4:pizza 8:bomb
void Collectable::populatePatterns(int eggs, int pizzas, int bombs, int difficultyLevel) {
    // Eggs: 2
    for (int i = 0; i < eggs; ++i) {
        _patterns.push_back(std::make_pair(2, RandomHelper::random_int(1, 3)));
    }
    
    // Pizzas: 4
    for (int i = 0; i < pizzas; ++i) {
        _patterns.push_back(std::make_pair(4, difficultyLevel > 3 ? RandomHelper::random_int(1, 3) : RandomHelper::random_int(2, 3)));
    }
    
    // Bombs: 8
    for (int i = 0; i < bombs; ++i) {
        _patterns.push_back(std::make_pair(8, difficultyLevel > 3 ? RandomHelper::random_int(1, 3) : RandomHelper::random_int(2, 3)));
    }
}

void Collectable::initPatterns(int difficultyLevel) {
    switch (difficultyLevel) {
        case 1:
            // 50% eggs, 30% pizza, 20% bomb
            populatePatterns(totalNumberOfPatterns * 0.5, totalNumberOfPatterns * 0.3, totalNumberOfPatterns * 0.2, difficultyLevel);
            break;
        case 2:
            
            break;
        case 3:
            break;
        case 4:
            break;
        case 5:
            break;
        case 6:
            break;
        default:
            break;
    }
}

void Collectable::spawn(cocos2d::Layer* layer, std::vector<Sprite*>& collectables) {
    if (not layer) { return; }
    
    Pattern const& pattern = _patterns.at(currentPatternIndex++ % _patterns.size());
    
    int degree = 0;
    float radius = 0.0;
    
    switch (pattern.second) {
        case 0:
            return;
        case 1:    // 7 items
            degree = 30;
            radius = 0.15;
            break;
        case 2:    // 5 items
            degree = 45;
            radius = 0.075;
            break;
        case 3:    // 3 items
            degree = 90;
            radius = 0.05;
            break;
            
        default:
            return;
    }
    int numberOfCollectable = 180 / degree + 1; // 180 = half 360. we need only half of the parabola
    
    int minPosY = RandomHelper::random_int(int(_visibleSize.height * 0.4), int(_visibleSize.height * 0.65));
    
    float positionX = _visibleSize.width;
    float positionY;
    for (int i = 0; i < numberOfCollectable; ++i) {
        Sprite* collectable = Sprite::create(String::createWithFormat("collectable%i.png", pattern.first)->getCString());
        if (not collectable) { continue; }
        
        collectable->setTag(pattern.first); // used as CollectableType:: 2:egg 4:pizza 8:bomb

        positionX += collectable->getContentSize().width * 1.5; // distance must be atleast 1.5 collectable width
        positionY = (_visibleSize.width * radius) * sin(degree2radian(i * degree)); // y = radius * sin(angle) // bigger radius = higher parabola
        collectable->setPosition(Vec2(positionX, minPosY + positionY));
        
        auto body = PhysicsBody::createCircle(collectable->getContentSize().width / 2, PhysicsMaterial(0.1f, 1.0f, 0.0f));
        body->setCategoryBitmask(pattern.first);  // set collectable type as category_bitmask (2:egg 4:pizza 8:scrolling_bomb)
        // body->setCollisionBitmask(1);
        body->setContactTestBitmask(CATEGORY_BITMASK_CHICKEN);
        body->setDynamic(false);
        collectable->setPhysicsBody(body);
        
        layer->addChild(collectable, BackgroundLayer::layerGround);
        collectables.push_back(collectable);
    }
}









