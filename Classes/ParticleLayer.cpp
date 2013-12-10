#include "ParticleLayer.h"

bool ParticleLayer::init()
{
	bool bRet = false;

	do{
		CC_BREAK_IF(! CCLayer::init());

		m_nuttracer = NULL;
		m_shieldtracer = NULL;

		bRet = true;
	}while(0);

	return bRet;
}

void ParticleLayer::onEnter()
{
	CCLayer::onEnter();

	CCSize size = CCDirector::sharedDirector()->getVisibleSize();

	m_nuttracer = createFireParticle();
	m_nuttracer->setPosition(ccp(size.width/2, size.height/2));

	m_shieldtracer = createGalaxy();
	m_shieldtracer->setPositionType(kCCPositionTypeGrouped);
	m_shieldtracer->setPosition(ccp(size.width/2, size.height/2));

	NOTIFY->addObserver(
		this,
		callfuncO_selector(ParticleLayer::shieldPositionChanged),
		kShieldPostionChangedMessage,
		NULL);

	NOTIFY->addObserver(
		this,
		callfuncO_selector(ParticleLayer::nutPositionChanged),
		kNutPostionChangedMessage,
		NULL);

	NOTIFY->addObserver(
		this,
		callfuncO_selector(ParticleLayer::gravityShock),
		kGravityShockMessage,
		NULL);

	scheduleUpdate();
}

void ParticleLayer::update(float delta)
{
	CCLOG("ParticleLayer::update");
	m_nuttracer->setPosition(m_nutposition);
	m_shieldtracer->setPosition(m_shieldposition);
}

void ParticleLayer::onExit()
{
	NOTIFY->removeObserver(this, kShieldPostionChangedMessage);
	NOTIFY->removeObserver(this, kNutPostionChangedMessage);
}

void ParticleLayer::shieldPositionChanged(CCObject* pdata)
{
	CCDictionary *dict = dynamic_cast<CCDictionary*>(pdata);
	float x = dynamic_cast<CCFloat*>(dict->objectForKey("x"))->getValue();
	float y = dynamic_cast<CCFloat*>(dict->objectForKey("y"))->getValue();
	m_shieldposition = ccp(x, y);
}

void ParticleLayer::nutPositionChanged(CCObject* pdata)
{
	CCDictionary *dict = dynamic_cast<CCDictionary*>(pdata);
	float x = dynamic_cast<CCFloat*>(dict->objectForKey("x"))->getValue();
	float y = dynamic_cast<CCFloat*>(dict->objectForKey("y"))->getValue();
	m_nutposition = ccp(x,y);
}

void ParticleLayer::gravityShock(CCObject *pdata)
{
	CCDictionary *dict = dynamic_cast<CCDictionary*>(pdata);
	float x = dynamic_cast<CCFloat*>(dict->objectForKey("x"))->getValue();
	float y = dynamic_cast<CCFloat*>(dict->objectForKey("y"))->getValue();

	CCParticleSystem *emitter = createExplodingRing();
	emitter->setPosition(ccp(x, y));
}

CCParticleSystem* ParticleLayer::createPhoenix()
{
	CCParticleSystem *emitter = new CCParticleSystemQuad();
	emitter->initWithFile("Particles/Phoenix.plist");
	addChild(emitter, 10);

	return emitter;
}

CCParticleSystem* ParticleLayer::createGalaxy()
{
	CCParticleSystem *emitter = new CCParticleSystemQuad();
	emitter->initWithFile("Particles/Galaxy.plist");
	//CCParticleSystem *emitter = CCParticleGalaxy::create();
	//emitter->retain();
	//emitter->setTexture( CCTextureCache::sharedTextureCache()->addImage("Particles/fire.png") );
	addChild(emitter, 10);

	return emitter;
}

CCParticleSystem* ParticleLayer::createExplodingRing()
{
	CCParticleSystem *emitter = new CCParticleSystemQuad();
	emitter->initWithFile("Particles/ExplodingRing.plist");
	emitter->setAutoRemoveOnFinish(true);
//	emitter->setEndRadius(100.0f);

	addChild(emitter, 10);

	return emitter;
}

CCParticleSystem* ParticleLayer::createExplosion()
{
	CCParticleSystem *emitter = CCParticleExplosion::create();
	emitter->retain();
	addChild(emitter, 10);

	emitter->setTexture( CCTextureCache::sharedTextureCache()->addImage("Particles/stars.png") );

	emitter->setAutoRemoveOnFinish(true);

	return emitter;
}

CCParticleSystem* ParticleLayer::createMeteor()
{
	CCParticleSystem *emitter = CCParticleMeteor::create();
	emitter->retain();
	addChild(emitter, 10);

	emitter->setGravity(CCPointZero);

	emitter->setTexture( CCTextureCache::sharedTextureCache()->addImage("Particles/fire.png") );
	return emitter;
}

CCParticleSystem* ParticleLayer::createFireParticle()
{
	CCParticleSystem *emitter = CCParticleFire::create();
	emitter->retain();
	addChild(emitter, 10);

	emitter->setTexture( CCTextureCache::sharedTextureCache()->addImage("Particles/fire.png") );
	return emitter;
}

CCParticleSystem* ParticleLayer::createFireWorks()
{
	CCParticleSystem *emitter = CCParticleFireworks::create();
	emitter->retain();
	emitter->setGravity(CCPointZero);
	addChild(emitter, 10);

	emitter->setTexture( CCTextureCache::sharedTextureCache()->addImage("Particles/stars.png") );

	emitter->setAutoRemoveOnFinish(true);

	return emitter;
}