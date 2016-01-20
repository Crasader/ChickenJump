#ifndef __SETTINGSMENU_LAYER_H__
#define __SETTINGSMENU_LAYER_H__

#include "cocos2d.h"

#include <UIWidget.h>

class SettingsMenuLayer : public cocos2d::LayerColor
{
public:
    virtual bool init();
    CREATE_FUNC(SettingsMenuLayer);
    
private:
    void createMenues();
    void addSoundButton();
    void addMusicButton();
    void settingsClicked(cocos2d::Ref const* ref, cocos2d::ui::Widget::TouchEventType const& eEventType);
    void toggleSound(cocos2d::Ref const* ref, cocos2d::ui::Widget::TouchEventType const& eEventType);
    void toggleMusic(cocos2d::Ref const* ref, cocos2d::ui::Widget::TouchEventType const& eEventType);
        
    bool _isCollapsed;
    
    cocos2d::Vec2 _origin;
    cocos2d::Size _visibleSize;
};


#endif // __SETTINGSMENU_LAYER_H__
