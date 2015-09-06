#include "AppDelegate.h"
#include "SplashScreenLayer.h"
#include "SimpleAudioEngine.h"

using namespace cocos2d;

AppDelegate::AppDelegate() {
    
}

AppDelegate::~AppDelegate()
{
}

//if you want a different context,just modify the value of glContextAttrs
//it will takes effect on all platforms
void AppDelegate::initGLContextAttrs()
{
    //set OpenGL context attributions,now can only set six attributions:
    //red,green,blue,alpha,depth,stencil
    GLContextAttrs glContextAttrs = {8, 8, 8, 8, 24, 8};
    
    GLView::setGLContextAttrs(glContextAttrs);
}

// If you want to use packages manager to install more packages,
// don't modify or remove this function
static int register_all_packages()
{
    return 0; //flag for packages manager
}

static Size smallResource  = Size(480, 320); // "iphone"
static Size mediumResource = Size(1024, 768); // "ipad"
static Size largeResource  = Size(2048, 1536); // "ipadhd"
static Size designResolution = Size(480, 320);

bool AppDelegate::applicationDidFinishLaunching() {
    // initialize director
    auto director = Director::getInstance();
    auto glview = director->getOpenGLView();
    
    if(!glview) {
        glview = GLViewImpl::create("ChickenJump");
        director->setOpenGLView(glview);
    }
    
    // turn on display FPS
    director->setDisplayStats(true);
    
    // set FPS. the default value is 1.0/60 if you don't call this
    director->setAnimationInterval(1.0 / 60);
    
    // Handling different screen size
    {
        Size screenSize = glview->getFrameSize();
        
        glview->setDesignResolutionSize(designResolution.width, designResolution.height, ResolutionPolicy::FIXED_WIDTH);
        
        std::vector<std::string> searchPaths;
        if (screenSize.height > mediumResource.height) {
            searchPaths.push_back("ipadhd");
            director->setContentScaleFactor(largeResource.height / designResolution.height);
        }
        else if (screenSize.width > smallResource.width) {
            searchPaths.push_back("ipad");
            director->setContentScaleFactor(mediumResource.height / designResolution.height);
        }
        else {
            searchPaths.push_back("iphone");
            director->setContentScaleFactor(smallResource.height / designResolution.height);
        }
        CCLOG("Path: %s", searchPaths.at(0).c_str());
        auto fileUtils = FileUtils::getInstance();
        fileUtils->setSearchPaths(searchPaths);
    }
    
    // Audio
    auto audioEngine = CocosDenshion::SimpleAudioEngine::getInstance();
    audioEngine->preloadEffect("jump.wav");
    audioEngine->preloadEffect("pickup_coin.wav");
    audioEngine->preloadEffect("bump.wav");
    audioEngine->setEffectsVolume(0.5f);
    
    
    register_all_packages();
    
    // create a scene. it's an autorelease object
    auto scene = SplashScreenLayer::createScene();
    
    // run
    director->runWithScene(scene);
    
    return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground() {
    Director::getInstance()->stopAnimation();
    
    // if you use SimpleAudioEngine, it must be pause
    // SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground() {
    Director::getInstance()->startAnimation();
    
    // if you use SimpleAudioEngine, it must resume here
    // SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
}
