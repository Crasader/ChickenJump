#ifndef __SCORELAYER_H__
#define __SCORELAYER_H__

#include "cocos2d.h"

#include <UILoadingBar.h>
#include <UIListView.h>

class ScoreLayer : public cocos2d::LayerColor
{
public:
    virtual bool init();
    CREATE_FUNC(ScoreLayer);
    
    void initLifeSprites(int lives);
    void startStopwatch(int type);
    void tick(int type);
    void updateLife(int lives);
    void updateScore(int score);
    void updateInvisibilityTimer(int remaining);
    void updateMagnetTimer(int remaining);
    
private:
    void addScore();
    void addScoreIcon();
    void addMagnetStopwatch();
    void addInvisibilityStopwatch();
    
    std::string imageScore = "score.png";
    std::string imageLife = "life.png";
    cocos2d::Sprite* _scoreIcon;
    cocos2d::Label* _scoreLabel;
    std::vector<cocos2d::Sprite*> _lifeSprites;
    cocos2d::ui::LoadingBar* _invisibilityStopwatch;
    cocos2d::ui::LoadingBar* _magnetStopwatch;
    
    cocos2d::Vec2 _origin;
    cocos2d::Size _visibleSize;
};


#endif // __SCORELAYER_H__
