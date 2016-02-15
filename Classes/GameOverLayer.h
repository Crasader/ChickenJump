#ifndef __GAMEOVER_LAYER_H__
#define __GAMEOVER_LAYER_H__

#include <cocos2d.h>
#include <UIWidget.h>
#include <UIButton.h>

class Stage;

class GameOverLayer : public cocos2d::LayerColor
{
public:
    virtual bool init();
    CREATE_FUNC(GameOverLayer);

    void setup(Stage const& stage, unsigned int score, unsigned int timeTaken, bool isStageClear);

private:
    void addHighscoreLabel();
    void addMainMenu();
    void addRestartButton();
    void addScoreBoard();
    void addScoreLabel();
    void addStars();
    void addTimerLogoAndLabel();
    
    void prepare(unsigned int timeTaken, bool isNewHighscore);
    void saveStatsAndUnlockNextStage(bool isStageClear);
    void mainMenuClicked(cocos2d::Ref const* ref, cocos2d::ui::Widget::TouchEventType const& eEventType);
    void restartClicked(Ref const* ref, cocos2d::ui::Widget::TouchEventType const& eEventType);
    void newHighscoreCelebration();
    void addFirework();
    
    cocos2d::Sprite* _scoreBoard;
    cocos2d::Sprite* _timerSprite;
    cocos2d::Label* _highScoreLabel;
    cocos2d::Label* _scoreLabel;
    cocos2d::Label* _timeLabel;
    cocos2d::ui::Button* _btnMainMenu;
    cocos2d::ui::Button* _btnRestart;
    cocos2d::Sprite* _star1;
    cocos2d::Sprite* _star2;
    cocos2d::Sprite* _star3;
    std::vector<cocos2d::Sprite*> _stars;
    
    cocos2d::Vec2 _origin;
    cocos2d::Size _visibleSize;
};

#endif // __GAMEOVER_LAYER_H__
