#ifndef _SunShine_H_
#define _SunShine_H_

#include "cocos2d.h"
#include <vector>

using namespace std;
USING_NS_CC;

class SunShine : public CCNode
{
public:
	SunShine();
	~SunShine();

	static SunShine* createSunShine(int value);

private:
	void sunDisappear();

	vector<CCSprite*> vc;

	int m_value;
	bool m_over;
};

#endif