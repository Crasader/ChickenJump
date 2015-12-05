#ifndef __SCORELAYER_H__
#define __SCORELAYER_H__

#include "cocos2d.h"

using namespace cocos2d;

class ScoreLayer : public cocos2d::LayerColor
{
public:
    virtual bool init();
    CREATE_FUNC(ScoreLayer);
    
    void initLifeSprites(int lives);
    void updateLife(int lives);
    void updateScore(int score);
    
private:
    Vec2 _origin;
    Size _visibleSize;
    
    std::string imageScore = "score.png";
    std::string imageLife = "life.png";
    Label* _scoreLabel;
    std::vector<Sprite*> _lifeSprites;
};


#endif // __SCORELAYER_H__
