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

	do{
		char name[64], picture[64];
		int numFrames;
		switch(type)
		{
		case en_BucketheadZombie:
			numFrames = 15;
			p->m_speed = 10.0f;
			p->m_hp = 100;
			strcpy(name, "BucketheadZombie");
			break;
		case en_ConeheadZombie:
			numFrames = 21;
			p->m_speed = 10.0f;
			p->m_hp = 100;
			strcpy(name, "ConeheadZombie");
			break;
		case en_FlagZombie:
			numFrames = 12;
			p->m_speed = 10.0f;
			p->m_hp = 100;
			strcpy(name, "FlagZombie");
			break;
		case en_NormalZombie:
			numFrames = 22;
			p->m_speed = 10.0f;
			p->m_hp = 100;
			strcpy(name, "zombie");
			break;
		default:
			numFrames = 22;
			p->m_speed = 10.0f;
			p->m_hp = 100;
			strcpy(name, "zombie");
			break;
		}

		sprintf(picture, "%s%03d.png", name, 1);

		CCSprite* sprite = CCSprite::createWithSpriteFrameName(picture);
		sprite->setPosition(pos);

		p->addChild(sprite);



		CCArray* animFrames = CCArray::createWithCapacity(numFrames);
		for(int i=1; i<=numFrames/*magic number*/; ++i)
		{
			sprintf(picture, "%s%03d.png", name, i);
			CCSpriteFrame* frame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(picture);
			animFrames->addObject(frame);
		}
		CCAnimation* animation = CCAnimation::createWithSpriteFrames(animFrames, 0.1f);
		CCAnimate* animate = CCAnimate::create(animation);
		sprite->runAction(CCRepeatForever::create(animate));

		sprite->setScale(1.5f);

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
	// TODO: create animation for all kinds of actions
}

//////////////////////////////////////////////////////////////////////////

void Zombie::update(float delta)
{
	CCLOG("Zombie::update");
	if(m_hp > 0)
	{
		if(! findSomethingToEat())
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
	CCPoint currentPos = getPosition();
	setPosition(ccp(currentPos.x - delta*m_speed, currentPos.y));
}

//////////////////////////////////////////////////////////////////////////

bool Zombie::findSomethingToEat()
{
	bool bRet = false;

	ZombieManager* p = dynamic_cast<ZombieManager*>(getParent());
	DemoScene* ds = dynamic_cast<DemoScene*>(p->getParent());
	Plant* plant = ds->findPlantInRange(this->boundingBox());

	if(NULL != plant)
	{
		plant->onHurt(1);

		bRet = true;
	}

	return bRet;
}
