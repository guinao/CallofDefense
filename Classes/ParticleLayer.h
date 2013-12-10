#ifndef _ParticleLayer_H_
#define _ParticleLayer_H_

#include "cocos2d.h"
#include "GlobalDefs.h"
#include "EnumPlantType.h"

USING_NS_CC;

class ParticleLayer : public CCLayer {
public:
	virtual bool init();
	CREATE_FUNC(ParticleLayer);
	virtual void onEnter();
	virtual void onExit();
	void update(float delta);

private:
	void shieldPositionChanged(CCObject* pdata);
	void nutPositionChanged(CCObject* pdata);
	void gravityShock(CCObject *pdata);
	CCParticleSystem* createPhoenix();
	CCParticleSystem* createGalaxy();
	CCParticleSystem* createExplodingRing();
	CCParticleSystem* createExplosion();
	CCParticleSystem* createMeteor();
	CCParticleSystem* createFireParticle();
	CCParticleSystem* createFireWorks();

	CCParticleSystem *m_gravityshock;
	CCParticleSystem *m_shieldtracer;
	CCParticleSystem *m_nuttracer;

	CCPoint m_shieldposition;
	CCPoint m_nutposition;
};

#endif