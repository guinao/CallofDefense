/*
    �ļ�����    TollgateScene.h
    �衡����    �ؿ�����
    �����ˣ�    ��ľͷ_�ӵ��� (���ͣ�http://www.benmutou.com)

    �������ڣ�   2013.03.24
*/
#ifndef _TollgateScene_H_
#define _TollgateScene_H_

#include "cocos2d.h"
USING_NS_CC;

#define TAG_MAP_LAYER 1	// �ؿ���ͼͼ��TAG
#define TAG_DATA_LAYER 2	// �ؿ�����ͼ��TAG

class TollgateMapLayer;
class TollgateScene : public CCLayer {
public:
	static CCScene* scene();
	virtual bool init();

	virtual void onExit();

	CREATE_FUNC(TollgateScene);
};

#endif