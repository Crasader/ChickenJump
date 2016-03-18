#ifndef __PAUSE_HUD_H__
#define __PAUSE_HUD_H__

#include "cocos2d.h"
#include <UILayout.h>
#include <UIButton.h>

class PauseHUD : public cocos2d::LayerColor
{
public:
    virtual bool init();
    CREATE_FUNC(PauseHUD);
    
private:
    void createMenus();
    
    void addResumeButton();
    void addRestartButton();
    void addMainMenuButton();
    void addSoundButton();
    void addMusicButton();

    void mainMenuClicked(cocos2d::Ref const* ref, cocos2d::ui::Widget::TouchEventType const& eEventType);
    void restartClicked(cocos2d::Ref const* ref, cocos2d::ui::Widget::TouchEventType const& eEventType);
    void toggleSound(cocos2d::Ref const* ref, cocos2d::ui::Widget::TouchEventType const& eEventType);
    void toggleMusic(cocos2d::Ref const* ref, cocos2d::ui::Widget::TouchEventType const& eEventType);

private:
    cocos2d::ui::Button* _btnResume;
    cocos2d::ui::Button* _btnRestart;
    cocos2d::ui::Button* _btnMainMenu;
    cocos2d::ui::Button* _btnSoundToggle;
    cocos2d::ui::Button* _btnMusicToggle;
    
    cocos2d::Vec2 _origin;
    cocos2d::Size _visibleSize;
};


#endif // __PAUSE_HUD_H__
