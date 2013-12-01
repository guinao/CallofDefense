#include "PlantManager.h"
#include <cstring>

PlantManager::PlantManager()
{
	m_plants = NULL;
}

//////////////////////////////////////////////////////////////////////////

PlantManager::~PlantManager()
{
	CC_SAFE_DELETE(m_plants);
}

//////////////////////////////////////////////////////////////////////////

bool PlantManager::init()
{
	bool bRet = false;

	do{
		CC_BREAK_IF(! CCLayer::init());

		scheduleUpdate();

		bRet = true;
	}while(0);

	return bRet;
}

//////////////////////////////////////////////////////////////////////////

void PlantManager::onExit()
{
	CCLayer::onExit();
//	CCSpriteFrameCache::sharedSpriteFrameCache()->removeSpriteFrameByName("PvZres2/peashooter.plist");
//	CCSpriteFrameCache::sharedSpriteFrameCache()->removeSpriteFrameByName("PvZres2/plants_type.plist");
}

//////////////////////////////////////////////////////////////////////////

void PlantManager::createPlants(const vector<PlantType> &v,	const vector<CCPoint> &vp)
{
	m_plants = CCArray::createWithCapacity(v.size());
	m_plants->retain();

	for(int i=0; i<(int)v.size(); ++i)
	{
		Plant *plant = Plant::createPlant(v[i], vp[i]);
		plant->scheduleUpdate();
		this->addChild(plant);
		m_plants->addObject(plant);
	}
}

//////////////////////////////////////////////////////////////////////////

void PlantManager::update(float delta)
{
	CCLOG("PlantManager::update");
	CCObject *Obj;
	CCARRAY_FOREACH(m_plants, Obj)
	{
		Plant* p = dynamic_cast<Plant*>(Obj);
		if(p->m_hp <= 0)
		{
			CCLOG("A Plant is eaten");
			p->setVisible(false);
			p->removeAllChildrenWithCleanup(true);
			m_plants->removeObject(p);
			this->removeChild(p);
		}
	}
}

//////////////////////////////////////////////////////////////////////////

void PlantManager::getPlantsPosition(vector<CCPoint>& vp)
{
	vp.clear();
	CCObject *Obj;
	CCARRAY_FOREACH(m_plants, Obj)
	{
		float x, y;
		Plant* plant = dynamic_cast<Plant*>(Obj);
		if(plant->m_hp > 0)
		{
			plant->getPosition(&x, &y);
			vp.push_back(ccp(x,y));
		}
	}
}

//////////////////////////////////////////////////////////////////////////