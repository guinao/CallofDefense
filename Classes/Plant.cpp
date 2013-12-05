#include "Plant.h"

Plant::Plant()
{
}

//////////////////////////////////////////////////////////////////////////

Plant::~Plant()
{
}

//////////////////////////////////////////////////////////////////////////

Plant* Plant::createPlant(PlantType type, CCPoint pos)
{
	Plant* p = new Plant();
	p->m_type = type;
	p->m_state = en_PlantAtEase;
	p->m_hp = 500;

	bool bRet = false;

	do{
		char name[64], picture[64];
		int numFrames;

		switch(type)
		{
		case en_CherryBomb:
			numFrames = 8;
			strcpy(name, "CherryBomb");
			break;
		case en_ScaredyShroom:
			numFrames = 17;
			strcpy(name, "ScaredyShroom");
			break;
		case en_IcePea:
			numFrames = 15;
			strcpy(name, "IcePea");
			break;
		case en_SunFlower:
			numFrames = 18;
			strcpy(name, "SunFlower");
			break;
		case en_Threepeater:
			numFrames = 16;
			strcpy(name, "Threepeater");
			break;
		case en_WallNut:
			numFrames = 16;
			strcpy(name, "WallNut");
			break;
		case en_PeaShooter:
			numFrames = 13;
			strcpy(name, "peashooter");
			break;
		default:
			numFrames = 13;
			strcpy(name, "peashooter");
			break;
		}

		sprintf(picture, "%s%03d.png", name, 1);

		CCSprite* sprite = CCSprite::createWithSpriteFrameName(picture);
		sprite->setPosition(pos);

		p->setSprite(sprite);

		CCArray* animFrames = CCArray::createWithCapacity(numFrames);
		for(int i=1; i<=numFrames/*magic number*/; ++i)
		{
			sprintf(picture, "%s%03d.png", name, i);
			CCSpriteFrame* frame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(picture);
			animFrames->addObject(frame);
		}
		CCAnimation* animation = CCAnimation::createWithSpriteFrames(animFrames, 0.1f);
		animation->setLoops(-1);

		
		sprite->runAction(CCAnimate::create(animation));

		p->setScale(1.5);

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

void Plant::createAnimations()
{
	// TODO: create animation for all kinds of actions
}

//////////////////////////////////////////////////////////////////////////

void Plant::update(float delta)
{
	if(m_hp > 0)
	{
		CCPoint direction = ccp(0, 0);
		if( findAim(direction) )
		{
			attack(direction);
		}
		else
		{
			idle();
		}
	}
}

//////////////////////////////////////////////////////////////////////////

void Plant::attack(CCPoint& direction)
{
	CCLOG("Plant::attack");
	switch(m_type)
	{
	case en_CherryBomb:
		break;
	case en_ScaredyShroom:
		break;
	case en_IcePea:
		break;
	case en_Threepeater:
		break;
	case en_PeaShooter:
		break;
	default:
		break;
	}
}

//////////////////////////////////////////////////////////////////////////

void Plant::idle()
{
	CCLOG("Plant::idle");
}

//////////////////////////////////////////////////////////////////////////

bool Plant::findAim(CCPoint& direction)
{
	bool bRet = false;

	// TODO:

	return bRet;
}

//////////////////////////////////////////////////////////////////////////

void Plant::onHurt(int hp)
{
	CCLOG("Plant::onHurt");
	m_hp -= hp;
}

//////////////////////////////////////////////////////////////////////////

void Plant::setSprite(CCSprite* sprite)
{
	m_sprite = sprite;
	addChild(m_sprite);
}

//////////////////////////////////////////////////////////////////////////

CCRect Plant::myBoundingBox()
{
	CCSize size = m_sprite->getContentSize();

	return CCRectMake(
		getPositionX()-size.width/2,
		getPositionY()-size.height/2,
		size.width,
		size.height);
}