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

        /* 塔魂标签 */
        m_towerSoulLab = (MMLabel*)MMWinManager::sharedWinManager()->getDesktopWin()->getWinByDes("tollgateMsgWinTowerSoulLab");
		CC_SAFE_RETAIN(m_towerSoulLab);

        /* 怪物标签 */
        m_monsterLab = (MMLabel*)MMWinManager::sharedWinManager()->getDesktopWin()->getWinByDes("tollgateMsgWinMonsterLab");
		CC_SAFE_RETAIN(m_monsterLab);

        /* 魔力标签 */
        m_magicLab = (MMLabel*)MMWinManager::sharedWinManager()->getDesktopWin()->getWinByDes("tollgateMsgWinHPLab");
		CC_SAFE_RETAIN(m_magicLab);

        /* 订阅消息 */
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

    /* 塔魂改变值 */
    CCInteger* towerSoulAltNum = dynamic_cast<CCInteger*>(dict->objectForKey(enMsgDataKey_TowerSoulAltNum));
    if(towerSoulAltNum != NULL) {
        m_iTowerSoulNum += towerSoulAltNum->getValue();
    }

    /* 塔魂值 */
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

    /* 怪物改变值 */
    CCInteger* monsterAltNum = dynamic_cast<CCInteger*>(dict->objectForKey(enMsgDataKey_MonsterAltNum));
    if(monsterAltNum != NULL) {
        m_iMonsterNum += monsterAltNum->getValue();
    }

    /* 怪物值 */
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

    /* 魔力改变值 */
    CCInteger* magicAltNum = dynamic_cast<CCInteger*>(dict->objectForKey(enMsgDataKey_MagicAltNum));
    if(magicAltNum != NULL) {
        m_iMagicNum += magicAltNum->getValue();
    }

    /* 魔力值 */
    CCInteger* magicNum = dynamic_cast<CCInteger*>(dict->objectForKey(enMsgDataKey_MagicNum));
    if(magicNum != NULL) {
        m_iMagicNum = magicNum->getValue();
    }

    m_magicLab->setsText(m_iMagicNum);

	/* 魔力值小于等于0，游戏失败 */
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
    /* 取消订阅消息 */
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
