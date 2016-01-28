#ifndef __PAUSELAYER_H__
#define __PAUSELAYER_H__

#include "cocos2d.h"
#include <UILayout.h>
#include <UIButton.h>

class PauseLayer : public cocos2d::LayerColor
{
public:
    virtual bool init();
    CREATE_FUNC(PauseLayer);
    
private:
    void createMenus();
    void createAdLayout();
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
    cocos2d::ui::Layout* _ad;
    
    cocos2d::Vec2 _origin;
    cocos2d::Size _visibleSize;
};


#endif // __PAUSELAYER_H__
