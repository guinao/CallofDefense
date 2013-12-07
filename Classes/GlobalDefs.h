#ifndef _GlobalDefs_H_
#define _GlobalDefs_H_

#define NOTIFY cocos2d::CCNotificationCenter::sharedNotificationCenter()

const int hasAI = 800;
const int AIupperbound = 100;
const float kNutWeight = 100.0f;
const float kZombieWeight = 10.0f;
const float kHpFull = 1000.0f;
const float kHpLow = 200.0f;
const float kHpMid = 500.0f;
const char kLoseMessage[] = "Defeated";
const char kWinMessage[] = "Stage Clear";
const char kScoreChangedMessage[] = "Add Score";
const char kShieldPostionChanged[] = "Shield position changed";

#endif