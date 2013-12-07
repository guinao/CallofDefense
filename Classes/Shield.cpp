#include "Shield.h"
#include "BootScene.h"

Shield* Shield::m_shield = NULL;

Shield::Shield()
{
	m_touched = false;
	m_radius = 200.0f;
	m_state = en_hpHigh;
	m_hp = kHpFull;
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
		texture[0] = CCTextureCache::sharedTextureCache()->addImage("PvZelements/Tallnut_body.png");
		texture[1] = CCTextureCache::sharedTextureCache()->addImage("PvZelements/Tallnut_cracked1.png");
		texture[2] = CCTextureCache::sharedTextureCache()->addImage("PvZelements/Tallnut_cracked2.png");

		m_sprite = CCSprite::createWithTexture(texture[0]);
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

void Shield::onExit()
{
	setTouchEnabled(false);
}

void Shield::collideDetect()
{

}

void Shield::onHurt(float losehp)
{
	m_hp -= losehp;
	if(m_hp>kHpLow && m_hp<=kHpMid && m_state!=en_hpMid)
	{
		m_state = en_hpMid;
		m_sprite->setTexture(texture[1]);
	}
	else if(m_hp<=kHpLow && m_hp>0 && m_state!=en_hpLow)
	{
		m_state = en_hpLow;
		m_sprite->setTexture(texture[2]);
	}
	else if(m_hp <= 0)
	{
		NOTIFY->postNotification(kLoseMessage, NULL);
//		CCDirector::sharedDirector()->replaceScene(BootScene::scene());
	}
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

static void printRect(const CCRect rect)
{
	char msg[128];

	sprintf(msg, "minx %f, miny %f, maxx %f, maxy %f", 
		rect.getMinX(), rect.getMinY(), rect.getMaxX(), rect.getMaxY());
	CCLOG(msg);
}

void Shield::ccTouchesMoved(CCSet *pTouches, CCEvent *pEvent)
{
	CCLOG("Shield::ccTouchesMoved");

	if(m_touched && 1==pTouches->count())
	{
		CCTouch	*touch = dynamic_cast<CCTouch*>(pTouches->anyObject());
		CCPoint temppos = touch->getLocationInView();
		CCPoint position = CCDirector::sharedDirector()->convertToUI(temppos);

		CCPoint delta = ccp(position.x-m_oldtouchpoint.x, position.y-m_oldtouchpoint.y);

		float x = m_sprite->getPositionX() + delta.x;
		float y = m_sprite->getPositionY() + delta.y;
		CCSize size = CCDirector::sharedDirector()->getVisibleSize();
		if(x > size.width)
			x = size.width;
		if(x < 0.0f)
			x = 0.0f;
		if(y > size.height)
			y = size.height;
		if(y < 0.0f)
			y = 0.0f;

		m_sprite->setPosition(ccp(x, y));
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