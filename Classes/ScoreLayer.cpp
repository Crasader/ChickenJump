#include "ScoreLayer.h"

#include "Constants.h"
#include "GameLayer.h"

using namespace cocos2d;

bool ScoreLayer::init()
{
    if ( !LayerColor::initWithColor(Color4B(0, 0, 0, 0)) ) {
        return false;
    }

    _origin = Director::getInstance()->getVisibleOrigin();
    _visibleSize = Director::getInstance()->getVisibleSize();

    // set ScoreHUD's size and position
    this->setContentSize(Size(_visibleSize.width, _visibleSize.height * 0.1));
    this->setPosition(0, _visibleSize.height - this->getContentSize().height);
    
    // add score icon
    auto icon = Sprite::create(imageScore);
    if (icon) {
        icon->setPosition(Vec2(_visibleSize.width - icon->getContentSize().width * 2.5, this->getContentSize().height * 0.5));
        this->addChild(icon);
    }

    // add score(text)
    _scoreLabel = Label::createWithTTF("0", font, _visibleSize.height * SCORE_FONT_SIZE);
    if (_scoreLabel) {
        _scoreLabel->setColor(Color3B::WHITE);
        _scoreLabel->setPosition(Vec2(_visibleSize.width - icon->getContentSize().width, this->getContentSize().height * 0.44));
        this->addChild(_scoreLabel);
    }
    
    // Initialize number of life sprites
    initLifeSprites(CHICKEN_LIVES_MAX);
    updateLife(CHICKEN_LIVES);

    return true;
}

void ScoreLayer::initLifeSprites(int lives) {
    Vec2 initialPosition = Vec2(_visibleSize.width * 0.05, this->getContentSize().height * 0.5);

    for (int i = 0; i < lives; ++i) {
        auto life = Sprite::create(imageLife);
        if (life) {
            life->setPosition(Vec2(initialPosition.x + i * life->getContentSize().width, initialPosition.y));
            this->addChild(life);

            _lifeSprites.push_back(life);
        }
    }
}

void ScoreLayer::updateLife(int lives) {
    for (int i = 0; i < _lifeSprites.size(); ++i) {
        _lifeSprites.at(i)->setVisible(true);
        if (i >= lives) {
            _lifeSprites.at(i)->setVisible(false);
        }
    }
}

void ScoreLayer::updateScore(int score) {
    if (_scoreLabel) {
        std::string scoreStr = String::createWithFormat("%d", score)->getCString();
        _scoreLabel->setString(scoreStr);
    }
}




