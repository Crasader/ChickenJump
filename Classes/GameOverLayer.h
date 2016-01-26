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

    void setup(unsigned int score, Stage const& stage, bool isStageClear);

private:
    void addHighscoreLabel();
    void addMainMenu();
    void addScoreLabel();
    void addStars();
    
    void prepare();
    void saveStatsAndUnlockNextStage();
    void mainMenuClicked(cocos2d::Ref const* ref, cocos2d::ui::Widget::TouchEventType const& eEventType);
    
    cocos2d::Label* _highScoreLabel;
    cocos2d::Label* _scoreLabel;
    cocos2d::ui::Button* _btnMainMenu;
    cocos2d::Sprite* _star1;
    cocos2d::Sprite* _star2;
    cocos2d::Sprite* _star3;
    std::vector<cocos2d::Sprite*> _stars;
    
    bool _isStageClear;
    
    cocos2d::Vec2 _origin;
    cocos2d::Size _visibleSize;
};

#endif // __GAMEOVER_LAYER_H__
