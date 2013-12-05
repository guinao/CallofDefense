#include "ZombieManager.h"
#include <cstring>

//////////////////////////////////////////////////////////////////////////

ZombieManager::ZombieManager()
{
	m_dShakePower = 10.0;
	m_probabiliy = 10;
}

//////////////////////////////////////////////////////////////////////////

ZombieManager::~ZombieManager()
{
}

//////////////////////////////////////////////////////////////////////////

bool ZombieManager::init()
{
	bool bRet = false;

	do{
		CC_BREAK_IF(! CCLayer::init());

		m_Zombies.clear();
		m_bMove = true;

		scheduleUpdate();

		srand(time(NULL));
//		CCTexture2D::PVRImagesHavePremultipliedAlpha(true);
//		CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("PvZres2/zombies_type.plist");

		bRet = true;
	}while(0);

	return bRet;
}

//////////////////////////////////////////////////////////////////////////

void ZombieManager::createZombies(const vector<ZombieType> &v,	const vector<CCPoint> &vp)
{
	for(int i=0; i<(int)v.size(); ++i)
	{
		Zombie  *zombie = Zombie::createZombie(v[i], vp[i]);
		zombie->scheduleUpdate();
		this->addChild(zombie);
		// put into array
		m_Zombies.push_back(zombie);
	}
}

//////////////////////////////////////////////////////////////////////////

void ZombieManager::update(float delta)
{
	CCLOG("ZombieManager::update");
	
	// 以一定的概率产生僵尸
	if( m_probabiliy > rand()%1000 )
	{
		// generate A Zombie
		CCSize size = CCDirector::sharedDirector()->getVisibleSize();
		int y = rand() % static_cast<int>(size.height);
		Zombie *zombie = Zombie::createZombie(en_NormalZombie, ccp(size.width, y));
		zombie->scheduleUpdate();
		this->addChild(zombie);
		m_Zombies.push_back(zombie);

		//if(m_probabiliy < 100)
		//{
		//	++m_probabiliy;
		//}
	}
}

//////////////////////////////////////////////////////////////////////////

void ZombieManager::enableMove(float delta)
{
	if(!m_bMove)
	{
		m_bMove = true;
		for(int i=0; i<m_Zombies.size(); ++i)
		{
			m_Zombies[i]->resumeSchedulerAndActions();
//			m_Zombies[i]->scheduleUpdate();
		}
	}
}

//////////////////////////////////////////////////////////////////////////

void ZombieManager::disableMove()
{
	if(m_bMove)
	{
		m_bMove = false;
		for(int i=0; i<m_Zombies.size(); ++i)
		{
			m_Zombies[i]->pauseSchedulerAndActions();
			//m_Zombies[i]->stopAllActions();
			//m_Zombies[i]->unscheduleUpdate();
		}
	}
}

//////////////////////////////////////////////////////////////////////////

void ZombieManager::moveZombie(Zombie* zombie, float delta)
{
	CCLOG("ZombieManager::moveZombie");
}

//////////////////////////////////////////////////////////////////////////

void ZombieManager::didAccelerate(CCAcceleration* pAccelerationValue, CCLabelAtlas* label)
{
	char output[128];

	float x = pAccelerationValue->x;
	float y = pAccelerationValue->y;
	float z = pAccelerationValue->z;
	float all = x*x + y*y + z*z;


	if(all > m_dShakePower)
	{
		disableMove();
//		m_dShakePower *= 2;
		schedule(schedule_selector(ZombieManager::enableMove), 5.0f, -1, 0.0f);

		sprintf(output, "%d", floor(all));
		label->setString(output);
	}
}

//////////////////////////////////////////////////////////////////////////

void ZombieManager::getZombiesPosition(vector<CCRect>& vc)
{
	vc.clear();
	vector<Zombie*>::iterator it = m_Zombies.begin();
	for( ; it!=m_Zombies.end(); ++it)
	{
		float x, y;
		if( 0 < (*it)->m_hp )
		{
			(*it)->getPosition(&x, &y);
			vc.push_back((*it)->myBoundingBox());
		}
	}
}

//////////////////////////////////////////////////////////////////////////

static void printRect(const CCRect& rect)
{
	char msg[128];
	sprintf(msg, "%f, %f, %f, %f",
		rect.getMinX(),
		rect.getMinY(),
		rect.getMaxX(),
		rect.getMaxY());

	CCLOG(msg);
	
}

static bool isCollide(const CCRect r1, const CCRect r2)
{
	bool bRet = false;
	if(r1.intersectsRect(r2))
	{
		double area1 = (r1.getMaxX()-r1.getMinX())*(r1.getMaxY()-r1.getMinY());
		double area2 = (r2.getMaxX()-r2.getMinX())*(r2.getMaxY()-r2.getMinY());
		float maxX = min(r1.getMaxX(), r2.getMaxX());
		float minX = max(r1.getMinX(), r2.getMinX());
		float maxY = min(r1.getMaxY(), r2.getMaxY());
		float minY = max(r1.getMinY(), r2.getMinY());
		double interarea = (maxX-minX) * (maxY-minY);

		bRet = interarea * 5 > max(area1, area2);
	}
	return bRet;
}

static bool inVisibleRigion(const CCRect& rect)
{
	CCSize size = CCDirector::sharedDirector()->getVisibleSize();

	return rect.getMinX() < size.width
		&& rect.getMaxX() > 0
		&& rect.getMinY() < size.height
		&& rect.getMaxY() > 0;
}

bool ZombieManager::hitDetect(CCRect rect)
{
	bool bRet = false;
	vector<Zombie*>::iterator it = m_Zombies.begin();

	vector<Zombie*> rest;
	for( ; it!=m_Zombies.end(); ++it)
	{
		CCRect rect_zombie = (*it)->myBoundingBox();
		if( isCollide(rect, rect_zombie) )
		{
			(*it)->onHurt(101, -350.0f, 0.0f);
			bRet = true;
		}
		else if(inVisibleRigion(rect_zombie))
		{
			rest.push_back(*it);
		}
		else
		{
			removeChild(*it, true);
		}
	}
	m_Zombies = rest;
	return bRet;
}
