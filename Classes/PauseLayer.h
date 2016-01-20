#ifndef __PAUSELAYER_H__
#define __PAUSELAYER_H__

#include "cocos2d.h"
#include <UIWidget.h>

using namespace cocos2d;

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

    void mainMenuClicked(Ref const* ref, cocos2d::ui::Widget::TouchEventType const& eEventType);
    void restartClicked(Ref const* ref, cocos2d::ui::Widget::TouchEventType const& eEventType);
    void toggleSound(Ref const* ref, cocos2d::ui::Widget::TouchEventType const& eEventType);
    void toggleMusic(Ref const* ref, cocos2d::ui::Widget::TouchEventType const& eEventType);

private:
    Vec2 _origin;
    Size _visibleSize;
};


#endif // __PAUSELAYER_H__
