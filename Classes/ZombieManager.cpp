#include "ZombieManager.h"
#include <cstring>

ZombieManager::ZombieManager()
{
	m_Zombies = NULL;
	m_dShakePower = 10;
}

//////////////////////////////////////////////////////////////////////////

ZombieManager::~ZombieManager()
{
	CC_SAFE_RETAIN(m_Zombies);
}

//////////////////////////////////////////////////////////////////////////

bool ZombieManager::init()
{
	bool bRet = false;

	do{
		CC_BREAK_IF(! CCLayer::init());

		this->setAccelerometerEnabled(true);
		m_bMove = true;
		scheduleUpdate();
//		CCTexture2D::PVRImagesHavePremultipliedAlpha(true);
//		CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("PvZres2/zombies_type.plist");

		bRet = true;
	}while(0);

	return bRet;
}

//////////////////////////////////////////////////////////////////////////

void ZombieManager::createZombies(const vector<ZombieType> &v,	const vector<CCPoint> &vp)
{
	m_Zombies = CCArray::createWithCapacity(v.size());
	m_Zombies->retain();

	for(int i=0; i<(int)v.size(); ++i)
	{
		Zombie  *zombie = Zombie::createZombie(v[i], vp[i]);
		zombie->scheduleUpdate();
		this->addChild(zombie);
		// put into array
		m_Zombies->addObject(zombie);
	}
}

//////////////////////////////////////////////////////////////////////////

void ZombieManager::update(float delta)
{
	CCLOG("ZombieManager::update");
}

//////////////////////////////////////////////////////////////////////////

void ZombieManager::enableMove(float delta)
{
	if(!m_bMove)
	{
		m_bMove = true;
		CCObject *pObj;
		CCARRAY_FOREACH(m_Zombies, pObj)
		{
			Zombie* zombie = dynamic_cast<Zombie*>(pObj);
			zombie->scheduleUpdate();
		}
	}
}

//////////////////////////////////////////////////////////////////////////

void ZombieManager::disableMove()
{
	if(m_bMove)
	{
		m_bMove = false;
		CCObject *pObj;
		CCARRAY_FOREACH(m_Zombies, pObj)
		{
			Zombie* zombie = dynamic_cast<Zombie*>(pObj);
			zombie->unscheduleUpdate();
		}
	}
}

//////////////////////////////////////////////////////////////////////////

void ZombieManager::moveZombies(float delta)
{
	CCObject *pObj;
	CCARRAY_FOREACH(m_Zombies, pObj)
	{
		Zombie* zombie = dynamic_cast<Zombie*>(pObj);
		float movespeed = 20.0f;
		CCPoint pos = zombie->getPosition();
		zombie->setPosition(ccp(pos.x-movespeed*delta, pos.y));
	}
}

//////////////////////////////////////////////////////////////////////////

void ZombieManager::moveZombie(Zombie* zombie, float delta)
{
	CCLOG("ZombieManager::moveZombie");
}

//////////////////////////////////////////////////////////////////////////

void ZombieManager::didAccelerate(CCAcceleration* pAccelerationValue, CCLabelAtlas* m_label)
{
	char output[128];

	float x = pAccelerationValue->x;
	float y = pAccelerationValue->y;
	float z = pAccelerationValue->z;
	float all = x*x + y*y + z*z;

	sprintf(output, "%d", floor(all));
	m_label->setString(output);

	if(all > m_dShakePower)
	{
		disableMove();
		m_dShakePower *= 2;
		schedule(schedule_selector(ZombieManager::enableMove), 3.0f, -1, 0.0f);
	}
}

//////////////////////////////////////////////////////////////////////////

void ZombieManager::getZombiesPosition(vector<CCPoint>& vc)
{
	vc.clear();
	CCObject *Obj;
	CCARRAY_FOREACH(m_Zombies, Obj)
	{
		float x, y;
		Zombie *zombie = dynamic_cast<Zombie*>(Obj);
		if(zombie->m_hp > 0)
		{
			zombie->getPosition(&x, &y);
			vc.push_back(ccp(x, y));
		}
	}
}

