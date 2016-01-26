#include "GameOverLayer.h"

#include "Constants.h"
#include "MainMenuLayer.h"
#include "Stage.h"
#include "StageStatus.h"

using namespace cocos2d;
using namespace ui;

static unsigned int _score = 0;
static Stage _stage;

static const std::string imageBtnMainMenu = "btn_menu.png";

void GameOverLayer::setup(unsigned int score, Stage const& stage, bool isStageClear)
{
    _stage = stage;
    _score = score;
    _isStageClear = isStageClear;
    
    prepare();
    saveStatsAndUnlockNextStage();
}

bool GameOverLayer::init()
{
    if ( !LayerColor::initWithColor(Color4B(0, 0, 0, 128)) ) {
        return false;
    }
    
    _origin = Director::getInstance()->getVisibleOrigin();
    _visibleSize = Director::getInstance()->getVisibleSize();
    
    _isStageClear = false;
    
    this->setContentSize(Size(_visibleSize.width, _visibleSize.height));
    this->setPosition(0, 0);
    
    addHighscoreLabel();
    addScoreLabel();
    addMainMenu();
    addStars();

    return true;
}

void GameOverLayer::addHighscoreLabel() {
    _highScoreLabel = Label::createWithTTF("", font, _visibleSize.height * SCORE_FONT_SIZE);
    if (not _highScoreLabel) { return; }
    _highScoreLabel->setColor(Color3B::WHITE);
    _highScoreLabel->setPosition(_visibleSize.width * 0.5, _visibleSize.height * 0.65);
    this->addChild(_highScoreLabel, BackgroundLayer::layerChicken);
}

void GameOverLayer::addMainMenu() {
    _btnMainMenu = Button::create(imageBtnMainMenu, imageBtnMainMenu);
    if (not _btnMainMenu) { return; }
    _btnMainMenu->addTouchEventListener(CC_CALLBACK_2(GameOverLayer::mainMenuClicked, this));
    _btnMainMenu->setPosition(Point(_visibleSize.width / 2 + _origin.x, _visibleSize.height * 0.3 + _origin.y));
    this->addChild(_btnMainMenu, BackgroundLayer::layerChicken);
}

void GameOverLayer::addScoreLabel() {
    _scoreLabel = Label::createWithTTF("", font, _visibleSize.height * SCORE_FONT_SIZE);
    if (not _scoreLabel) { return; }
    _scoreLabel->setColor(Color3B::WHITE);
    _scoreLabel->setPosition(_visibleSize.width / 2 + _origin.x, _visibleSize.height * 0.5 + _origin.y);
    this->addChild(_scoreLabel, BackgroundLayer::layerChicken);
}

void GameOverLayer::addStars() {
    _star1 = Sprite::create("star_empty.png");
    if (_star1) {
        _star1->setPosition(_visibleSize.width * 0.5 - _star1->getContentSize().width * 1.5, _visibleSize.height * 0.65);
        this->addChild(_star1, BackgroundLayer::layerChicken);
        _stars.push_back(_star1);
    }

    _star2 = Sprite::create("star_empty.png");
    if (_star2) {
        _star2->setPosition(_visibleSize.width * 0.5, _visibleSize.height * 0.7);
        this->addChild(_star2, BackgroundLayer::layerChicken);
        _stars.push_back(_star2);
    }

    _star3 = Sprite::create("star_empty.png");
    if (_star3) {
        _star3->setPosition(_visibleSize.width * 0.5 + _star1->getContentSize().width * 1.5, _visibleSize.height * 0.65);
        this->addChild(_star3, BackgroundLayer::layerChicken);
        _stars.push_back(_star3);
    }
}

void GameOverLayer::prepare() {
    // HIGHSCORE
    if (_stage.getName() == StageStatus::infinite and _highScoreLabel) {
        UserDefault* d = UserDefault::getInstance();
        auto highScore = d->getIntegerForKey(HIGHSCORE, 0);
        if (_score > highScore) {
            highScore = _score;
            d->setIntegerForKey(HIGHSCORE, highScore);
            d->flush();
        }
        
        std::string highScoreStr = String::createWithFormat("HighScore: %d", highScore)->getCString();
        _highScoreLabel->setString(highScoreStr);
    }

    // SCORE
    if (_scoreLabel) {
        std::string scoreStr = String::createWithFormat("Score: %d", _score)->getCString();
        _scoreLabel->setString(scoreStr);
    }
    
    // STAR
    if (_stage.getName() != StageStatus::infinite) {
        int star = RandomHelper::random_int(1, 3);
        for (int i = 0; i < star; ++i) {
            _stars.at(i)->setTexture("star.png");
        }
    }
}

void GameOverLayer::saveStatsAndUnlockNextStage() {
    try {
        Stage ss(_stage.getName(),
                 _stage.getImageFile(),
                 _stage.getClickedImageFile(),
                 _stage.getLockedImageFile(),
                 _stage.getDifficulty(),
                 _stage.getScore(),
                 _stage.getStar(),
                 _stage.isUnlocked(),
                 _stage.isPlayed());
        
        StageStatus::saveStage(ss);

        if (_isStageClear) { StageStatus::unlockNextStage(ss); }
    }
    catch(...) {
        CCLOG("Coulnd't store stage info from GameOver");
    }
}

void GameOverLayer::mainMenuClicked(const Ref* ref, const cocos2d::ui::Widget::TouchEventType& eEventType) {
    if (eEventType != ui::Widget::TouchEventType::ENDED) { return; }

    auto d = Director::getInstance();
    if (d->isPaused()) {
        d->resume();
    }
    
    BackButton<MainMenuLayer>* mainMenu = new BackButton<MainMenuLayer>();
    if (not mainMenu) { return; }
    mainMenu->goBack(this);
}














