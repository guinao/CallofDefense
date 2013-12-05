#ifndef _SpaceZombie_H_
#define _SpaceZombie_H_

#include "cocos2d.h"
#include "cocos-ext.h"
#include "GlobalDefs.h"
#include "EnumPlantType.h"
#include <vector>

using namespace cocos2d::extension;
using namespace std;
USING_NS_CC;

class ZombieManager;
class SpaceZombie : public CCNode
{
	friend class ZombieManager;

public:

	static SpaceZombie* createSpaceZombie(ZombieType type, CCPoint pos);
	bool init(ZombieType type, CCPoint pos);

	void update(float delta);
	void hitAway(float x, float y);

//	CCRect myBoundingBox();
//	void onHurt(int hurt, float xspeed, float yspeed);

private:
	//	void attack();
	void performMove(float delta);
//	bool findSomethingToEat();

	CCAction *m_animationFloating;
	CCAction *m_animationWalking;
	CCAction *m_animationAttack;
	CCAction *m_animationDead;

	CCSprite* m_sprite;
	ZombieType m_type;
	ZombieState m_state1;
	StateInSpace m_state2;

	int m_hp;
	int m_ai;
	int m_aicount;
	float m_speed;
	CCPoint m_direction;
//	float m_xspeedfloating; set as 2x of the walking speed;
//	float m_yspeedfloating;
};

#endif