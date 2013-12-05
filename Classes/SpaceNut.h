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

	void update(float delta);
	void changeXSpeedBy(float delta);
	void changeYSpeedBy(float delta);
	void reverseXSpeed(){	m_xspeed = -m_xspeed;	};
	void reverseYSpeed(){	m_yspeed = -m_yspeed;	};
	void setXSpeed(float speed){	m_xspeed = speed;	};
	void setYSpeed(float speed){	m_yspeed = speed;	};
	float getXSpeed(){	return m_xspeed;	};
	float getYSpeed(){	return m_yspeed;	};
	CCRect myBoundingBox();

private:
	void setSprite(CCSprite* sprite);
	void recvShieldPosition(CCObject *pData);
	void moveInSpace(float delta);
	void moveInShield(float delta);

	CCSprite* m_sprite;
	float m_xspeed;
	float m_yspeed;
	int m_gravity;
	StateInSpace m_state;
	float m_shieldpos[3];
};

#endif