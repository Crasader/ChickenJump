#ifndef __POPUPLAYER_H__
#define __POPUPLAYER_H__

#include "cocos2d.h"

using namespace cocos2d;

class PopupLayer : public cocos2d::LayerColor
{
public:
    virtual bool init();
    CREATE_FUNC(PopupLayer);
    
//    void menuResumeCallback(cocos2d::Ref* pSender);
    void menuExitCallback(cocos2d::Ref* pSender);
    
private:
    Vec2 _origin;
    Size _visibleSize;
};


#endif // __POPUPLAYER_H__
