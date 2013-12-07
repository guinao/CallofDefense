#ifndef _SpaceNut_H_
#define _SpaceNut_H_

#include "cocos2d.h"
#include "GlobalDefs.h"
#include "EnumPlantType.h"

USING_NS_CC;

class SpaceNut : public CCNode
{
public:
	SpaceNut();
	~SpaceNut();

	CREATE_FUNC(SpaceNut);
	virtual bool init();
	virtual void onExit();

	void update(float delta);
	void hit(float v1x, float v1y, float m1);
	void changeSpeedXBy(float delta);
	void changeSpeedYBy(float delta);
	void reverseSpeedX(){	m_speedx = -m_speedx;	};
	void reverseSpeedY(){	m_speedy = -m_speedy;	};
	void setSpeedX(float speed){	m_speedx = speed;	};
	void setSpeedY(float speed){	m_speedy = speed;	};
	float getSpeedX(){	return m_speedx;	};
	float getSpeedY(){	return m_speedy;	};
	float getWeight(){	return m_weight;	};
	CCRect myBoundingBox();

private:
	void setSprite(CCSprite* sprite);
	void recvShieldPosition(CCObject *pData);
	void moveInSpace(float delta);
	void moveInShield(float delta);

	CCSprite* m_sprite;
	float m_speedx;
	float m_speedy;
	int m_gravity;
	StateInSpace m_state;
	float m_shieldpos[3];
	float m_rotateangle;
	float m_weight;
};

#endif