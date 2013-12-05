#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "SimpleAudioEngine.h"
#include "touch_dispatcher\CCTouch.h"
#include "cocoa\CCSet.h"

class BootScene : public cocos2d::CCLayer
{
public:
	BootScene();
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  

    // there's no 'id' in cpp, so we recommand to return the exactly class pointer
    static cocos2d::CCScene* scene();
    
    // a selector callback
    void menuCloseCallback(CCObject* pSender);

    // implement the "static node()" method manually
    CREATE_FUNC(BootScene);
	void genBackground();
	void onEnter();
	virtual void ccTouchesBegan(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent);
	virtual void ccTouchesEnded(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent);
	cocos2d::CCSprite* spriteWithColor(cocos2d::ccColor4F bgColor, float textureWidth, float textureHeight);
	cocos2d::ccColor4F randomBrightColor();
	cocos2d::CCSprite * spriteWithColor1(cocos2d::ccColor4F c1, cocos2d::ccColor4F c2, float textureWidth, float textureHeight, int nStripes);
	void update(float dt);
	void eggAppear();
	cocos2d::CCSprite *_background;
	cocos2d::CCSprite *_starticon;
};

#endif  // __HELLOWORLD_SCENE_H__