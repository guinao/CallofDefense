/*
    �ļ�����    TollgateDataLayer.h
    �衡����    �ؿ�����ͼ��
    �����ˣ�    ��ľͷ_�ӵ��� (���ͣ�http://www.benmutou.com)

    �������ڣ�   2013.03.26
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

	/* ���չ���������Ϣ */
	void recvMonsterDead(CCObject* pData);

	int m_iTowerSoulNum;    /* �������� */
	int m_iMonsterNum;      /* �������� */
	int m_iMagicNum;        /* ħ������ */

	/* �����ǩ */
	MMLabel* m_towerSoulLab;

	/* �����ǩ */
	MMLabel* m_monsterLab;

	/* ħ����ǩ */
	MMLabel* m_magicLab;
};

#endif