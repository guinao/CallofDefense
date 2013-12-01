/*
    文件名：    TollgateSelectScene.h
    描　述：    关卡选择场景
    创建人：    笨木头_钟迪龙 (博客：http://www.benmutou.com)

    创建日期：   2013.03.19
*/
#ifndef _TollgateSelectScene_H_
#define _TollgateSelectScene_H_

#include "cocos2d.h"
#include "cocos-ext.h"
USING_NS_CC_EXT;
USING_NS_CC;

class TollgateSelectScene : public CCLayer {
public:
    static CCScene* scene();
    virtual bool init();

    CREATE_FUNC(TollgateSelectScene);

private:
	CCLabelTTF* createLevelLab(const char* sLvl);

    void level_1(CCObject* pSender);
    void level_2(CCObject* pSender);
//     void level_3(CCObject* pSender);
//     void level_4(CCObject* pSender);
//     void level_5(CCObject* pSender);
};

#endif