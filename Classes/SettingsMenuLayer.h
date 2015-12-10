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
    
    Menu* _settingsMenu;
    Menu* _muteToggleMenu;
    
    bool _isCollapsed;
    
    Vec2 _origin;
    Size _visibleSize;
    
    std::string imageBtnSettings = "btn_settings.png";
    std::string imageBtnSettingsClicked = "btn_settingsclicked.png";
    std::string imageBtnMute = "btn_mute.png";
    std::string imageBtnUnMute = "btn_unmute.png";
    std::string imageBtnMuteMusic = "btn_mute.png";
    std::string imageBtnUnMuteMusic = "btn_unmute.png";
};


#endif // __SETTINGSMENU_LAYER_H__
