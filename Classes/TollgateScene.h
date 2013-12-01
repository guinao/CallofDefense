/*
    文件名：    TollgateScene.h
    描　述：    关卡场景
    创建人：    笨木头_钟迪龙 (博客：http://www.benmutou.com)

    创建日期：   2013.03.24
*/
#ifndef _TollgateScene_H_
#define _TollgateScene_H_

#include "cocos2d.h"
USING_NS_CC;

#define TAG_MAP_LAYER 1	// 关卡地图图层TAG
#define TAG_DATA_LAYER 2	// 关卡数据图层TAG

class TollgateMapLayer;
class TollgateScene : public CCLayer {
public:
	static CCScene* scene();
	virtual bool init();

	virtual void onExit();

	CREATE_FUNC(TollgateScene);
};

#endif