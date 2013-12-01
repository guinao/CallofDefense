/*
    �ļ�����    SceneManager.h
    �衡����    �����л�������
    �����ˣ�    ��ľͷ (���ͣ�http://www.benmutou.com)

    �������ڣ�   2012.11.22
*/

#ifndef __SCENE_MANAGER_H__
#define __SCENE_MANAGER_H__

#include "cocos2d.h"

using namespace cocos2d;

class SceneManager : public CCObject {
public:
    /* ����ö���� */
    enum EnumSceneType {
        en_TollgateScene,  /* �ؿ����� */
        en_TollgateEditorScene, /* �ؿ��༭������ */
		en_TollgateSelectScene,	/* �ؿ�ѡ�񳡾� */
		en_WinScene,		/* ʤ������ */
		en_GameOverScene,	/* ��Ϸ�������� */
		en_DemoScene		/* ���Գ��������ڹ������� */
    };

    /* ��ȡ�������������� */
    static SceneManager* sharedSceneManager();

    /* ��ʼ�� */
    virtual bool init();

    /* �л����� */
    void changeScene(EnumSceneType enScenType);

private:
    /* �������������� */
    static SceneManager* mSceneManager;
};

#endif