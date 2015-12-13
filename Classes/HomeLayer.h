#ifndef __HOMELAYER_H__
#define __HOMELAYER_H__

#include "cocos2d.h"

#include "FloatingChicken.h"
#include "SettingsMenuLayer.h"

using namespace cocos2d;

class HomeLayer : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();
    virtual bool init();
    CREATE_FUNC(HomeLayer);

    void update(float dt);
    
    virtual void onExit() {
        // Cleanup
        Layer::onExit();
        Layer::cleanup();
        TextureCache::getInstance()->removeUnusedTextures();
    }
private:
    void addBackground();
    void addFlyingChickens();
    void addGround();
    void addLogo();
    void addPlayMenu();
    void gotoMainMenuLayer(cocos2d::Ref* sender);
    void initStage();
    
    FloatingChicken* _flyingChicken1;
    FloatingChicken* _flyingChicken2;
    FloatingChicken* _flyingChicken4;
    
    SettingsMenuLayer* _settingsHUD;
    
    Vec2 _origin;
    Size _visibleSize;
};

#endif // __HOMELAYER_H__
