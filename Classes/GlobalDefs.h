#ifndef _GlobalDefs_H_
#define _GlobalDefs_H_

#define NOTIFY cocos2d::CCNotificationCenter::sharedNotificationCenter()

const int hasAI = 8000;
const int AIupperbound = 100;
const float kNutWeight = 100.0f;
const float kZombieWeight = 1000.0f;
const float kZombieSpeedFloating = 50.0f;
const float kZombieSpeedInShield = 10.0f;
const float kZombieSpeedFlyAway = 500.0f;
const float kHpFull = 1000.0f;
const float kHpLow = 200.0f;
const float kHpMid = 500.0f;
const char kLoseMessage[] = "Defeated";
const char kWinMessage[] = "Stage Clear";
const char kScoreChangedMessage[] = "Add Score";
const char kShieldPostionChangedMessage[] = "Shield position changed";
const char kNutPostionChangedMessage[] = "Nut position changed";
const char kZombiesOnBoardMessage[] = "Waring! Zombies on board!";
const char kZombieLeaveMessage[] = "Zombie on board decrease by 1";
const char kZombiesApproachingMessage[] = "A big wave of Zombies is approaching";
const char kGravityShockMessage[] = "Gravity shock";

#endif