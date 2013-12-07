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
	virtual bool init(ZombieType type, CCPoint pos);
	virtual void update(float delta);

	void hit(float v1x, float v1y, float m1);
	ZombieState getZombieState(){	return m_state1;	};
	CCRect myBoundingBox(){	return m_sprite->boundingBox();	};
	int getHp(){	return m_hp;	};
	float getSpeedX(){	return m_speed * m_direction.x;	};
	float getSpeedY(){	return m_speed * m_direction.y;	};
	float getWeight(){	return m_weight;	};
//	CCRect myBoundingBox();
//	void onHurt(int hurt, float xspeed, float yspeed);

private:
	//	void attack();
	void performMove(float delta);
	void performFlyAway(float delta);
	void performAttacking(float delta);

	CCAction* createWalkingAction();
	CCAction* createFloatingAction();
	CCAction* createFlyAwayAction();

	void updateState2();

	CCSprite* m_sprite;
	ZombieType m_type;
	ZombieState m_state1;
	StateInSpace m_state2;

	int m_hp;
	int m_ai;
	int m_aicount;
	float m_speed;
	CCPoint m_direction;
	int m_weight;
//	float m_speedxfloating; set as 2x of the walking speed;
//	float m_speedyfloating;
};

#endif