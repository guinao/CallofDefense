#ifndef _Plant_H_
#define _Plant_H_

#include "cocos2d.h"
#include "cocos-ext.h"
#include "EnumPlantType.h"

using namespace cocos2d::extension;
USING_NS_CC;

class PlantManager;

class Plant : public CCNode
{
friend class PlantManager;

public:
	Plant();
	~Plant();

	static Plant* createPlant(PlantType type, CCPoint pos);
	void update(float delta);
	void onHurt(int hp);
	bool isAlive(){ return m_hp > 0; };

private:
	void createAnimations();
	void attack(CCPoint& direction);
	bool findAim(CCPoint& direction);
	void idle();

	CCAnimation *m_animationAtEase;
	CCAnimation *m_animationAttack;

	CCSprite* m_sprite;
	PlantType m_type;
	PlantState m_state;
	int m_hp;
};

#endif