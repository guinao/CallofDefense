#include "TouchLayer.h"

//////////////////////////////////////////////////////////////////////////

CCScene* TouchLayer::scene()
{
	CCScene* scene = NULL;

	do{
		scene = CCScene::create();
		CC_BREAK_IF(! scene);

		TouchLayer* layer = TouchLayer::create();
		CC_BREAK_IF(! layer);

		scene->addChild(layer);
	}while (0);

	return scene;
}

//////////////////////////////////////////////////////////////////////////

bool TouchLayer::init()
{
	bool bRet = false;

	do{
		CC_BREAK_IF(! CCLayer::init());

		createWidgets();
		createSunshines();

		bRet = true;
	}while(0);

	return bRet;	
}

//////////////////////////////////////////////////////////////////////////

bool TouchLayer::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent)
{
	return true;
}

//////////////////////////////////////////////////////////////////////////

void TouchLayer::ccTouchMoved(CCTouch *pTouches, CCEvent *pEvent)
{

}

//////////////////////////////////////////////////////////////////////////

void TouchLayer::ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent)
{

}

//////////////////////////////////////////////////////////////////////////

void TouchLayer::update(float delta)
{

}

//////////////////////////////////////////////////////////////////////////

void TouchLayer::createWidgets()
{
	//////////////////////////////////////////////////////////////////////////
	// create background
	CCSprite *background = CCSprite::createWithSpriteFrameName("background1.png");
	CCSize newsize = CCDirector::sharedDirector()->getVisibleSize();
	CCSize oldsize = background->getContentSize();
	background->setAnchorPoint(ccp(0, 0));
	background->setPosition(ccp(0.0f, 0.0f));
	background->setScaleX(newsize.width / oldsize.width);
	background->setScaleY(newsize.height / oldsize.height);
	addChild(background, 1);

	//////////////////////////////////////////////////////////////////////////
	// create plant selector
}

//////////////////////////////////////////////////////////////////////////

void TouchLayer::createSunshines()
{
	SunShine* sun = SunShine::createSunShine(50);
	addChild(sun, 2);
}
