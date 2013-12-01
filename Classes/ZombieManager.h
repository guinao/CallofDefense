#ifndef _ZombieManager_H_
#define _ZombieManager_H_

#include "cocos2d.h"
#include "cocos-ext.h"
#include "Character.h"
#include "EnumPlantType.h"
#include "Zombie.h"
#include <vector>
using namespace std;

class DemoScene;

class ZombieManager : public CCLayer
{
friend class DemoScene;

public:
	ZombieManager();
	~ZombieManager();

	CREATE_FUNC(ZombieManager);
	virtual bool init();
	virtual void update(float delta);
	void enableMove(float delta);
	void disableMove();
	void didAccelerate(CCAcceleration* pAccelerationValue, CCLabelAtlas* m_label);

	void createZombies(const vector<ZombieType> &v, const vector<CCPoint> &vp);

	void getZombiesPosition(vector<CCPoint>& vc);

private:
	void moveZombies(float delta);
	void moveZombie(Zombie* zombie, float delta);

	CCArray* m_Zombies;
	bool m_bMove;
	double m_dShakePower;
};

#endif
