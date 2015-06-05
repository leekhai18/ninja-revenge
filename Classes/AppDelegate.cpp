#include "AppDelegate.h"
#include "MainMenuScene.h"

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
        glview = GLViewImpl::create("Ninja Revenge");
        director->setOpenGLView(glview);
    }

    // turn on display FPS
    director->setDisplayStats(true);

    // set FPS. the default value is 1.0/60 if you don't call this
    director->setAnimationInterval(1.0 / 60);

	auto screenSize = glview->getFrameSize();
	auto designSize = Size(480, 320);

	auto fileUtils = FileUtils::getInstance();
	std::vector<std::string> searchPaths;

	searchPaths.push_back("hd");
	searchPaths.push_back("hd/animations");
	searchPaths.push_back("hd/sprites");
	searchPaths.push_back("x2");
	searchPaths.push_back("sound");
	
	fileUtils->setSearchPaths(searchPaths);

	//init armature resource
	ArmatureDataManager::getInstance()->addArmatureFileInfo("player/player.ExportJson");
	ArmatureDataManager::getInstance()->addArmatureFileInfo("enemy1/enemy1.ExportJson");
	ArmatureDataManager::getInstance()->addArmatureFileInfo("enemy2/enemy2.ExportJson");
	ArmatureDataManager::getInstance()->addArmatureFileInfo("story/story.ExportJson");
	ArmatureDataManager::getInstance()->addArmatureFileInfo("dirt/dirt.ExportJson");

	//director->setContentScaleFactor(0.50f);
    register_all_packages();

    // create a scene. it's an autorelease object
    auto scene = MainMenuScene::createScene();

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
