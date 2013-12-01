#include "TollgateSelectScene.h"
#include "SceneManager.h"
#include "MMWidget\MMWinManager.h"
#include "GlobalParam.h"
#include "MMWidget\MMBase.h"
#include "MMWidget\MMRoundOprBtn.h"
#include "GlobalClient.h"
#include "GlobalPath.h"


CCScene* TollgateSelectScene::scene() {
    CCScene* scene = NULL;

    do {
        scene = CCScene::create();
        CC_BREAK_IF(! scene);

        TollgateSelectScene* layer = TollgateSelectScene::create();
        CC_BREAK_IF(! layer);

        scene->addChild(layer);
    } while (0);

    return scene;
}

bool TollgateSelectScene::init() {
    bool bRet = false;

    do {
        CC_BREAK_IF(! CCLayer::init());

        CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();

        /* 创建关卡选则菜单 */
        const char* norImg = "tollgate/choose_btn_nor.png";
        const char* lightImg = "tollgate/choose_btn_light.png";
        const char* disableImg = "tollgate/choose_btn_light.png";

        CCMenuItemImage* level_1_Item = CCMenuItemImage::create(norImg, lightImg, disableImg, this,
            menu_selector(TollgateSelectScene::level_1));
		level_1_Item->addChild(createLevelLab("1"));

        CCMenuItemImage* level_2_Item = CCMenuItemImage::create(norImg, lightImg, disableImg, this,
            menu_selector(TollgateSelectScene::level_2));
		level_2_Item->addChild(createLevelLab("2"));

//         CCMenuItemImage* level_3_Item = CCMenuItemImage::create(norImg, lightImg, disableImg, this,
//             menu_selector(TollgateSelectScene::level_3));
// 		level_3_Item->addChild(createLevelLab("3"));
// 
//         CCMenuItemImage* level_4_Item = CCMenuItemImage::create(norImg, lightImg, disableImg, this,
//             menu_selector(TollgateSelectScene::level_4));
// 		level_4_Item->addChild(createLevelLab("4"));
// 
//         CCMenuItemImage* level_5_Item = CCMenuItemImage::create(norImg, lightImg, disableImg, this,
//             menu_selector(TollgateSelectScene::level_5));
// 		level_5_Item->addChild(createLevelLab("5"));

        CCMenu* menu = CCMenu::create(level_1_Item, level_2_Item, NULL);
        menu->alignItemsHorizontallyWithPadding(20);
        menu->setPosition(ccp(visibleSize.width / 2, visibleSize.height / 2));
        this->addChild(menu);

        bRet = true;
    } while (0);

    return bRet;
}

CCLabelTTF* TollgateSelectScene::createLevelLab( const char* sLvl ) {
	CCLabelTTF* level_lab = CCLabelTTF::create(sLvl, PATH_FONT_PUBLIC, GlobalParam::PublicFontSizeLargest);
	level_lab->setColor(ccRED);
	level_lab->setPosition(ccp(60, 60));

	return level_lab;
}

void TollgateSelectScene::level_1(CCObject* pSender) {
    GlobalClient::sharedGlobalClient()->setiCurTollgateLevel(1);
    SceneManager::sharedSceneManager()->changeScene(SceneManager::en_TollgateScene);
}

void TollgateSelectScene::level_2(CCObject* pSender) {
    GlobalClient::sharedGlobalClient()->setiCurTollgateLevel(2);
    SceneManager::sharedSceneManager()->changeScene(SceneManager::en_TollgateScene);
}

// void TollgateSelectScene::level_3(CCObject* pSender) {
//     GlobalClient::sharedGlobalClient()->setiCurTollgateLevel(3);
//     SceneManager::sharedSceneManager()->changeScene(SceneManager::en_TollgateScene);
// }
// 
// void TollgateSelectScene::level_4(CCObject* pSender) {
//     GlobalClient::sharedGlobalClient()->setiCurTollgateLevel(4);
//     SceneManager::sharedSceneManager()->changeScene(SceneManager::en_TollgateScene);
// }
// 
// void TollgateSelectScene::level_5(CCObject* pSender) {
//     GlobalClient::sharedGlobalClient()->setiCurTollgateLevel(5);
//     SceneManager::sharedSceneManager()->changeScene(SceneManager::en_TollgateScene);
// }
