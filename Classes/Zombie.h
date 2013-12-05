#ifndef _Zombie_H_
#define _Zombie_H_

#include "cocos2d.h"
#include "cocos-ext.h"
#include "EnumPlantType.h"
#include <vector>

using namespace cocos2d::extension;
using namespace std;
USING_NS_CC;

class ZombieManager;
class Zombie : public CCNode
{
friend class ZombieManager;

public:
	Zombie();
	~Zombie();

	static Zombie* createZombie(ZombieType type, CCPoint pos);

	void update(float delta);
	CCRect myBoundingBox();
	void onHurt(int hurt, float xspeed, float yspeed);

private:
	void createAnimations();
	void attack();
	void moving(float delta);
	bool findSomethingToEat();

	CCAction *m_animationAtEase;
	CCAction *m_animationAttack;
	CCAction *m_animationDead;
	CCAction *m_animationFlyAway;

	CCSprite* m_sprite;
	ZombieType m_type;
	ZombieState m_state;
	int m_hp;
	float m_xspeed;
	float m_yspeed;
	double m_distance;		// distance to next path point
	vector<CCPoint> m_path;
};

#endif