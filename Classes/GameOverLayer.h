#ifndef __GAMEOVER_LAYER_H__
#define __GAMEOVER_LAYER_H__

#include <cocos2d.h>
#include <UIWidget.h>

using namespace cocos2d;

class Stage;

class GameOverLayer : public cocos2d::LayerColor
{
public:
//    static cocos2d::Scene* createScene(unsigned int score, Stage& stage, bool isStageClear);
    virtual bool init();
    CREATE_FUNC(GameOverLayer);

    void prepare(unsigned int score, Stage const& stage, bool isStageClear);

private:
    void addHighscoreLabel();
    void addScoreLabel();
    void addMainMenu();
    void saveStatsAndUnlockNextStage();
    void updateDifficultyLevel();
    void mainMenuClicked(Ref const* ref, cocos2d::ui::Widget::TouchEventType const& eEventType);
    
    Vec2 _origin;
    Size _visibleSize;
};

#endif // __GAMEOVER_LAYER_H__
