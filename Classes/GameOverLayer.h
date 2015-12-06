#ifndef __GAMEOVER_LAYER_H__
#define __GAMEOVER_LAYER_H__

#include <cocos2d.h>

using namespace cocos2d;

class Stage;

class GameOverLayer : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene(unsigned int score, Stage& stage, bool isStageClear);

    virtual bool init();
    
    CREATE_FUNC(GameOverLayer);
    
    virtual void onExit() {
        // Cleanup
        Layer::onExit();
        Layer::cleanup();
        TextureCache::getInstance()->removeUnusedTextures();
    }

private:
    void gotoMainMenuLayer(cocos2d::Ref* sender);
    
    Vec2 _origin;
    Size _visibleSize;
};

#endif // __GAMEOVER_LAYER_H__
