/*
    �ļ�����    TollgateMapLayer.h
    �衡����    �ؿ���ͼͼ��
    �����ˣ�    ��ľͷ_�ӵ��� (���ͣ�http://www.benmutou.com)

    �������ڣ�   2013.03.22
*/
#ifndef _TollgateMapLayer_H_
#define _TollgateMapLayer_H_

#include "cocos2d.h"
#include "cocos-ext.h"
USING_NS_CC;
USING_NS_CC_EXT;

#define HOME_LAYER_LVL 3  // ���ݵĲ��
#define HERO_LAYER_LVL 10    // Ӣ�۵Ĳ��
#define MONSTER_LAYER_LVL 15    // ����Ĳ��
#define BULLET_LAYER_LVL 20  // �ӵ��Ĳ��


class TowerPos;
class Home;
class Hero;
class MonsterManager;
class HeroManager;
class TollgateMapLayer : public CCLayer {
public:
    TollgateMapLayer();
    ~TollgateMapLayer();

    CREATE_FUNC(TollgateMapLayer);
    virtual bool init();

	/* ��ȡ���й������ */
	CCArray* getMonsterList();

    virtual void onExit();

	//void didAccelerate( CCAcceleration *pAccelerationValue);

private:
	/* ��������� */
	MonsterManager* m_monsterMgr;

	/* Ӣ�۹����� */
	HeroManager* m_heroMgr;

    /* ��ǰ�ؿ� */
    int m_iCurLevel;

    /* ��ȡ�ؿ����� */
    void loadConfig();

    /*��������  */
    void createHome();

    /* ������ʼ�� */
    void createStartPoint();
};

#endif