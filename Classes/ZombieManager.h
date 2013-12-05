#ifndef _ZombieManager_H_
#define _ZombieManager_H_

#include "cocos2d.h"
#include "cocos-ext.h"
#include "EnumPlantType.h"
#include "Zombie.h"
#include "SpaceNut.h"
#include "Plant.h"
#include <vector>

using namespace std;

class DemoScene;

class ZombieManager : public CCLayer
{
friend class DemoScene;

public:
	ZombieManager();
	~ZombieManager();

	CREATE_FUNC(ZombieManager);			// create a random infinite zombie generator

	virtual bool init();
	virtual void update(float delta);
	void enableMove(float delta);
	void disableMove();
	void didAccelerate(CCAcceleration* pAccelerationValue, CCLabelAtlas* label);

	void createZombies(const vector<ZombieType> &v, const vector<CCPoint> &vp);

	void getZombiesPosition(vector<CCRect>& vc);
	bool hitDetect(CCRect rect);

private:
	void moveZombie(Zombie* zombie, float delta);

	vector<Zombie*> m_Zombies;
	bool m_bMove;
	double m_dShakePower;
	int m_probabiliy;
};

#endif
