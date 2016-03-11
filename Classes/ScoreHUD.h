#ifndef __SCORE_HUD_H__
#define __SCORE_HUD_H__

#include "cocos2d.h"

#include <UILoadingBar.h>
#include <UIListView.h>

class ScoreHUD : public cocos2d::LayerColor
{
public:
    virtual bool init();
    CREATE_FUNC(ScoreHUD);
    
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
    
    cocos2d::Sprite* _scoreIcon;
    cocos2d::Label* _scoreLabel;
    std::vector<cocos2d::Sprite*> _lifeSprites;
    cocos2d::Sprite* _invisibilityIcon;
    cocos2d::ui::LoadingBar* _invisibilityStopwatch;
    cocos2d::Sprite* _magnetIcon;
    cocos2d::ui::LoadingBar* _magnetStopwatch;
    
    cocos2d::Vec2 _origin;
    cocos2d::Size _visibleSize;
};


#endif // __SCORE_HUD_H__
