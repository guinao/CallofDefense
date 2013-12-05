#include "Shield.h"

Shield* Shield::m_shield = NULL;

Shield::Shield()
{
	m_touched = false;
	m_radius = 200.0f;
}

Shield::~Shield()
{
}

Shield* Shield::getShieldSingleton()
{
	if(NULL == m_shield)
	{
		m_shield = Shield::create();
		if(NULL != m_shield)
		{
			m_shield->autorelease();
		}
	}

	return m_shield;
}

bool Shield::init()
{
	bool bRet = false;

	do{
		m_sprite = CCSprite::create("PvZelements/Tallnut_body.png");
		CCRotateBy *action1 = CCRotateBy::create(1, 20, 20);
		CCActionInterval *action2 = action1->reverse();
		CCSequence *action3 = CCSequence::create(
			action1, 
			action2, 
			action2, 
			action1, 
			NULL);

		m_sprite->runAction(CCRepeatForever::create(action3));

		CCSize size = CCDirector::sharedDirector()->getVisibleSize();
		CCPoint position = ccp(size.width/2 , size.height/2);
		m_sprite->setPosition(position);
		addChild(m_sprite, 51);

		setTouchEnabled(true);


		bRet = true;
	}while(0);

	return bRet;
}

void Shield::drawShieldRegion()
{
	glLineWidth( 5.0f );
	ccDrawColor4B(255,0,0,255);
	ccDrawCircle(m_sprite->getPosition(), m_radius, 0, 100, false);
}

void Shield::draw()
{
	drawShieldRegion();
}

void Shield::update(float delta)
{

}

void Shield::collideDetect()
{

}

void Shield::ccTouchesBegan(CCSet *pTouches, CCEvent *pEvent)
{
	if(1 == pTouches->count())
	{
		CCTouch	*touch = dynamic_cast<CCTouch*>(pTouches->anyObject());
		CCPoint position = touch->getLocationInView();
		position = CCDirector::sharedDirector()->convertToUI(position);

		if( m_sprite->boundingBox().containsPoint(position) )
		{
			m_touched = true;
			m_oldtouchpoint = position;
		}
	}
}

void Shield::ccTouchesMoved(CCSet *pTouches, CCEvent *pEvent)
{
	if(m_touched && 1==pTouches->count())
	{
		CCTouch	*touch = dynamic_cast<CCTouch*>(pTouches->anyObject());
		CCPoint position = touch->getLocationInView();
		position = CCDirector::sharedDirector()->convertToUI(position);

		CCPoint delta = ccp(position.x-m_oldtouchpoint.x, position.y-m_oldtouchpoint.y);
		CCPoint current = m_sprite->getPosition();
		m_sprite->setPosition(ccp(current.x+delta.x, current.y+delta.y));

		m_oldtouchpoint = position;
		CCDictionary *dict = CCDictionary::create();
		dict->setObject(CCFloat::create(m_radius), 0);
		dict->setObject(CCFloat::create(m_sprite->getPositionX()), 1);
		dict->setObject(CCFloat::create(m_sprite->getPositionY()), 2);

		NOTIFY->postNotification("ShieldPositonChange", dict);
	}
}

void Shield::ccTouchesEnded(CCSet *pTouches, CCEvent *pEvent)
{
	m_touched = false;
}

void Shield::getCenterAndRadius(float &r, float &x, float &y)
{
	r = m_radius;
	x = m_sprite->getPositionX();
	y = m_sprite->getPositionY();
}