/*
    文件名：    TollgateDataLayer.h
    描　述：    关卡数据图层
    创建人：    笨木头_钟迪龙 (博客：http://www.benmutou.com)

    创建日期：   2013.03.26
*/
#ifndef _TollgateDataLayer_H_
#define _TollgateDataLayer_H_


#include "cocos2d.h"
USING_NS_CC;

class MMLabel;
class TollgateDataLayer : public CCLayer {
public:
	TollgateDataLayer();
	~TollgateDataLayer();

	CREATE_FUNC(TollgateDataLayer);
	virtual bool init();

	virtual void onExit();

	int getiMagicNum();
	int getiTowerSoulNum();
private:
	void recvRefreshTowerSoulNum(CCObject* pData);
	void recvRefreshMonsterNum(CCObject* pData);
	void recvRefreshMagicNum(CCObject* pData);
	void recvAllMonsterDead(CCObject* pData);

	/* 接收怪物死亡消息 */
	void recvMonsterDead(CCObject* pData);

	int m_iTowerSoulNum;    /* 塔魂数量 */
	int m_iMonsterNum;      /* 怪物数量 */
	int m_iMagicNum;        /* 魔力数量 */

	/* 塔魂标签 */
	MMLabel* m_towerSoulLab;

	/* 怪物标签 */
	MMLabel* m_monsterLab;

	/* 魔力标签 */
	MMLabel* m_magicLab;
};

#endif