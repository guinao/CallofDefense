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
	virtual void onEnter();
	virtual void onExit();

	virtual void didAccelerate(CCAcceleration* pAccelerationValue);
	virtual void update(float delta);

private:
	void createNut();
	SpaceZombie* generateZombie();
	void processCollide(SpaceNut* nut, SpaceZombie* zombie);
	void restartAllZombies(float);
	void loseGame(CCObject*);
	void winGame(CCObject*);
	void updateScore(CCObject *pdata);
	CCSpriteBatchNode *m_batchnode;

	int m_score;
	CCLabelAtlas* m_label;

	SpaceNut *m_nut;
	vector<SpaceZombie*> m_zombies;
	Shield* m_shield;
};

#endif