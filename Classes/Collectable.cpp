#include "Collectable.h"

#include "Constants.h"
#include "Stage.h"

using namespace cocos2d;

static int totalNumberOfPatterns = 20;
static int currentPatternIndex = 0;

Collectable::Collectable(Stage const& stage) {
    _origin = Director::getInstance()->getVisibleOrigin();
    _visibleSize = Director::getInstance()->getVisibleSize();
    
    initPatterns(stage.getDifficulty());
    std::random_shuffle(_patterns.begin(), _patterns.end());
}

// 2:egg 4:pizza 8:bomb
void Collectable::populatePatterns(int difficultyLevel, int eggs, int pizzas, int bombs) {
    // Eggs: 2
    for (int i = 0; i < eggs; ++i) {
        _patterns.push_back(std::make_pair(2, RandomHelper::random_int(1, 3)));
    }
    
    // Pizzas: 4
    for (int i = 0; i < pizzas; ++i) {
        _patterns.push_back(std::make_pair(4, RandomHelper::random_int(2, 3)));
    }
    
    // Bombs: 8
    for (int i = 0; i < bombs; ++i) {
        _patterns.push_back(std::make_pair(8, RandomHelper::random_int(2, 3)));
    }
}

void Collectable::initPatterns(int difficultyLevel) {
    switch (difficultyLevel) {
        case 1:    // eggs(100%), pizza(0), bomb(0)
            populatePatterns(difficultyLevel, totalNumberOfPatterns * 1.0, 0, 0);
            break;
        case 2:    // eggs(75%), pizza(35%), bomb(0)
            populatePatterns(difficultyLevel, totalNumberOfPatterns * 0.75, totalNumberOfPatterns * 0.35, 0);
            break;
        case 3:    // eggs(55%), pizza(30%), bomb(15%)
            populatePatterns(difficultyLevel, totalNumberOfPatterns * 0.55, totalNumberOfPatterns * 0.3, totalNumberOfPatterns * 0.15);
            break;
        case 4:    // eggs(50%), pizza(30%), bomb(20%)
            populatePatterns(difficultyLevel, totalNumberOfPatterns * 0.5, totalNumberOfPatterns * 0.3, totalNumberOfPatterns * 0.2);
            break;
        case 5:    // eggs(40%), pizza(30%), bomb(30%) // magnet effect introduced
            populatePatterns(difficultyLevel, totalNumberOfPatterns * 0.4, totalNumberOfPatterns * 0.3, totalNumberOfPatterns * 0.3);
            break;
        case 6:    // eggs(35%), pizza(35%), bomb(30%) // invisibility introduced
            populatePatterns(difficultyLevel, totalNumberOfPatterns * 0.35, totalNumberOfPatterns * 0.35, totalNumberOfPatterns * 0.3);
            break;
        case 7:    // Infinite Stage (eggs(35%), pizza(35%), bomb(30%))
            populatePatterns(difficultyLevel, totalNumberOfPatterns * 0.35, totalNumberOfPatterns * 0.35, totalNumberOfPatterns * 0.3);
            break;
        default:
            break;
    }
}

Spawned Collectable::spawn(cocos2d::Layer* layer, std::vector<Sprite*>& collectables) {
    Spawned result = std::make_pair(0,0);
    if (not layer) { return result; }
    
    Pattern const& pattern = _patterns.at(currentPatternIndex++ % _patterns.size());
    
    int degree = 0;
    float radius = 0.0;
    
    // set spawned.type
    result.first = pattern.first;
    
    switch (pattern.second) {
        case 0:
            return result;
        case 1:    // 7 items
            degree = 30;
            radius = 0.15;
            result.second = 7;
            break;
        case 2:    // 5 items
            degree = 45;
            radius = 0.075;
            result.second = 5;
            break;
        case 3:    // 3 items
            degree = 90;
            radius = 0.05;
            result.second = 3;
            break;
            
        default:
            return result;
    }
    int numberOfCollectable = 180 / degree + 1; // 180 = half 360. we need only half of the parabola
    
    int minPosY = RandomHelper::random_int(int(_visibleSize.height * 0.4), int(_visibleSize.height * 0.65));
    
    float positionX = _visibleSize.width;
    float positionY;
    for (int i = 0; i < numberOfCollectable; ++i) {
        Sprite* collectable = Sprite::create(StringUtils::format("collectable%i.png", pattern.first));
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
    
    return result;
}









