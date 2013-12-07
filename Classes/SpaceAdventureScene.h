#ifndef _SpaceAdventureScene_H_
#define _SpaceAdventureScene_H_

#include "cocos2d.h"
#include "PlantManager.h"
#include "EnumPlantType.h"
#include "SpaceNut.h"
#include "ZombieManager.h"
#include "Shield.h"
#include "SpaceZombie.h"
#include <vector>

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
	SpaceZombie* generateZombie();
	void processCollide(SpaceNut* nut, SpaceZombie* zombie);
	void loseGame(CCObject*);
	void winGame(CCObject*);

	ZombieManager *m_zombiemanager;
	SpaceNut *m_nut;

	double m_maxshakevalue;
	double m_shakevaluebound;
	int m_generateSeed;

	CCLabelAtlas* m_label;

	vector<SpaceZombie*> m_zombies;
	Shield* m_shield;
};

#endif