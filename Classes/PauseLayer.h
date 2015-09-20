#ifndef __MAINMENU_SCENE_H__
#define __MAINMENU_SCENE_H__

#include "cocos2d.h"

using namespace cocos2d;

class PauseLayer : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();
    void menuResumeCallback(cocos2d::Ref* pSender);
    void menuExitCallback(cocos2d::Ref* pSender);
    CREATE_FUNC(PauseLayer);
};


#endif // __MAINMENU_SCENE_H__
