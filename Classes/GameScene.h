#ifndef __GAME_SCENE_H__
#define __GAME_SCENE_H__

#include "cocos2d.h"
#include "GameSceneTouchLayer.h"
#include "GameMenuLayer.h"

USING_NS_CC;


class GameScene : public cocos2d::Scene
{
public:    
    static GameScene* shareGameScene();
    GameSceneTouchLayer *gameLayer;
    GameMenuLayer *menuLayer;
    
    void initLayer();
    void reset();
};
#endif // __GAME_SCENE_H__
