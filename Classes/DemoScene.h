#ifndef _DemoScene_H_
#define _DemoScene_H_

#include "cocos2d.h"
#include "cocos-ext.h"
#include "PlantManager.h"
#include "ZombieManager.h"
#include "EnumPlantType.h"
#include "TouchLayer.h"
#include "SunShine.h"
#include "Plant.h"


using namespace cocos2d::extension;
USING_NS_CC;

class DemoScene : public CCLayer {
public:
	static CCScene* scene();
	CREATE_FUNC(DemoScene);
	virtual bool init();
	virtual void onExit();
	virtual void didAccelerate(CCAcceleration* pAccelerationValue);
	virtual void update(float delta);
	Plant* findPlantInRange(CCRect rect);

//	virtual void ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
//	virtual void ccTouchesMoved(CCSet *pTouches, CCEvent *pEvent);
//	virtual void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);

private:
	void backToTollgateSelectScene(float dt);
	void labForCCSprites();
	void labForCCAction();
	void labForCCScale9Sprite();
	void labForCCAnimation();
	void labForPlantManager();
	void labForSunShine();
	bool labForZombieManager();
	void labForTouchLayer();
	void labForTexture();
	void getPlantsPosition();
	void getZombiesPosition();

	GameState checkGameState();

	CCLabelAtlas* m_label;

	// variables for accelerate
	int m_shakeCnt;
	int m_swingCnt;

	// Plants and Zombies
	PlantManager* m_plantmanager;
	ZombieManager* m_zombiemanager;
	vector<CCPoint> m_plantsposition;
	vector<CCRect> m_zombiesposition;
};

#endif