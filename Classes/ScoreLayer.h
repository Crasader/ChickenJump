#ifndef __SCORELAYER_H__
#define __SCORELAYER_H__

#include "cocos2d.h"

using namespace cocos2d;

class ScoreLayer : public cocos2d::LayerColor
{
public:
    virtual bool init();
    CREATE_FUNC(ScoreLayer);
    
    void updateScore(int score);
    
private:
    Vec2 _origin;
    Size _visibleSize;
    std::string imageScore = "score.png";
    Label* _scoreLabel;
};


#endif // __SCORELAYER_H__
