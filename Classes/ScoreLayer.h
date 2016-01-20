#ifndef __SCORELAYER_H__
#define __SCORELAYER_H__

#include "cocos2d.h"

class ScoreLayer : public cocos2d::LayerColor
{
public:
    virtual bool init();
    CREATE_FUNC(ScoreLayer);
    
    void initLifeSprites(int lives);
    void updateLife(int lives);
    void updateScore(int score);
    
private:
    cocos2d::Vec2 _origin;
    cocos2d::Size _visibleSize;
    
    std::string imageScore = "score.png";
    std::string imageLife = "life.png";
    cocos2d::Label* _scoreLabel;
    std::vector<cocos2d::Sprite*> _lifeSprites;
};


#endif // __SCORELAYER_H__
