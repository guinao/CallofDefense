#ifndef _TouchLayer_H_
#define _TouchLayer_H_

#include "cocos2d.h"
#include "cocos-ext.h"
#include "PlantManager.h"
#include "EnumPlantType.h"
#include "SunShine.h"

using namespace cocos2d::extension;
USING_NS_CC;

/************************************************************************/
/*  This layer is used for manipulating touch events such as collecting */
/*  sunshines, put a plant onto a slot, and the update is isolated from */
/*  the game scene layer												*/
/************************************************************************/

class TouchLayer : public CCLayer {
public:
	static CCScene* scene();
	virtual bool init();
	CREATE_FUNC(TouchLayer);
	virtual void update(float delta);
	virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
	virtual void ccTouchMoved(CCTouch *pTouches, CCEvent *pEvent);
	virtual void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);
//	virtual void ccTouchCancelled(CCTouch *pTouch, CCEvent *pEvent);

private:
	void createWidgets();
	void createSunshines();

};

#endif