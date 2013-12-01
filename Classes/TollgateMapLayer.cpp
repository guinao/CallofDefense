#include "TollgateMapLayer.h"
#include "TowerPos.h"
#include "EnumPosType.h"
#include "PosLoadUtil.h"
#include "SimpleAudioEngine.h"
#include "GlobalDefine.h"
#include "MonsterPos.h"
#include "HeroManager.h"
#include "MonsterManager.h"
#include "EnumMsgDataKey.h"
#include "GlobalClient.h"

TollgateMapLayer::TollgateMapLayer() {
    m_iCurLevel = GlobalClient::sharedGlobalClient()->get_iCurTollgateLevel();
	m_monsterMgr = NULL;
	m_heroMgr = NULL;
	setAccelerometerEnabled(true);
}

TollgateMapLayer::~TollgateMapLayer() {
}

bool TollgateMapLayer::init() {
    bool bRet = false;

    do {
        CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();

        /* ��ȡ�ؿ����� */
        loadConfig();

		/* ������������� */
		m_monsterMgr = MonsterManager::createWithLevel(m_iCurLevel);
		this->addChild(m_monsterMgr, MONSTER_LAYER_LVL);

		/* ����Ӣ�۹����� */
		m_heroMgr = HeroManager::createWithLevel(m_iCurLevel);
		this->addChild(m_heroMgr, HERO_LAYER_LVL);

        /* ������ʼ�� */
        createStartPoint();

        /* �������� */
        createHome();
		
        /* ��ʼ�����ꡢ�����ħ������ */
        CCDictionary* dict = CCDictionary::create();

        dict->setObject(CCInteger::create(5), enMsgDataKey_TowerSoulNum);
        NOTIFY->postNotification("TowerSoulChange", dict);

        dict->removeAllObjects();
        dict->setObject(CCInteger::create(m_monsterMgr->getNotShowMonsterCount()), enMsgDataKey_MonsterNum);
        NOTIFY->postNotification("MonsterNumChange", dict);

        dict->removeAllObjects();
        dict->setObject(CCInteger::create(100), enMsgDataKey_MagicNum);
        NOTIFY->postNotification("MagicChange", dict);

        bRet = true;
    } while (0);

    return true;
}

void TollgateMapLayer::loadConfig() {
    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();

	/* ��ӱ������� */
	CocosDenshion::SimpleAudioEngine::sharedEngine()->playBackgroundMusic(
		CCString::createWithFormat("music/tollgate_%d.mp3", m_iCurLevel)->getCString(), true);

    /* ��ӵ�ͼ���� */
    CCString* sBG = CCString::createWithFormat("tollgate/level_%d.jpg", m_iCurLevel);
    CCSprite* map = CCSprite::create(sBG->getCString());
    map->setPosition(ccp(visibleSize.width / 2, visibleSize.height / 2));
    this->addChild(map, 1);

}

CCArray* TollgateMapLayer::getMonsterList() {
	return m_monsterMgr->getMonsterList();
}

void TollgateMapLayer::onExit() {
    this->unscheduleAllSelectors();

    /* ȡ��������Ϣ */
}

void TollgateMapLayer::createHome() {
    MonsterPos* pos = m_monsterMgr->getMonsterEndPos();

    CCSprite* home = CCSprite::create("tollgate/home.png");
    home->setPosition(pos->getPos());

    CCActionInterval* rotateBy = CCRotateBy::create(15.0f, 360, 360);
    CCActionInterval* repeat = CCRepeatForever::create(rotateBy);
    home->runAction(repeat);

    this->addChild(home, HOME_LAYER_LVL);
}

void TollgateMapLayer::createStartPoint() {
	MonsterPos* pos = m_monsterMgr->getMonsterStartPos();

	CCSprite* startSp = CCSprite::create("tollgate/start.png");
	startSp->setPosition(pos->getPos());

	CCActionInterval* rotateBy = CCRotateBy::create(15.0f, 360, 360);
	CCActionInterval* repeat = CCRepeatForever::create(rotateBy);
	startSp->runAction(repeat);

	this->addChild(startSp, HOME_LAYER_LVL);
}

//void TollgateMapLayer::didAccelerate(CCAcceleration *pAccelerationValue)
//{
//	CCDictionary *dict = CCDictionary::create();
//
//	int x = (int)pAccelerationValue->x;
//	int y = (int)pAccelerationValue->y;
//	int z = (int)pAccelerationValue->z;
//
//	dict->setObject(CCInteger::create(x*x+y*y+z*z), enMsgDataKey_MagicNum);
//	NOTIFY->postNotification("MagicChange", dict);
//}