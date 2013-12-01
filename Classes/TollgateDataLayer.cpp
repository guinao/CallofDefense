#include "TollgateDataLayer.h"
#include "I18N.h"
#include "EnumStrKey.h"
#include "GlobalPath.h"
#include "MMWidget\MMWinManager.h"
#include "GlobalParam.h"
#include "GlobalDefine.h"
#include "EnumMsgDataKey.h"
#include "MMWidget/MMLabel.h"
#include "SceneManager.h"
#include "GlobalDefine.h"
#include "EnumMsgDataKey.h"

TollgateDataLayer::TollgateDataLayer() {
	m_towerSoulLab = NULL;
	m_monsterLab = NULL;
	m_magicLab = NULL;
}

TollgateDataLayer::~TollgateDataLayer() {
	CC_SAFE_RELEASE(m_towerSoulLab);
	CC_SAFE_RELEASE(m_monsterLab);
	CC_SAFE_RELEASE(m_magicLab);
}

bool TollgateDataLayer::init() {
    bool bRet = false;

    do {
		CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();

		MMWinManager::sharedWinManager()->createWinsFromXML(PATH_UI_TollgateProMsgWin);
		//MMWinManager::sharedWinManager()->createWinsFromXML(PATH_UI_Menu);

        /* �����ǩ */
        m_towerSoulLab = (MMLabel*)MMWinManager::sharedWinManager()->getDesktopWin()->getWinByDes("tollgateMsgWinTowerSoulLab");
		CC_SAFE_RETAIN(m_towerSoulLab);

        /* �����ǩ */
        m_monsterLab = (MMLabel*)MMWinManager::sharedWinManager()->getDesktopWin()->getWinByDes("tollgateMsgWinMonsterLab");
		CC_SAFE_RETAIN(m_monsterLab);

        /* ħ����ǩ */
        m_magicLab = (MMLabel*)MMWinManager::sharedWinManager()->getDesktopWin()->getWinByDes("tollgateMsgWinHPLab");
		CC_SAFE_RETAIN(m_magicLab);

        /* ������Ϣ */
        NOTIFY->addObserver(this, 
            callfuncO_selector(TollgateDataLayer::recvRefreshTowerSoulNum), 
            "TowerSoulChange", 
            NULL);

        NOTIFY->addObserver(this, 
            callfuncO_selector(TollgateDataLayer::recvRefreshMonsterNum), 
            "MonsterNumChange", 
            NULL);

        NOTIFY->addObserver(this, 
            callfuncO_selector(TollgateDataLayer::recvRefreshMagicNum), 
            "MagicChange", 
            NULL);

		NOTIFY->addObserver(this, 
			callfuncO_selector(TollgateDataLayer::recvMonsterDead), 
			"MonsterDead", 
			NULL);

		NOTIFY->addObserver(this, 
			callfuncO_selector(TollgateDataLayer::recvAllMonsterDead), 
			"AllMonsterDead", 
			NULL);

        bRet = true;
    } while (0);

    return bRet;
}

void TollgateDataLayer::recvRefreshTowerSoulNum( CCObject* pData ) {
    CCDictionary* dict = dynamic_cast<CCDictionary*>(pData);

    if(dict == NULL) {
        return;
    }

    /* ����ı�ֵ */
    CCInteger* towerSoulAltNum = dynamic_cast<CCInteger*>(dict->objectForKey(enMsgDataKey_TowerSoulAltNum));
    if(towerSoulAltNum != NULL) {
        m_iTowerSoulNum += towerSoulAltNum->getValue();
    }

    /* ����ֵ */
    CCInteger* towerSoulNum = dynamic_cast<CCInteger*>(dict->objectForKey(enMsgDataKey_TowerSoulNum));
    if(towerSoulNum != NULL) {
        m_iTowerSoulNum = towerSoulNum->getValue();
    }

    m_towerSoulLab->setsText(m_iTowerSoulNum);
}

void TollgateDataLayer::recvRefreshMonsterNum( CCObject* pData ) {
    CCDictionary* dict = dynamic_cast<CCDictionary*>(pData);

    if(dict == NULL) {
        return;
    }

    /* ����ı�ֵ */
    CCInteger* monsterAltNum = dynamic_cast<CCInteger*>(dict->objectForKey(enMsgDataKey_MonsterAltNum));
    if(monsterAltNum != NULL) {
        m_iMonsterNum += monsterAltNum->getValue();
    }

    /* ����ֵ */
    CCInteger* monsterSoulNum = dynamic_cast<CCInteger*>(dict->objectForKey(enMsgDataKey_MonsterNum));
    if(monsterSoulNum != NULL) {
        m_iMonsterNum = monsterSoulNum->getValue();
    }

    m_monsterLab->setsText(m_iMonsterNum);

}

void TollgateDataLayer::recvRefreshMagicNum( CCObject* pData ) {
    CCDictionary* dict = dynamic_cast<CCDictionary*>(pData);

    if(dict == NULL) {
        return;
    }

    /* ħ���ı�ֵ */
    CCInteger* magicAltNum = dynamic_cast<CCInteger*>(dict->objectForKey(enMsgDataKey_MagicAltNum));
    if(magicAltNum != NULL) {
        m_iMagicNum += magicAltNum->getValue();
    }

    /* ħ��ֵ */
    CCInteger* magicNum = dynamic_cast<CCInteger*>(dict->objectForKey(enMsgDataKey_MagicNum));
    if(magicNum != NULL) {
        m_iMagicNum = magicNum->getValue();
    }

    m_magicLab->setsText(m_iMagicNum);

	/* ħ��ֵС�ڵ���0����Ϸʧ�� */
	if(m_iMagicNum <= 0) {
		SceneManager::sharedSceneManager()->changeScene(SceneManager::en_GameOverScene);
	}
}

void TollgateDataLayer::recvMonsterDead(CCObject* pData) {
	m_iTowerSoulNum += 10;
	m_towerSoulLab->setsText(m_iTowerSoulNum);
}

void TollgateDataLayer::recvAllMonsterDead( CCObject* pData ) {
	if(m_iMagicNum > 0) {
		SceneManager::sharedSceneManager()->changeScene(SceneManager::en_WinScene);
	}
}

void TollgateDataLayer::onExit() { 
    /* ȡ��������Ϣ */
    NOTIFY->removeObserver(this, "TowerSoulChange");
    NOTIFY->removeObserver(this, "MonsterNumChange");
    NOTIFY->removeObserver(this, "MagicChange");
	NOTIFY->removeObserver(this, "MonsterDead");
	NOTIFY->removeObserver(this, "AllMonsterDead");

	MMWinManager::sharedWinManager()->getDesktopWin()->removeAllWins();
}

int TollgateDataLayer::getiMagicNum() {
	return m_iMagicNum;
}

int TollgateDataLayer::getiTowerSoulNum() {
	return m_iTowerSoulNum;
}
