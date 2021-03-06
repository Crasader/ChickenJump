#ifndef __GAME_LAYER_H__
#define __GAME_LAYER_H__

#include <cocos2d.h>

#include <UILoadingBar.h>

#include "Chicken.h"
#include "Collectable.h"
#include "GameOverHUD.h"
#include "LayerBackground.h"
#include "LayerGround.h"
#include "LayerTwo.h"
#include "PauseHUD.h"
#include "ScoreHUD.h"
#include "SpecialCollectable.h"
#include "Stage.h"
#include "Trampoline.h"

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
    static cocos2d::Scene* createScene(Stage const& stage);
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    
    // implement the "static create()" method manually
    CREATE_FUNC(GameLayer);
    

    static GameLayer* getInstance();
    Stage getStage();
    std::shared_ptr<Chicken> getChicken() { return _chicken; }
    void pauseGame(cocos2d::Ref const* sender);
    void resumeClicked(cocos2d::Ref const* sender);
    void resumeGame(cocos2d::Ref const* sender);
    
    // contact listners
    bool onContactBegin(cocos2d::PhysicsContact const& contact);
    
    // touch listners
    virtual bool onTouchBegan(cocos2d::Touch const* touch, cocos2d::Event const* event);
    virtual void onTouchEnded(cocos2d::Touch const* touch, cocos2d::Event const* event);
    virtual void onTouchMoved(cocos2d::Touch const* touch, cocos2d::Event const* event);
    
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
    void elapsedTime(float tick);
    void endOfStage();
    void focusOnCharacter();
    void gameOver(int stageCompletionPercentage);
    void handleCollectableConsumption(cocos2d::Sprite* collectable);
    void initScoreHUDLives();
    void jump(float trampolinePositionY);
    void lastLifeExploded();
    void releaseTouch();
    void removeCollectable(cocos2d::Sprite* collectable);
    void removeSpecialCollectable(cocos2d::Sprite* collectable);
    void showUnlockedItem(Stage const& stage);
    void spawnCloud(float dt);
    void spawnCollectable();
    void spawnSpecialObject();
    void speedUp();
    void updateCollectables(float speed);
    void updateInvisibilityStopwatch(float dt);
    void updateMagnetStopwatch(float dt);
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
    std::vector<cocos2d::Sprite*> _collectables;
    std::vector<cocos2d::Sprite*> _specialCollectables;
    GameState _state;
    Sequence* _sequence;

    GameOverHUD* _gameOverHUD;
    PauseHUD* _pauseHUD;
    ScoreHUD* _scoreHUD;
    std::shared_ptr<Collectable> _collectable;
    std::shared_ptr<SpecialCollectable> _specialCollectable;
    int _totalEggs;
    int _totalPizzas;

    cocos2d::Sprite* _finger;
    cocos2d::Sprite* _unlockedItem;
    cocos2d::Label* _loading;
    cocos2d::Menu* _pauseMenu;
    int _score;
    int _collectedPizzas;
    
    float _stageLength;
    float _stageRemaining;
    float _distanceForNewCollectables;
    float _distanceForNewSpecialObject;

    cocos2d::Vec2 _lineStartPoint;
    cocos2d::Vec2 _lineEndPoint;
    
    cocos2d::Vec2 _origin;
    cocos2d::Size _visibleSize;
    
    unsigned int _elapsedTime; // seconds
};


#endif // __GAME_LAYER_H__







