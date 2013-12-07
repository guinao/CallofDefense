#include "Zombie.h"
#include "ZombieManager.h"
#include "DemoScene.h"
#include "Plant.h"

//////////////////////////////////////////////////////////////////////////

Zombie::Zombie()
{
}

//////////////////////////////////////////////////////////////////////////

Zombie::~Zombie()
{
}

//////////////////////////////////////////////////////////////////////////

Zombie* Zombie::createZombie(ZombieType type, CCPoint pos)
{
	Zombie *p = new Zombie();
	p->m_type = type;
	p->m_state = en_ZombieMoving;

	bool bRet = false;

	p->m_speedy = 0.0f;

	do{
		char name[64], picture[64];
		int numFrames;
		switch(type)
		{
		case en_BucketheadZombie:
			numFrames = 15;
			p->m_speedx = 10.0f;
			p->m_hp = 100;
			strcpy(name, "BucketheadZombie");
			break;
		case en_ConeheadZombie:
			numFrames = 21;
			p->m_speedx = 10.0f;
			p->m_hp = 100;
			strcpy(name, "ConeheadZombie");
			break;
		case en_FlagZombie:
			numFrames = 12;
			p->m_speedx = 10.0f;
			p->m_hp = 100;
			strcpy(name, "FlagZombie");
			break;
		case en_NormalZombie:
			numFrames = 22;
			p->m_speedx = 10.0f;
			p->m_hp = 100;
			strcpy(name, "zombie");
			break;
		default:
			numFrames = 22;
			p->m_speedx = 10.0f;
			p->m_hp = 100;
			strcpy(name, "zombie");
			break;
		}

		sprintf(picture, "%s%03d.png", name, 1);

		p->m_sprite = CCSprite::createWithSpriteFrameName(picture);
		(p->m_sprite)->setPosition(pos);

		CCArray* animFrames = CCArray::createWithCapacity(numFrames);
		for(int i=1; i<=numFrames/*magic number*/; ++i)
		{
			sprintf(picture, "%s%03d.png", name, i);
			CCSpriteFrame* frame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(picture);
			animFrames->addObject(frame);
		}
		CCAnimation* animation = CCAnimation::createWithSpriteFrames(animFrames, 0.1f);
		CCAnimate* animate = CCAnimate::create(animation);
		p->m_animationAtEase = CCRepeatForever::create(animate);
		(p->m_sprite)->runAction(p->m_animationAtEase);

		(p->m_sprite)->setScale(1.5f);

		p->addChild(p->m_sprite, 10);

		bRet = true;
	}while(0);

	if(bRet)
	{
		p->autorelease();
		return p;
	}
	else
	{
		return NULL;
	}
}

//////////////////////////////////////////////////////////////////////////

void Zombie::createAnimations()
{
}

//////////////////////////////////////////////////////////////////////////

void Zombie::update(float delta)
{
	CCLOG("Zombie::update");
//	if(m_hp > 0)
	{
//		if(! findSomethingToEat())
		{
			moving(delta);
		}
	}
}

//////////////////////////////////////////////////////////////////////////

void Zombie::attack()
{
	CCLOG("Zombie::attack");
}

//////////////////////////////////////////////////////////////////////////

void Zombie::moving(float delta)
{
	CCLOG("Zombie::moving");
	char msg[128];

	CCPoint currentPos = m_sprite->getPosition();
	m_sprite->setPosition(ccp(currentPos.x - delta*m_speedx, currentPos.y + delta*m_speedy));

	sprintf(msg, "%f, %f, %f, %f", 
		myBoundingBox().getMinX(),
		myBoundingBox().getMinY(),
		myBoundingBox().getMaxX(),
		myBoundingBox().getMaxY());
	CCLOG(msg);

}

//////////////////////////////////////////////////////////////////////////

bool Zombie::findSomethingToEat()
{
	CCLOG("Zombie::findSomethingToEat");

	bool bRet = false;
	ZombieManager* p = dynamic_cast<ZombieManager*>(getParent());
	DemoScene* ds = dynamic_cast<DemoScene*>(p->getParent());
	Plant* plant = ds->findPlantInRange(myBoundingBox());
	char msg[128];
	CCRect rect = myBoundingBox();
	sprintf(msg, "%f, %f, %f, %f", rect.getMinX(), rect.getMinY(), rect.getMaxX(), rect.getMaxY());
	CCLOG(msg);

	if(NULL != plant)
	{
		plant->onHurt(1);

		bRet = true;
	}

	return bRet;
}

//////////////////////////////////////////////////////////////////////////

CCRect Zombie::myBoundingBox()
{	
	return m_sprite->boundingBox();
}

//////////////////////////////////////////////////////////////////////////

void Zombie::onHurt(int hurt, float xspeed, float yspeed)
{
	m_hp -= hurt;
	if(m_hp < 0)
	{
		m_sprite->stopAllActions();
		CCRotateBy *action1 = CCRotateBy::create(0.2, 180.0, 180.0);
		m_sprite->runAction(CCRepeatForever::create(action1));
		m_speedx = xspeed;
		m_speedy = yspeed;
	}
}