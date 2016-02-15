#ifndef __MAINMENU_LAYER_H__
#define __MAINMENU_LAYER_H__

#include <cocos2d.h>
#include <UIPageView.h>

#include "BackButton.h"
#include "HomeLayer.h"

class Stage;

class MainMenuLayer : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();
    
    CREATE_FUNC(MainMenuLayer);

private:
    void addBackground();
    void addBackButton();
    void addHeaderLabel();
    void addPageNavigationButtons();
    void addStages();
    void gotoGamePlayLayer(cocos2d::Ref const* sender, Stage const& stage);
    void menuSelectSgate(cocos2d::Ref const* sender, Stage const& stage);
    void pageScrollClicked(cocos2d::Ref const* ref, cocos2d::ui::Widget::TouchEventType const& eEventType);
    void pageViewEvent(cocos2d::Ref const* ref, cocos2d::ui::PageView::EventType const& eEventType);
    void selectLevel(std::string const& level);
    
    bool _countryFrance;
    BackButton<HomeLayer>* _backButton;
    
    Vec2 _origin;
    Size _visibleSize;
};

#endif // __MAINMENU_LAYER_H__
