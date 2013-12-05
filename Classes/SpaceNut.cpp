#include "SpaceNut.h"
#include <cmath>

const double pi = cos(-1.0);

SpaceNut::SpaceNut()
{
	m_xspeed = 50.0;
	m_yspeed = -50.0;
	m_state = en_Floating;
	m_rotateangle = 0.0;
}

SpaceNut::~SpaceNut()
{
}

bool SpaceNut::init()
{
	bool bRet = false;

	char name[64], picture[64];
	int numFrames = 16;
	strcpy(name, "WallNut");

	sprintf(picture, "%s%03d.png", name, 1);

	m_sprite = CCSprite::create("PvZelements/Wallnut_body.png");
//	m_sprite = CCSprite::createWithSpriteFrameName(picture);

	CCSize size = CCDirector::sharedDirector()->getVisibleSize();
	m_sprite->setPosition(ccp(size.width/2, size.height/2));
	
	CCArray* animFrames = CCArray::createWithCapacity(numFrames);
	for(int i=1; i<=numFrames/*magic number*/; ++i)
	{
		sprintf(picture, "%s%03d.png", name, i);
		CCSpriteFrame* frame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(picture);
		animFrames->addObject(frame);
	}
	CCAnimation* animation = CCAnimation::createWithSpriteFrames(animFrames, 0.1f);
	CCAnimate* animate = CCAnimate::create(animation);
//	m_sprite->runAction(CCRepeatForever::create(animate));

//	m_sprite->setScale(1.5f);

	addChild(m_sprite, 20);
	
	scheduleUpdate();

	NOTIFY->addObserver(this,
		callfuncO_selector(SpaceNut::recvShieldPosition),
		"ShieldPositonChange",
		NULL
		);
	bRet = true;

	return bRet;
}

void SpaceNut::changeXSpeedBy(float delta)
{
	switch(m_state)
	{
	case en_Floating:
		m_xspeed += delta;
		break;
	case en_InShield:
		m_xspeed = delta*10;
		break;
	default:
		m_xspeed += delta;
		break;
	}
}

void SpaceNut::changeYSpeedBy(float delta)
{
	switch(m_state)
	{
	case en_Floating:
		m_yspeed += delta;
		break;
	case en_InShield:
		m_yspeed = delta*10;
		break;
	default:
		m_yspeed += delta;
		break;
	}
}

void SpaceNut::update(float delta)
{
	CCLOG("SpaceNut::update(float delta)");
	
	float dx = m_shieldpos[1] - m_sprite->getPositionX();
	float dy = m_shieldpos[2] - m_sprite->getPositionY();
	if(m_shieldpos[0] * m_shieldpos[0] > dx*dx + dy*dy)
	{
		m_state = en_InShield;
	}
	else
	{
		m_state = en_Floating;
	}

	switch(m_state)
	{
	case en_Floating:
		moveInSpace(delta);
		break;
	case en_InShield:
		moveInShield(delta);
		break;
	default:
		moveInSpace(delta);
		break;
	}



}

void SpaceNut::moveInShield(float delta)
{
	CCPoint current = m_sprite->getPosition();

	float dx = delta*m_xspeed;
	float dy = delta*m_yspeed;
	m_sprite->setPositionX(current.x + delta*m_xspeed);
	m_sprite->setPositionY(current.y + delta*m_yspeed);

	CCSize spritesize = m_sprite->getContentSize();
	float r2 = spritesize.height*spritesize.height + spritesize.width*spritesize.width;
	float angle = sqrt((dx*dx+dy*dy)/r2)/pi*180.0;
	
	m_rotateangle += dx>0 ? angle : -angle;

	m_sprite->setRotation(m_rotateangle);

	// detect if the nut collide with the visible region
	CCSize size = CCDirector::sharedDirector()->getVisibleSize();
	CCRect rect = myBoundingBox();
	float maxX = rect.getMaxX();
	float minX = rect.getMinX();
	float maxY = rect.getMaxY();
	float minY = rect.getMinY();

	if(maxX>size.width || minX<0)
	{
		m_sprite->setPosition(current);
	}

	if(maxY>size.height || minY<0)
	{
		m_sprite->setPosition(current);
	}


	m_xspeed = 0.0f;
	m_yspeed = 0.0f;
}

void SpaceNut::moveInSpace(float delta)
{
	CCPoint current = m_sprite->getPosition();

	m_sprite->setPositionX(current.x + delta*m_xspeed);
	m_sprite->setPositionY(current.y + delta*m_yspeed);

	// detect if the nut collide with the visible region
	CCSize size = CCDirector::sharedDirector()->getVisibleSize();
	CCRect rect = myBoundingBox();
	float maxX = rect.getMaxX();
	float minX = rect.getMinX();
	float maxY = rect.getMaxY();
	float minY = rect.getMinY();

	if(maxX>size.width || minX<0)
	{
		m_xspeed = -m_xspeed;
		m_sprite->setPosition(current);
	}

	if(maxY>size.height || minY<0)
	{
		m_yspeed = -m_yspeed;
		m_sprite->setPosition(current);
	}
}

CCRect SpaceNut::myBoundingBox()
{
	return m_sprite->boundingBox();
}

void SpaceNut::recvShieldPosition(CCObject *pData)
{
	CCLOG("I got the message");
	CCDictionary *dict = dynamic_cast<CCDictionary*>(pData);

	m_shieldpos[0] = dynamic_cast<CCFloat*>(dict->objectForKey(0))->getValue();
	m_shieldpos[1] = dynamic_cast<CCFloat*>(dict->objectForKey(1))->getValue();
	m_shieldpos[2] = dynamic_cast<CCFloat*>(dict->objectForKey(2))->getValue();
}