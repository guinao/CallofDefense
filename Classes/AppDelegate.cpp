#include "cocos2d.h"
#include "CCEGLView.h"
#include "AppDelegate.h"
#//include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"
//#include "TowerPosEditorScene.h"
//#include "PosLoadUtil.h"
//#include "SceneManager.h"
//#include "CsvUtil.h"
//#include "I18N.h"
//#include "GlobalClient.h"
//#include "MMWidget\MMWinManager.h"
#include "DemoScene.h"
#include "SpaceAdventureScene.h"
#include "BootScene.h"

using namespace CocosDenshion;

USING_NS_CC;

AppDelegate::AppDelegate() 
{
}

AppDelegate::~AppDelegate() 
{
//		CCSpriteFrameCache::sharedSpriteFrameCache()->removeSpriteFrameByName("PvZres2/peashooter.plist");
		CCSpriteFrameCache::sharedSpriteFrameCache()->removeSpriteFrameByName("PvZres2/plants_type.plist");
		CCSpriteFrameCache::sharedSpriteFrameCache()->removeSpriteFrameByName("PvZres2/zombies_type.plist");
		CCSpriteFrameCache::sharedSpriteFrameCache()->removeSpriteFrameByName("PvZres2/plant_sun.plist");
		CCSpriteFrameCache::sharedSpriteFrameCache()->removeSpriteFrameByName("PvZres2/cardMenu.plist");

    SimpleAudioEngine::end();
}

bool AppDelegate::applicationDidFinishLaunching() {
	CCDirector *pDirector = CCDirector::sharedDirector();
	pDirector->setOpenGLView(CCEGLView::sharedOpenGLView());

	CCEGLView::sharedOpenGLView()->setDesignResolutionSize(800, 600, kResolutionShowAll);

	pDirector->setDisplayStats(true);

	pDirector->setAnimationInterval(1.0 / 60);

	//pDirector->runWithScene(DemoScene::scene());
	//SimpleAudioEngine::sharedEngine()->vibrate(1000);

	pDirector->runWithScene(SpaceAdventureScene::scene());
	//pDirector->runWithScene(BootScene::scene());
	/* 调用场景管理器切换场景 */
    //SceneManager::sharedSceneManager()->changeScene(SceneManager::en_DemoScene);
    return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground()
{
    CCDirector::sharedDirector()->stopAnimation();

    SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground()
{
    CCDirector::sharedDirector()->startAnimation();

    SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();
}
