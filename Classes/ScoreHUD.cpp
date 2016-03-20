#include "ScoreHUD.h"

#include <UIListView.h>

#include "Constants.h"
#include "GameLayer.h"

using namespace cocos2d;
using namespace ui;

static const std::string imageScore = "icon_score.png";
static const std::string imageLife = "life.png";
static const std::string imageSandwatchMagnet = "sandwatch.png";
static const std::string imageIconMagnet = "icon_magnet.png";
static const std::string imageIconInvisibility = "icon_invisibility.png";

bool ScoreHUD::init()
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
    addScoreIcon();

    // add score(text)
    addScore();
    
    // sandwatches
    addMagnetStopwatch();
    addInvisibilityStopwatch();
    
    // Initialize number of life sprites only in stages where life matters
    updateLife(0);
    if (GameLayer::getInstance()->getStage().getDifficulty() > 2) {
        initLifeSprites(CHICKEN_LIVES_MAX);
        updateLife(CHICKEN_LIVES);
    }
    
    return true;
}

void ScoreHUD::addMagnetStopwatch() {
    // Icon
    _magnetIcon = Sprite::create(imageIconMagnet);
    if (not _magnetIcon) { return; }
    _magnetIcon->setPosition(Vec2(this->getContentSize().width * 0.55, this->getContentSize().height * 0.5));
    _magnetIcon->setVisible(false);
    this->addChild(_magnetIcon, BackgroundLayer::layerTouch);

    // Sandwatch
    _magnetStopwatch = cocos2d::ui::LoadingBar::create();
    if (not _magnetStopwatch) { return; }
    
    _magnetStopwatch->loadTexture(imageSandwatchMagnet);
    _magnetStopwatch->setColor(Color3B::ORANGE);
    _magnetStopwatch->setPercent(0);
    _magnetStopwatch->setPosition(Vec2(this->getContentSize().width * 0.625, this->getContentSize().height * 0.5));
    this->addChild(_magnetStopwatch, BackgroundLayer::layerTouch);
}

void ScoreHUD::addInvisibilityStopwatch() {
    // Icon
    _invisibilityIcon = Sprite::create(imageIconInvisibility);
    if (not _invisibilityIcon) { return; }
    _invisibilityIcon->setPosition(Vec2(this->getContentSize().width * 0.725, this->getContentSize().height * 0.5));
    _invisibilityIcon->setVisible(false);
    this->addChild(_invisibilityIcon, BackgroundLayer::layerTouch);
    
    // Sandwatch
    _invisibilityStopwatch = cocos2d::ui::LoadingBar::create();
    if (not _invisibilityStopwatch) { return; }
    
    _invisibilityStopwatch->loadTexture(imageSandwatchMagnet);
    _invisibilityStopwatch->setColor(Color3B::ORANGE);
    _invisibilityStopwatch->setPercent(0);
    _invisibilityStopwatch->setPosition(Vec2(this->getContentSize().width * 0.8, this->getContentSize().height * 0.5));
    this->addChild(_invisibilityStopwatch, BackgroundLayer::layerTouch);
}

// 1:Magnet 2:Invisibility
void ScoreHUD::startStopwatch(int type) {
    switch (type) {
        case 1:
            if (not _magnetStopwatch) { return; }
            _magnetStopwatch->setPercent(100);
            if (_magnetIcon) { _magnetIcon->setVisible(true); }
            break;
        case 2:
            if (not _invisibilityStopwatch) { return; }
            _invisibilityStopwatch->setPercent(100);
            if (_invisibilityIcon) { _invisibilityIcon->setVisible(true); }
            break;
        default:
            break;
    }
}

// 1:Magnet 2:Invisibility
void ScoreHUD::tick(int type) {
    // magnet_effect -= 5; means: 100/5 = 20 seconds
    switch (type) {
        case 1:
            if (_magnetStopwatch) {
                _magnetStopwatch->setPercent(_magnetStopwatch->getPercent() - 100/MAGNET_EFFECT_DURATION);
            }
            
            if (_magnetStopwatch->getPercent() <= 0 and _magnetIcon) {
                _magnetIcon->setVisible(false);
                
                // reset magnet effect
                GameLayer::getInstance()->getChicken()->setMagnetEffect(false);
            }
            
            break;
        case 2:
            if (_invisibilityStopwatch) {
                _invisibilityStopwatch->setPercent(_invisibilityStopwatch->getPercent() - 100/INVISIBILITY_EFFECT_DURATION);
            }
            
            if (_invisibilityStopwatch->getPercent() <= 0 and _invisibilityIcon) {
                _invisibilityIcon->setVisible(false);
                
                // make our chicken visible
                GameLayer::getInstance()->getChicken()->makeVisible();
            }
            
            break;
        default:
            break;
    }
}

void ScoreHUD::addScore() {
    _scoreLabel = Label::createWithTTF("0", font, _visibleSize.height * SCORE_FONT_SIZE_BIG);
    if (not _scoreLabel) { return; }

    _scoreLabel->setColor(Color3B::WHITE);
    _scoreLabel->setPosition(Vec2(_visibleSize.width - _scoreIcon->getContentSize().width, this->getContentSize().height * 0.44));
    this->addChild(_scoreLabel);
}

void ScoreHUD::addScoreIcon(){
    _scoreIcon = Sprite::create(imageScore);
    if (not _scoreIcon) { return; }
    _scoreIcon->setPosition(Vec2(_visibleSize.width - _scoreIcon->getContentSize().width * 2.5, this->getContentSize().height * 0.5));
    this->addChild(_scoreIcon);
}

void ScoreHUD::initLifeSprites(int lives) {
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

void ScoreHUD::updateLife(int lives) {
    for (int i = 0; i < _lifeSprites.size(); ++i) {
        _lifeSprites.at(i)->setVisible(true);
        if (i >= lives) {
            _lifeSprites.at(i)->setVisible(false);
        }
    }
}

void ScoreHUD::updateScore(int score) {
    if (_scoreLabel) {
        std::string scoreStr = StringUtils::format("%d", score);
        _scoreLabel->setString(scoreStr);
    }
}




