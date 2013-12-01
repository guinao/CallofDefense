#include "SunShine.h"

//////////////////////////////////////////////////////////////////////////

SunShine::SunShine()
{
}

//////////////////////////////////////////////////////////////////////////

SunShine::~SunShine()
{
}

//////////////////////////////////////////////////////////////////////////

SunShine* SunShine::createSunShine(int value)
{
	SunShine *s = new SunShine();

	s->m_value = value;

	bool bRet = false;

	do{
		char name[64], picture[64];
		int numFrames = 22;

		strcpy(name, "Sun");
		sprintf(picture, "%s%03d.png", name, 1);

		CCSprite* sprite = CCSprite::createWithSpriteFrameName(picture);
		CCSize size = CCDirector::sharedDirector()->getVisibleSize();
		srand(time(NULL));
		CCPoint startPos = ccp(rand()%(static_cast<int>(size.width)), size.height);
		CCPoint endPos = ccp(rand()%(static_cast<int>(size.width)), 0);
		sprite->setPosition(startPos);

		s->addChild(sprite);

		CCArray* animFrames = CCArray::createWithCapacity(numFrames);
		for(int i=1; i<=numFrames/*magic number*/; ++i)
		{
			sprintf(picture, "%s%03d.png", name, i);
			CCSpriteFrame* frame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(picture);
			animFrames->addObject(frame);
		}
		CCAnimation* animation = CCAnimation::createWithSpriteFrames(animFrames, 10.0f);
		animation->setLoops(-1);
		CCAnimate* animate = CCAnimate::create(animation);
		CCMoveTo* moveto = CCMoveTo::create(10.0f, endPos);
		
		CCSequence* sequence = CCSequence::create(
			CCSpawn::createWithTwoActions(animate, moveto), 
			CCFadeTo::create(10.0f, 0),
			NULL
		);

		sprite->runAction(sequence);

		//vc.push_back(sprite);

		bRet = true;
	}while(0);

	if(bRet)
	{
		s->autorelease();
		return s;
	}
	else
	{
		return NULL;
	}
}

//////////////////////////////////////////////////////////////////////////

void SunShine::sunDisappear()
{
}