/*
    �ļ�����    TollgateSelectScene.h
    �衡����    �ؿ�ѡ�񳡾�
    �����ˣ�    ��ľͷ_�ӵ��� (���ͣ�http://www.benmutou.com)

    �������ڣ�   2013.03.19
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