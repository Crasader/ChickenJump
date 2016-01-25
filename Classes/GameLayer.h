#ifndef __GAME_LAYER_H__
#define __GAME_LAYER_H__

#include <cocos2d.h>

#include <UILoadingBar.h>

#include "Chicken.h"
#include "Collectable.h"
#include "GameOverLayer.h"
#include "LayerBackground.h"
#include "LayerGround.h"
#include "LayerTwo.h"
#include "PauseLayer.h"
#include "ScoreLayer.h"
#include "SpecialCollectable.h"
#include "Stage.h"
#include "Trampoline.h"

using namespace cocos2d;

typedef enum {
    init,
    started,
    paused,
    finishing,
    finished,
    terminate
    
} GameState;

class GameLayer : public cocos2d::LayerColor
{
public:
    static cocos2d::Scene* createScene(Stage stage);
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    
    // implement the "static create()" method manually
    CREATE_FUNC(GameLayer);
    

    static GameLayer* getInstance();
    void pauseGame(cocos2d::Ref const* sender);
    void resumeClicked(cocos2d::Ref const* sender);
    void resumeGame(cocos2d::Ref const* sender);
    
    // contact listners
    bool onContactBegin(cocos2d::PhysicsContact const& contact);
    
    // touch listners
    virtual bool onTouchBegan(Touch const* touch, Event const* event);
    virtual void onTouchEnded(Touch const* touch, Event const* event);
    virtual void onTouchMoved(Touch const* touch, Event const* event);
    
    void update(float dt);
    
    virtual void onEnterTransitionDidFinish();
    
private:
    void addBG();
    void addChicken();
    void addContactListners();
    void addExplosionEffect();
    void addFirstLayer();
    void addGroundLayer();
    void addLoadingWheel();
    void addPauseMenu();
    void addProgressBar();
    void addSecondLayer();
    void addTouchListners();
    void addTutorial();
    void cleanTrampoline();
    void drawNewTrampoline();
    void endOfStage();
    void focusOnCharacter();
    void gameOver(bool hasStageFinished);
    void handleCollectableConsumption(Sprite* collectable);
    void initScoreHUDLives();
    void jump(float trampolinePositionY);
    void lastLifeExploded();
    void releaseTouch();
    void removeCollectable(Sprite* collectable);
    void removeSpecialCollectable(Sprite* collectable);
    void spawnCloud(float dt);
    void spawnCollectable();
    void spawnSpecialObject();
    void speedUp();
    void updateCollectables(float speed);
    void updateSpecialCollectables(float speed);
    void updateScoreLabel();
    void updateStageComplesion(float speed);
    
    static GameLayer* _instance;
    
    std::shared_ptr<LayerBackground> _layerBackground;
    std::shared_ptr<LayerGround> _layerGround;
    std::shared_ptr<LayerTwo> _layerTwo;
    Trampoline* _trampoline;
    std::shared_ptr<Chicken> _chicken;
    cocos2d::ui::LoadingBar* _progressBar;
    std::vector<Sprite*> _collectables;
    std::vector<Sprite*> _specialCollectables;
    GameState _state;
    Sequence* _sequence;

    GameOverLayer* _gameOverHUD;
    PauseLayer* _pauseHUD;
    ScoreLayer* _scoreHUD;
    std::shared_ptr<Collectable> _collectable;
    std::shared_ptr<SpecialCollectable> _specialCollectable;

    Sprite* _finger;
    Label* _loading;
    Menu* _pauseMenu;
    unsigned int _score;
    
    float _stageLength;
    float _stageRemaining;
    float _distanceForNewCollectables;
    float _distanceForNewSpecialObject;

    Vec2 _lineStartPoint;
    Vec2 _lineEndPoint;
    
    Vec2 _origin;
    Size _visibleSize;

};


#endif // __GAME_LAYER_H__







