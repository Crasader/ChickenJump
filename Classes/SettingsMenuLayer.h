#ifndef __SETTINGSMENU_LAYER_H__
#define __SETTINGSMENU_LAYER_H__

#include "cocos2d.h"

using namespace cocos2d;

class SettingsMenuLayer : public cocos2d::LayerColor
{
public:
    virtual bool init();
    CREATE_FUNC(SettingsMenuLayer);
    
private:
    void addSettingsAndAllSubMenues();
    void settingsClicked(Ref* ref);
    void toggleSound(Ref* ref);
    void toggleMusic(Ref* ref);
    
    Menu* _settingsMenu;
    Menu* _soundToggleMenu;
    Menu* _musicToggleMenu;
    
    bool _isCollapsed;
    
    Vec2 _origin;
    Size _visibleSize;    
};


#endif // __SETTINGSMENU_LAYER_H__
