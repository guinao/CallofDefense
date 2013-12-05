#ifndef _Shield_H_
#define _Shield_H_

#include "cocos2d.h"
#include "GlobalDefs.h"
#include <vector>
#include <utility>

using namespace std;
USING_NS_CC;

class Shield : public CCLayer
{
public:
	Shield();
	~Shield();

	static Shield* getShieldSingleton();

	virtual bool init();

	virtual void update(float delta);
	virtual void draw();

	void collideDetect();

	virtual void ccTouchesBegan(CCSet *pTouches, CCEvent *pEvent);
	virtual void ccTouchesMoved(CCSet *pTouches, CCEvent *pEvent);
	virtual void ccTouchesEnded(CCSet *pTouches, CCEvent *pEvent);
	
	void getCenterAndRadius(float &r, float &x, float &y);
private:
	CREATE_FUNC(Shield);
	void drawShieldRegion();

	CCSprite* m_sprite;
	pair<float, float> m_speed;
//	CCPoint m_position;
	CCPoint m_oldtouchpoint;
	float m_radius;
	bool m_touched;

	static Shield *m_shield;
};

#endif