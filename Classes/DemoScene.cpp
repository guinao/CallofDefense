#include "DemoScene.h"
#include "GlobalPath.h"
#include "GlobalParam.h"
#include "SceneManager.h"
#include <vector>
using namespace std;

//////////////////////////////////////////////////////////////////////////

CCScene* DemoScene::scene()
{
	CCScene* scene = NULL;

	do{
		scene = CCScene::create();
		CC_BREAK_IF(! scene);

		DemoScene* layer = DemoScene::create();
		CC_BREAK_IF(! layer);

		scene->addChild(layer);
	}while (0);

	return scene;
}

//////////////////////////////////////////////////////////////////////////

bool DemoScene::init()
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

		//////////////////////////////////////////////////////////////////////////

		// init for acceler
//		this->setAccelerometerEnabled(true);
		this->scheduleUpdate();

//		this->setAccelerometerInterval(1./60);
		m_shakeCnt = 0;
		m_swingCnt = 0;

		//////////////////////////////////////////////////////////////////////////

		CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();

		m_label = CCLabelAtlas::create("1:", "nums_font.png", 14, 21, '0');
		m_label->setString("111");
		m_label->setPosition(ccp(visibleSize.width/2, visibleSize.height-40));
		this->addChild(m_label, 0, 1);

		labForTouchLayer();

		labForPlantManager();

		CC_BREAK_IF(! labForZombieManager());

		//labForSunShine();

		//labForCCSprites();

		//labForCCAnimation();

		//labForCCScale9Sprite();

		//this->schedule(schedule_selector(DemoScene::backToTollgateSelectScene), 3.0f);

		bRet = true;
	}while(0);

	return bRet;
}

//////////////////////////////////////////////////////////////////////////

void DemoScene::backToTollgateSelectScene(float dt)
{
	char output[100];
	sprintf(output, "%f", dt);
	
	m_label->setString(output);
}

//////////////////////////////////////////////////////////////////////////

void DemoScene::labForCCSprites()
{
	CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();

	// add a node with ccsprite elements
	CCNode* plantnode1 = CCNode::create();
	plantnode1->setAnchorPoint(ccp(0.5, 0.5));

	CCPoint center = ccp(visibleSize.width/2, visibleSize.height/2);

	CCSprite* plant1 = CCSprite::create("PvZelements/PeaShooter_Head.png");
	plant1->setPosition(ccp(center.x, center.y));
	plantnode1->addChild(plant1);

	CCLOG("%f %f\n", center.x, center.y);

	CCSprite* plant2 = CCSprite::create("PvZelements/GatlingPea_mouth.png");
	plant2->setPosition(ccp(center.x + 0.685*plant1->getContentSize().width, center.y + 0.15 * plant1->getContentSize().height));
	plantnode1->addChild(plant2);

	CCSprite* plant4 = CCSprite::create("PvZelements/PeaShooter_stalk_top.png");
	plant4->setPosition(ccp(center.x, center.y - 0.5 * plant1->getContentSize().height));
	plantnode1->addChild(plant4);

	CCSprite* plant3 = CCSprite::create("PvZelements/PeaShooter_stalk_bottom.png");
	plant3->setPosition(ccp(center.x, center.y - 0.5*plant1->getContentSize().height-plant4->getContentSize().height));
	plantnode1->addChild(plant3);

	this->addChild(plantnode1);
}

//////////////////////////////////////////////////////////////////////////

void DemoScene::labForCCScale9Sprite()
{
	CCTexture2D::PVRImagesHavePremultipliedAlpha(true);
	CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("PvZres2/peashooter.plist");

	char name[32];

	CCScale9Sprite* peashooter = CCScale9Sprite::createWithSpriteFrameName("peashooter001.png");
	peashooter->setPosition(ccp(200, 200));
	CCSize size = peashooter->getContentSize();
	peashooter->setContentSize(CCSize(size.width*2, size.height*2));
	this->addChild(peashooter);

	CCArray* animFrames = CCArray::createWithCapacity(13);
	for(int i=1; i<=13; ++i)
	{
		sprintf(name, "peashooter%03d.png", i);
		CCSpriteFrame* frame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(name);
		animFrames->addObject(frame);
	}
	CCAnimation* animation = CCAnimation::createWithSpriteFrames(animFrames, 0.1f);
	animation->setLoops(-1);

	//peashooter->runAction(CCAnimate::create(animation));

	CCSpriteFrameCache::sharedSpriteFrameCache()->removeSpriteFrameByName("PvZres2/peashooter.plist");

}

//////////////////////////////////////////////////////////////////////////

void DemoScene::labForCCAnimation()
{
	// Create a peashooter using animation frames
	CCTexture2D::PVRImagesHavePremultipliedAlpha(true);
	CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("PvZres2/peashooter.plist");

	char name[32];

	CCSprite* peashooter = CCSprite::createWithSpriteFrameName("peashooter001.png");
	peashooter->setPosition(ccp(100, 100));
	this->addChild(peashooter);

	CCArray* animFrames = CCArray::createWithCapacity(13);
	for(int i=1; i<=13; ++i)
	{
		sprintf(name, "peashooter%03d.png", i);
		CCSpriteFrame* frame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(name);
		animFrames->addObject(frame);
	}
	CCAnimation* animation = CCAnimation::createWithSpriteFrames(animFrames, 0.1f);
	animation->setLoops(-1);

	peashooter->runAction(CCAnimate::create(animation));
	CCSpriteFrameCache::sharedSpriteFrameCache()->removeSpriteFrameByName("PvZres2/peashooter.plist");
}

//////////////////////////////////////////////////////////////////////////

void DemoScene::labForCCAction()
{
	
}

//////////////////////////////////////////////////////////////////////////

void DemoScene::didAccelerate(CCAcceleration* pAccelerationValue)
{
	m_zombiemanager->didAccelerate(pAccelerationValue, m_label);
}

//////////////////////////////////////////////////////////////////////////

void DemoScene::labForPlantManager()
{
	CCSize size = CCDirector::sharedDirector()->getVisibleSize();
	vector<PlantType> v1;
	vector<CCPoint> v2;
	v1.push_back(en_CherryBomb);
	v1.push_back(en_IcePea);
	v1.push_back(en_SunFlower);
	v1.push_back(en_WallNut);
	v1.push_back(en_PeaShooter);
	v1.push_back(en_ScaredyShroom);
	v1.push_back(en_Threepeater);
	int gridy = 10;
	int gridx = 14;
	float dx = size.width / gridx;
	float dy = size.height / gridy;
	for(int i=0; i<7; ++i)
	{
		float x = i / gridy * dx + 2 * dx;
		float y = i % gridy * dy + 1 * dy;
		v2.push_back(ccp(x, y));
	}

	m_plantmanager = PlantManager::create();
	m_plantmanager->createPlants(v1, v2);
	this->addChild(m_plantmanager);
}

//////////////////////////////////////////////////////////////////////////

bool DemoScene::labForZombieManager()
{
	bool bRet = false;

	do{
		CCSize size = CCDirector::sharedDirector()->getVisibleSize();
		vector<ZombieType> v1;
		vector<CCPoint> v2;
		v1.push_back(en_BucketheadZombie);
		v1.push_back(en_ConeheadZombie);
		v1.push_back(en_FlagZombie);
		v1.push_back(en_NormalZombie);
		int grid = 8;
		float dx = size.width / grid;
		float dy = size.height / grid;
		for(int i=0; i<4; ++i)
		{
			float x = i / (grid-1) * dx + dx;
			float y = i % (grid-1) * dy + dy;
			v2.push_back(ccp(size.width-x, size.height-y));
		}

		m_zombiemanager = ZombieManager::create();
		CC_BREAK_IF(! m_zombiemanager);
		m_zombiemanager->createZombies(v1, v2);
		this->addChild(m_zombiemanager);

		bRet = true;
	}while(0);

	return bRet;
}

//////////////////////////////////////////////////////////////////////////

void DemoScene::update(float delta)
{
	getPlantsPosition();
	getZombiesPosition();
	switch (checkGameState())
	{
	case en_GameLose:
		break;
	case en_GameWin:
		break;
	case en_GameTied:
	default:
		break;
	}
}

//////////////////////////////////////////////////////////////////////////

GameState DemoScene::checkGameState()
{
	return en_GameTied;
}

//////////////////////////////////////////////////////////////////////////

void DemoScene::labForSunShine()
{
	SunShine* sun = SunShine::createSunShine(50);
	addChild(sun);
}

//////////////////////////////////////////////////////////////////////////

void DemoScene::labForTouchLayer()
{
	TouchLayer* layer1 = TouchLayer::create();
	addChild(layer1);
}

//////////////////////////////////////////////////////////////////////////

void DemoScene::getPlantsPosition()
{
	m_plantmanager->getPlantsPosition(m_plantsposition);
}

//////////////////////////////////////////////////////////////////////////

void DemoScene::getZombiesPosition()
{
	m_zombiemanager->getZombiesPosition(m_zombiesposition);
}

//////////////////////////////////////////////////////////////////////////

Plant* DemoScene::findPlantInRange(CCRect rect)
{
	Plant* p = NULL;

	CCObject *Obj;
	CCARRAY_FOREACH(m_plantmanager->m_plants, Obj)
	{
		Plant *plant = dynamic_cast<Plant*>(Obj);
		if(plant->boundingBox().intersectsRect(rect) && plant->isAlive())
		{
			p = plant;
			break;
		}
	}

	return p;
}