#ifndef __SETTINGSMENU_LAYER_H__
#define __SETTINGSMENU_LAYER_H__

#include "cocos2d.h"

#include <UIWidget.h>

using namespace cocos2d;
using namespace cocos2d::ui;

class SettingsMenuLayer : public cocos2d::LayerColor
{
public:
    virtual bool init();
    CREATE_FUNC(SettingsMenuLayer);
    
private:
    void createMenues();
    void addSoundButton();
    void addMusicButton();
    void settingsClicked(const Ref* ref, const cocos2d::ui::Widget::TouchEventType& eEventType);
    void toggleSound(const Ref* ref, const cocos2d::ui::Widget::TouchEventType& eEventType);
    void toggleMusic(const Ref* ref, const cocos2d::ui::Widget::TouchEventType& eEventType);
        
    bool _isCollapsed;
    
    Vec2 _origin;
    Size _visibleSize;    
};


#endif // __SETTINGSMENU_LAYER_H__
