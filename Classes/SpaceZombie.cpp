#include "SpaceZombie.h"
#include "Shield.h"

static void normalize(CCPoint &d)
{
	float r = sqrt(d.x*d.x + d.y*d.y);
	d.x /= r;
	d.y /= r;
}

SpaceZombie* SpaceZombie::createSpaceZombie(ZombieType type, CCPoint pos)
{
	SpaceZombie *p = new SpaceZombie();
	if(p->init(type, pos))
	{
		return p;
	}
	else
	{
		return NULL;
	}
}

bool SpaceZombie::init(ZombieType type, CCPoint pos)
{
	bool bRet = false;

	do{
		m_type = type;
		m_state1 = en_ZombieMoving;
		m_state2 = en_Floating;
		
		Shield *shield = Shield::getShieldSingleton();
		float r, x, y;
		shield->getCenterAndRadius(r, x, y);

		m_direction = ccp(x-pos.x, y-pos.y);
		normalize(m_direction);

		m_aicount = 0;

		char name[64], picture[64];
		int numFrames;
		switch(type)
		{
		case en_BucketheadZombie:
			numFrames = 15;
			m_speed = 10.0f;
			m_hp = 100;
			m_ai = 20;
			strcpy(name, "BucketheadZombie");
			break;
		case en_ConeheadZombie:
			numFrames = 21;
			m_speed = 10.0f;
			m_hp = 100;
			m_ai = 40;
			strcpy(name, "ConeheadZombie");
			break;
		case en_FlagZombie:
			numFrames = 12;
			m_speed = 10.0f;
			m_hp = 100;
			m_ai = 80;
			strcpy(name, "FlagZombie");
			break;
		case en_NormalZombie:
			numFrames = 22;
			m_speed = 10.0f;
			m_hp = 100;
			m_ai = 10;
			strcpy(name, "zombie");
			break;
		default:
			numFrames = 22;
			m_speed = 10.0f;
			m_hp = 100;
			m_ai = 10;
			strcpy(name, "zombie");
			break;
		}

		sprintf(picture, "%s%03d.png", name, 1);

		m_sprite = CCSprite::createWithSpriteFrameName(picture);
		m_sprite->setPosition(pos);
		m_sprite->setScale(2.0);

		addChild(m_sprite, 10);

		scheduleUpdate();

		//////////////////////////////////////////////////////////////////////////
		//	create walking animation
		CCArray* animFrames = CCArray::createWithCapacity(numFrames);
		for(int i=1; i<=numFrames/*magic number*/; ++i)
		{
			sprintf(picture, "%s%03d.png", name, i);
			CCSpriteFrame* frame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(picture);
			animFrames->addObject(frame);
		}
		CCAnimation* animation = CCAnimation::createWithSpriteFrames(animFrames, 0.1f);
		CCAnimate* animate = CCAnimate::create(animation);
		m_animationWalking = CCRepeatForever::create(animate);

		//////////////////////////////////////////////////////////////////////////
		// create floating animation
		CCRotateBy *action2 = CCRotateBy::create(0.2, 18.0, 18.0);
		CCActionInterval *action3 = action2->reverse();
		CCSequence *action4 = CCSequence::create(
			action2, action3, action3, action2, NULL);
		m_animationFloating = CCRepeatForever::create(action4);

		bRet = true;
	}while(0);

	return bRet;
}

void SpaceZombie::update(float delta)
{
	switch(m_state1)
	{
	case en_ZombieMoving:
		performMove(delta);
		break;
	case en_ZombieAttacking:
		break;
	case en_ZombieDead:
		if()
		{

		}
		break;
	case en_ZombieStopped:
		break;
	default:
		break;
	}
}

void SpaceZombie::performMove(float delta)
{	
	Shield *shield = Shield::getShieldSingleton();
	float r, x, y;
	shield->getCenterAndRadius(r, x, y);
	float dx = x - m_sprite->getPositionX();
	float dy = y - m_sprite->getPositionY();
	
	StateInSpace state;
	if(r*r > dx*dx + dy*dy)
	{
		state = en_Floating;
	}
	else
	{
		state = en_InShield;
	}
	if(state != m_state2)
	{
		m_sprite->stopAllActions();
		switch(state)
		{
		case en_Floating:
			m_sprite->runAction(m_animationFloating);
			srand(time(NULL));
			m_aicount += rand() % m_ai;
			if(m_aicount > hasAI)
			{
				m_direction = ccp(dx, dy);
				normalize(m_direction);
			}
			x = m_sprite->getPositionX() + m_direction.x * m_speed * 2;
			y = m_sprite->getPositionY() + m_direction.y * m_speed * 2;
			m_sprite->setPosition(ccp(x,y));
			break;
		case en_InShield:
			m_sprite->runAction(m_animationWalking);
			srand(time(NULL));
			m_aicount += rand() % m_ai;
			if(m_aicount > hasAI)
			{
				m_direction = ccp(dx, dy);
				normalize(m_direction);
			}
			x = m_sprite->getPositionX() + m_direction.x * m_speed;
			y = m_sprite->getPositionY() + m_direction.y * m_speed;
			m_sprite->setPosition(ccp(x,y));

			break;
		}
		m_state2 = state;
	}
}

void SpaceZombie::hitAway(float x, float y)
{
	m_state1 = en_ZombieDead;
	m_hp = -1;
	CCRotateBy *rotate1 = CCRotateBy::create(1.0f, 20.0f, 20.0f);
	CCActionInterval *rotate2 = rotate1->reverse();
	CCSequence *action = CCSequence::create(
		rotate1,
		rotate2,
		rotate2,
		rotate1,
		NULL);
	m_sprite->runAction(CCRepeatForever::create(action));
	m_direction = ccp(x, y);
}