#ifndef _PlantManager_H_
#define _PlantManager_H_

#include "cocos2d.h"
#include "cocos-ext.h"
#include "Plant.h"
#include "EnumPlantType.h"
#include <vector>
using namespace std;

/************************************************************************/
/* This class is used for manage actions of plants                      */
/************************************************************************/

class DemoScene;

class PlantManager : public CCLayer
{
friend class DemoScene;

public:
	PlantManager();
	~PlantManager();

	CREATE_FUNC(PlantManager);
	virtual bool init();
	virtual void onExit();
	virtual void update(float delta);

	void createPlants(const vector<PlantType> &v, const vector<CCPoint> &vp);
	void getPlantsPosition(vector<CCPoint>& vp);

private:
	CCArray* m_plants;
};

#endif
