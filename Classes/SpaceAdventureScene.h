#ifndef _SpaceAdventureScene_H_
#define _SpaceAdventureScene_H_

#include "cocos2d.h"
#include "PlantManager.h"
#include "EnumPlantType.h"
#include "SpaceNut.h"
#include "ZombieManager.h"
#include "Shield.h"

USING_NS_CC;

class SpaceAdventureScene : public CCLayer {
public:
	SpaceAdventureScene();
	~SpaceAdventureScene();

	static CCScene* scene();
	CREATE_FUNC(SpaceAdventureScene);
	virtual bool init();
	virtual void onExit();

	virtual void didAccelerate(CCAcceleration* pAccelerationValue);
	virtual void update(float delta);

private:
	void createNut();
	void createZombies();
	void createShield();

	ZombieManager *m_zombiemanager;
	SpaceNut *m_nut;

	double m_maxshakevalue;
	double m_shakevaluebound;

	CCLabelAtlas* m_label;

	Shield* m_shield;
};

#endif