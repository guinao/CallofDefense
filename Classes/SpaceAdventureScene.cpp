#include "SpaceAdventureScene.h"

SpaceAdventureScene::SpaceAdventureScene()
{
	CC_SAFE_RETAIN(Shield::getShieldSingleton());

	m_maxshakevalue = 0.0;
	m_shakevaluebound = 10.0;
}

SpaceAdventureScene::~SpaceAdventureScene()
{
//	CC_SAFE_RELEASE(Shield::getShieldSingleton());
}

CCScene* SpaceAdventureScene::scene()
{
	CCScene* scene = NULL;

	do{
		scene = CCScene::create();
		CC_BREAK_IF(! scene);

		SpaceAdventureScene* layer = SpaceAdventureScene::create();
		CC_BREAK_IF(! layer);

		scene->addChild(layer);
	}while (0);

	return scene;
}

bool SpaceAdventureScene::init()
{
	bool bRet = false;

	do{
		CC_BREAK_IF(! CCLayer::init());

		CCTexture2D::PVRImagesHavePremultipliedAlpha(true);
		CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("PvZres2/peashooter.plist");
		CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("PvZres2/plants_type.plist");
		CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("PvZres2/zombies_type.plist");
		CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("PvZres2/plant_sun.plist");
		CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("PvZres2/cardMenu.plist");

		CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();

		m_label = CCLabelAtlas::create("1:", "nums_font.png", 14, 21, '0');
		m_label->setString("111");
		m_label->setPosition(ccp(visibleSize.width/2, visibleSize.height-40));
		this->addChild(m_label, 10, 1);

		setAccelerometerEnabled(true);
		scheduleUpdate();

		createNut();
		createZombies();
		createShield();

		bRet = true;
	}while(0);

	return bRet;
}

void SpaceAdventureScene::update(float delta)
{
	if( m_zombiemanager->hitDetect(m_nut->myBoundingBox()) )
	{
		m_nut->reverseXSpeed();
		m_nut->reverseYSpeed();
	}
}

void SpaceAdventureScene::didAccelerate(CCAcceleration* pAccelerationValue)
{
	char output[128];

	double x = pAccelerationValue->x;
	double y = pAccelerationValue->y;
	double z = pAccelerationValue->z;
	double all = x*x + y*y + z*z;

	sprintf(output, "SpaceAdventureScene::didAccelerate:%f, %f, %f", x, y, z);
	CCLOG(output);

	m_nut->changeXSpeedBy(x*50);
	m_nut->changeYSpeedBy(y*50);

	m_zombiemanager->didAccelerate(pAccelerationValue, m_label);
}

void SpaceAdventureScene::onExit()
{
}

void SpaceAdventureScene::createNut()
{
	m_nut = SpaceNut::create();
	addChild(m_nut,40);
}

void SpaceAdventureScene::createZombies()
{
	m_zombiemanager = ZombieManager::create();
	addChild(m_zombiemanager, 30);
}

void SpaceAdventureScene::createShield()
{
	m_shield = Shield::getShieldSingleton();

	addChild(m_shield, 50);
}