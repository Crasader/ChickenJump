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
    auto sprite = Sprite::create(imageScore);
    if (sprite) {
        sprite->setPosition(Vec2(_visibleSize.width - sprite->getContentSize().width * 2.5, this->getContentSize().height * 0.5));
        this->addChild(sprite);
    }

    // add score(text)
    _scoreLabel = Label::createWithTTF("0", font, _visibleSize.height * SCORE_FONT_SIZE);
    if (_scoreLabel) {
        _scoreLabel->setColor(Color3B::WHITE);
        _scoreLabel->setPosition(Vec2(_visibleSize.width - sprite->getContentSize().width, this->getContentSize().height * 0.44));
        this->addChild(_scoreLabel);
    }

    return true;
}

void ScoreLayer::updateScore(int score) {
    if (_scoreLabel) {
        std::string scoreStr = String::createWithFormat("%d", score)->getCString();
        _scoreLabel->setString(scoreStr);
    }
}




