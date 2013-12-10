#include "SimpleAudioEngine.h"
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
		m_facingLeft = true;
		m_weight = kZombieWeight;
		m_aicount = 0;

		CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect("music/crash1.wav");

		char name[64], picture[64];
		int numFrames;
		switch(type)
		{
		case en_BucketheadZombie:
			numFrames = 15;
			m_speed = kZombieSpeedFloating;
			m_hp = 100;
			m_ai = 20;
			strcpy(name, "BucketheadZombie");
			break;
		case en_ConeheadZombie:
			numFrames = 21;
			m_speed = kZombieSpeedFloating;
			m_hp = 100;
			m_ai = 40;
			strcpy(name, "ConeheadZombie");
			break;
		case en_FlagZombie:
			numFrames = 12;
			m_speed = kZombieSpeedFloating;
			m_hp = 100;
			m_ai = 80;
			strcpy(name, "FlagZombie");
			break;
		case en_NormalZombie:
			numFrames = 22;
			m_speed = kZombieSpeedFloating;
			m_hp = 100;
			m_ai = 10;
			strcpy(name, "zombie");
			break;
		default:
			numFrames = 22;
			m_speed = kZombieSpeedFloating;
			m_hp = 100;
			m_ai = 10;
			strcpy(name, "zombie");
			break;
		}

		sprintf(picture, "%s%03d.png", name, 1);

		m_sprite = CCSprite::createWithSpriteFrameName(picture);
		m_sprite->setPosition(pos);
		m_sprite->setScale(2.0);

		m_sprite->runAction(createFloatingAction());

		Shield *shield = Shield::getShieldSingleton();
		float r, x, y;
		shield->getCenterAndRadius(r, x, y);

		m_direction = ccp(x-pos.x, y-pos.y);

		updateState2();

		normalize(m_direction);
		updateFacing();

		scheduleUpdate();

		bRet = true;
	}while(0);

	return bRet;
}

void SpaceZombie::updateState2()
{
	Shield *shield = Shield::getShieldSingleton();
	float r, x, y;
	shield->getCenterAndRadius(r, x, y);
	float dx = x - m_sprite->getPositionX();
	float dy = y - m_sprite->getPositionY();

	if(r*r < dx*dx + dy*dy)
	{
		m_state2 = en_Floating;
	}
	else
	{
		m_state2 = en_InShield;
	}
}

void SpaceZombie::updateFacing()
{
	if(m_direction.x > 0 && m_facingLeft)
	{
		m_sprite->setFlipX(true);
		m_facingLeft = false;
	}
	else if(m_direction.x < 0 && !m_facingLeft)
	{
		m_sprite->setFlipX(false);
		m_facingLeft = true;
	}
}

void SpaceZombie::update(float delta)
{
	switch(m_state1)
	{
	case en_ZombieMoving:
		performMove(delta);
		break;
	case en_ZombieAttacking:
		performAttacking(delta);
		break;
	case en_ZombieDead:
		//CCLOG("Zombie Dead");
		break;
	case en_ZombieStopped:
		//CCLOG("Zombie Stoped");
		break;
	case en_ZombieFlyAway:
		performFlyAway(delta);
		break;
	default:
		break;
	}
}

void SpaceZombie::performMove(float delta)
{	
	//CCLOG("SpaceZombie::performMove");
	char msg[128];
	sprintf(msg, "Position: %f, %f, Direction: %f, %f", 
		m_sprite->getPositionX(), m_sprite->getPositionY(), m_direction.x, m_direction.y);
	//CCLOG(msg);

	StateInSpace state;

	Shield *shield = Shield::getShieldSingleton();
	float r, x, y;
	shield->getCenterAndRadius(r, x, y);
	float dx = x - m_sprite->getPositionX();
	float dy = y - m_sprite->getPositionY();

	if(r*r < dx*dx + dy*dy)
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
			m_speed = kZombieSpeedFloating;
			m_sprite->runAction(createFloatingAction());
			NOTIFY->postNotification(kZombieLeaveMessage, NULL);
			break;
		case en_InShield:
			m_speed = kZombieSpeedInShield;
			m_sprite->runAction(createWalkingAction());
			NOTIFY->postNotification(kZombiesOnBoardMessage, NULL);
			break;
		}
		m_state2 = state;
	}

	switch(m_state2)
	{
	case en_Floating:
		srand(time(NULL));
		m_aicount += rand() % m_ai;
		if(m_aicount > hasAI)
		{
			m_direction = ccp(dx, dy);
			normalize(m_direction);
			updateFacing();
			m_aicount = 0;
		}
		x = m_sprite->getPositionX() + m_direction.x * m_speed * delta;
		y = m_sprite->getPositionY() + m_direction.y * m_speed * delta;
		m_sprite->setPosition(ccp(x,y));
		break;
	case en_InShield:
		srand(time(NULL));
		m_aicount += rand() % m_ai;
		if(m_aicount > hasAI)
		{
			m_direction = ccp(dx, dy);
			normalize(m_direction);
			updateFacing();
			m_aicount = 0;
		}
		x = m_sprite->getPositionX() + m_direction.x * m_speed * delta;
		y = m_sprite->getPositionY() + m_direction.y * m_speed * delta;
		m_sprite->setPosition(ccp(x,y));

		shield->getCenterAndRadius(r, x, y);
		if(m_sprite->boundingBox().containsPoint(ccp(x,y)))
		{
			m_state1 = en_ZombieAttacking;
			//NOTIFY->postNotification(kZombiesOnBoardMessage, NULL);
		}
		break;
	}
}

void SpaceZombie::performFlyAway(float delta)
{
//	CCLOG("SpaceZombie::performFlyAway");
	float x = m_sprite->getPositionX() + m_direction.x * m_speed * delta;
	float y = m_sprite->getPositionY() + m_direction.y * m_speed * delta;
	m_sprite->setPosition(ccp(x,y));
}

void SpaceZombie::hit(float v1x, float v1y, float m1)
{
	char msg[128];
	sprintf(msg,"Before hit, direction: %f, %f", m_direction.x, m_direction.y);
//	CCLOG(msg);
	CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("music/crash1.wav");
	updateState2();

	if(m_state2 == en_Floating)
	{
		float v2x = getSpeedX();
		float v2y = getSpeedY();

		m_direction.x = -m_direction.x;
		m_direction.y = -m_direction.y;
		m_speed = kZombieSpeedFlyAway;

		m_sprite->stopAllActions();
		m_sprite->runAction(createFlyAwayAction());
		
		m_state1 = en_ZombieFlyAway;
		scoreChanged();

		sprintf(msg,"After hit, direction: %f, %f", m_direction.x, m_direction.y);
		//CCLOG(msg);
	}
	else if(m_state2 == en_InShield)
	{
		m_hp -= m1;
		if(m_hp <= 0)
		{
			m_facingLeft = v1x < 0 ? true : false;
			scoreChanged();
			performDead();
		}
	}
}

void SpaceZombie::performDead()
{
	if(en_ZombieAttacking == m_state1)
	{
		NOTIFY->postNotification(kZombieLeaveMessage, NULL);
	}

	m_state1 = en_ZombieFlyAway;
	m_sprite->stopAllActions();

	float rot = 90.0f;
	if(!m_facingLeft)
	{
		rot = -rot;
	}
	if(m_sprite->isFlipX())
	{
		rot = -rot;
	}
	CCRotateTo *action1 = CCRotateTo::create(0.2f, rot);
	CCFadeOut *action2 = CCFadeOut::create(5.0f);
	CCTintTo *action3 = CCTintTo::create(5.0f, 0, 0, 0);
	CCCallFunc *action4 = CCCallFunc::create(this,callfunc_selector(SpaceZombie::finishDeadAction));
	CCSequence *action  = CCSequence::create(action1, action2, action3, action4, NULL);
	m_sprite->runAction(action);

}

void SpaceZombie::finishDeadAction()
{
	m_state1 = en_ZombieDead;
}

void SpaceZombie::performAttacking(float delta)
{
	Shield* shield = Shield::getShieldSingleton();
	float r, x, y;
	shield->getCenterAndRadius(r, x, y);
	if( m_sprite->boundingBox().containsPoint(ccp(x,y)) )
	{
		shield->onHurt(100.0*delta);
	}
	else
	{
		m_state1 = en_ZombieMoving;
		NOTIFY->postNotification(kZombieLeaveMessage, NULL);
		updateState2();
	}
}

CCAction* SpaceZombie::createWalkingAction()
{
	char name[64], picture[64];
	int numFrames;
	switch(m_type)
	{
	case en_BucketheadZombie:
		numFrames = 15;
		strcpy(name, "BucketheadZombie");
		break;
	case en_ConeheadZombie:
		numFrames = 21;
		strcpy(name, "ConeheadZombie");
		break;
	case en_FlagZombie:
		numFrames = 12;
		strcpy(name, "FlagZombie");
		break;
	case en_NormalZombie:
		numFrames = 22;
		strcpy(name, "zombie");
		break;
	default:
		numFrames = 22;
		strcpy(name, "zombie");
		break;
	}

	CCArray* animFrames = CCArray::createWithCapacity(numFrames);
	for(int i=1; i<=numFrames/*magic number*/; ++i)
	{
		sprintf(picture, "%s%03d.png", name, i);
		CCSpriteFrame* frame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(picture);
		animFrames->addObject(frame);
	}
	CCAnimation* animation = CCAnimation::createWithSpriteFrames(animFrames, 0.2f);
	CCAnimate* animate = CCAnimate::create(animation);
	return CCRepeatForever::create(animate);
}

CCAction* SpaceZombie::createFloatingAction()
{
	CCRotateBy *action2 = CCRotateBy::create(1.0f, 10.0f, 10.0f);
	CCActionInterval *action3 = action2->reverse();
	CCSequence *action4 = CCSequence::create(
		action2, action3, action3, action2, NULL);
	return CCRepeatForever::create(action4);
}

CCAction* SpaceZombie::createFlyAwayAction()
{
	CCRotateBy *action1 = CCRotateBy::create(0.2f, 180.0f, 180.0f);
	return CCRepeatForever::create(action1);
}

void SpaceZombie::scoreChanged()
{
	int score;
	switch(m_type)
	{
	case en_NormalZombie:
		score = 10;
		break;
	case en_FlagZombie:
		score = 15;
		break;
	case en_ConeheadZombie:
		score = 30;
		break;
	case en_BucketheadZombie:
		score = 50;
		break;
	default:
		score = 10;
	}
	NOTIFY->postNotification(kScoreChangedMessage, CCInteger::create(score));
}

void SpaceZombie::performShocked()
{
	switch(m_state1)
	{
	case en_ZombieAttacking:
	case en_ZombieMoving:
		m_statae1old = m_state1;
		m_state1 = en_ZombieStopped;
		scheduleOnce(schedule_selector(SpaceZombie::recover), 10.0f);
		break;
	case en_ZombieDead:
	case en_ZombieFlyAway:
	case en_ZombieStopped:
	default:
		break;
	}
}

void SpaceZombie::recover(float)
{
	m_state1 = m_statae1old;
}