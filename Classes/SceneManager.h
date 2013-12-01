/*
    文件名：    SceneManager.h
    描　述：    场景切换管理器
    创建人：    笨木头 (博客：http://www.benmutou.com)

    创建日期：   2012.11.22
*/

#ifndef __SCENE_MANAGER_H__
#define __SCENE_MANAGER_H__

#include "cocos2d.h"

using namespace cocos2d;

class SceneManager : public CCObject {
public:
    /* 场景枚举类 */
    enum EnumSceneType {
        en_TollgateScene,  /* 关卡场景 */
        en_TollgateEditorScene, /* 关卡编辑器场景 */
		en_TollgateSelectScene,	/* 关卡选择场景 */
		en_WinScene,		/* 胜利场景 */
		en_GameOverScene,	/* 游戏结束场景 */
		en_DemoScene		/* 测试场景，用于功能试验 */
    };

    /* 获取场景管理器对象 */
    static SceneManager* sharedSceneManager();

    /* 初始化 */
    virtual bool init();

    /* 切换场景 */
    void changeScene(EnumSceneType enScenType);

private:
    /* 场景管理器对象 */
    static SceneManager* mSceneManager;
};

#endif