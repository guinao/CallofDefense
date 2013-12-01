#include "SceneManager.h"
#include "TowerPosEditorScene.h"
#include "TollgateScene.h"
#include "GlobalClient.h"
#include "TollgateSelectScene.h"
#include "WinScene.h"
#include "GameOverScene.h"
#include "DemoScene.h"

SceneManager* SceneManager::mSceneManager = NULL;

SceneManager* SceneManager::sharedSceneManager() {
    if(mSceneManager == NULL) {
        mSceneManager = new SceneManager();
        if(mSceneManager && mSceneManager->init()) {
            mSceneManager->autorelease();
        }
        else {
            CC_SAFE_DELETE(mSceneManager);
            mSceneManager = NULL;
        }
    }

    return mSceneManager;
}

bool SceneManager::init() {

    return true;
}

void SceneManager::changeScene( EnumSceneType enScenType ) {
    CCScene* pScene = NULL;

    switch (enScenType) {
    case en_TollgateScene: /* 关卡场景 */
		CCLOG("Tollgate Scene");
		pScene = TollgateScene::scene();
		GlobalClient::sharedGlobalClient()->setCurTollgateScene((TollgateScene*)pScene);
        break;
    case en_TollgateEditorScene:    /* 关卡编辑器场景 */
		CCLOG("Scene TollgateEditor");
        pScene = TowerPosEditorScene::scene();
        break;
	case en_TollgateSelectScene:	/* 关卡选择场景 */
		CCLOG("Scene Pick Level");
		pScene = TollgateSelectScene::scene();
		break;
	case en_WinScene:		/* 胜利场景 */
		CCLOG("Scene Game Win");
		pScene = WinScene::scene();
		break;
	case en_GameOverScene:	/* 游戏结束场景 */
		CCLOG("Scene Game Over");
		pScene = GameOverScene::scene();
		break;
	case en_DemoScene:
		CCLOG("Demo Scene");
		pScene = DemoScene::scene();
		break;
    }

    if(pScene == NULL) {
        return;
    }

	CCDirector* pDirector = CCDirector::sharedDirector();
	CCScene* curScene = pDirector->getRunningScene();
	if(curScene == NULL) {
		pDirector->runWithScene(pScene);
	}
	else {
		pDirector->replaceScene(pScene);
	}
}
