#include "SpaceAdventureScene.h"
#include "BootScene.h"

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
//		CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("PvZres2/peashooter.plist");
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
		//createZombies();
		createShield();

		NOTIFY->addObserver(
			this, 
			callfuncO_selector(SpaceAdventureScene::loseGame), 
			kLoseMessage,
			NULL);
		bRet = true;
	}while(0);

	return bRet;
}

//////////////////////////////////////////////////////////////////////////

static void printRect(const CCRect& rect)
{
	char msg[128];
	sprintf(msg, "%f, %f, %f, %f",
		rect.getMinX(),
		rect.getMinY(),
		rect.getMaxX(),
		rect.getMaxY());

	CCLOG(msg);

}

static bool isCollide(const CCRect& r1, const CCRect& r2)
{
	bool bRet = false;
	if(r1.intersectsRect(r2))
	{
		double area1 = (r1.getMaxX()-r1.getMinX())*(r1.getMaxY()-r1.getMinY());
		double area2 = (r2.getMaxX()-r2.getMinX())*(r2.getMaxY()-r2.getMinY());
		float maxX = min(r1.getMaxX(), r2.getMaxX());
		float minX = max(r1.getMinX(), r2.getMinX());
		float maxY = min(r1.getMaxY(), r2.getMaxY());
		float minY = max(r1.getMinY(), r2.getMinY());
		double interarea = (maxX-minX) * (maxY-minY);

		bRet = interarea * 5 > max(area1, area2);
	}
	return bRet;
}

static bool inVisibleRigion(const CCRect& rect)
{
	CCSize size = CCDirector::sharedDirector()->getVisibleSize();

	return rect.getMinX() < size.width
		&& rect.getMaxX() > 0
		&& rect.getMinY() < size.height
		&& rect.getMaxY() > 0;
}

//////////////////////////////////////////////////////////////////////////

void SpaceAdventureScene::update(float delta)
{
	//if( m_zombiemanager->hitDetect(m_nut->myBoundingBox()) )
	//{
	//	m_nut->reverseSpeedX();
	//	m_nut->reverseSpeedY();
	//}

	vector<SpaceZombie*> vz;

	CCRect nutrect = m_nut->myBoundingBox();
	
	for(int i=0; i<(int)m_zombies.size(); ++i)
	{
		CCRect zombierect = m_zombies[i]->myBoundingBox();

		if( !inVisibleRigion(zombierect) )
		{
//			m_zombies[i]->setVisible(false);
			removeChild(m_zombies[i]);
			continue;
		}

		switch(m_zombies[i]->getZombieState())
		{
		case en_ZombieAttacking:
		case en_ZombieMoving:
		case en_ZombieStopped:
			if( isCollide(nutrect, zombierect) )
			{
				processCollide(m_nut, m_zombies[i]);
			}
			vz.push_back(m_zombies[i]);
			break;
		case en_ZombieDead:
		case en_ZombieFlyAway:
		default:
			break;
		}
	}

	m_zombies = vz;

	SpaceZombie *zombie = generateZombie();
	if( NULL != zombie )
	{
		addChild(zombie,35);
		m_zombies.push_back(zombie);
	}

}

void SpaceAdventureScene::processCollide(SpaceNut* nut, SpaceZombie* zombie)
{
	float m1 = nut->getWeight();
	float v1x = nut->getSpeedX();
	float v1y = nut->getSpeedY();

	float m2 = zombie->getWeight();
	float v2x = zombie->getSpeedX();
	float v2y = zombie->getSpeedY();

	zombie->hit(v1x, v1y, m1);

	m_nut->hit(v2x, v2y, m2);
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

	m_nut->changeSpeedXBy(x*50);
	m_nut->changeSpeedYBy(y*50);

	//m_zombiemanager->didAccelerate(pAccelerationValue, m_label);
}

void SpaceAdventureScene::onExit()
{
	unscheduleUpdate();
	setAccelerometerEnabled(false);
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

	addChild(m_shield);
}

SpaceZombie* SpaceAdventureScene::generateZombie()
{
	SpaceZombie *zombie = NULL;
	srand(time(NULL));
	if( m_zombies.size()<1 && rand()%200 < 200 )
	{
		ZombieType type = static_cast<ZombieType>(rand()%4+1);

		CCSize size = CCDirector::sharedDirector()->getVisibleSize();
		CCPoint startpos;
		switch(rand() % 4)
		{
		case 0:	// from left
			startpos = ccp(0, rand()%static_cast<int>(size.height));
			break;
		case 1:	// from top
			startpos = ccp(rand()%static_cast<int>(size.width), size.height);
			break;
		case 2:	// from right
			startpos = ccp(size.width, rand()%static_cast<int>(size.height));
			break;
		case 3:	// from buttom
			startpos = ccp(rand()%static_cast<int>(size.width), 0);
			break;
		} 
		zombie = SpaceZombie::createSpaceZombie(type, startpos);
	}

	return zombie;
}

void SpaceAdventureScene::loseGame(CCObject*)
{
	CCDirector::sharedDirector()->replaceScene(BootScene::scene());
}

void SpaceAdventureScene::winGame(CCObject*)
{

}