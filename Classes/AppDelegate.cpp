#include "AppDelegate.h"
#include "GameLayer.h"

USING_NS_CC;

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

bool AppDelegate::applicationDidFinishLaunching() {
    // initialize director
    auto director = Director::getInstance();
    auto glview = director->getOpenGLView();
    if(!glview) {
        glview = GLViewImpl::create("My Game");
        director->setOpenGLView(glview);
    }
    
    // turn on display FPS
    director->setDisplayStats(true);

    // set FPS. the default value is 1.0/60 if you don't call this
    director->setAnimationInterval(1.0 / 60);
    
    // ********* Handling different screen size *********
    Size screenSize = glview->getFrameSize();
    Size designSize = Size(2048, 1536);

//    glview->setDesignResolutionSize(designSize.width, designSize.height, ResolutionPolicy::EXACT_FIT);
    
//    std::vector<std::string> searchPaths;
//    if (screenSize.width > 768) {
////        searchPaths.push_back("hd");
//        director->setContentScaleFactor(2);
//    } else  {
////        searchPaths.push_back("sd");
//        director->setContentScaleFactor(1);
//    }
//    auto fileUtils = FileUtils::getInstance();
//    fileUtils->setSearchPaths(searchPaths);
    // ********* Handling different screen size ********* [END]
    
    // ********* Handling different screen size (another way) *********
    glview->setDesignResolutionSize(designSize.width, designSize.height, ResolutionPolicy::EXACT_FIT);
    
    if (screenSize.height > 768) {
        director->setContentScaleFactor(1536/designSize.height);
    } else if (screenSize.height > 320) {
        director->setContentScaleFactor(768/designSize.height);
    } else {
        director->setContentScaleFactor(380/designSize.height);
    }
    // ********* Handling different screen size (another way) ********* [END]
    
    register_all_packages();

    // create a scene. it's an autorelease object
    auto scene = GameLayer::scene();

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
