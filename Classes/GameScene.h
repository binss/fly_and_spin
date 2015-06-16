#ifndef __GAME_SCENE_H__
#define __GAME_SCENE_H__

#include "cocos2d.h"
#include "GameSceneTouchLayer.h"
#include "GameMenuLayer.h"
#include "GameBackgroundLayer.h"
#include "GamePauseLayer.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;


class GameScene : public cocos2d::Scene
{
public:    
    static GameScene* shareGameScene();
    GameSceneTouchLayer *gameLayer;
    GameMenuLayer *menuLayer;
    GameBackgroundLayer *backgroundLayer;
    GamePauseLayer *pauseLayer;
    void initLayer();
    void reset();
    void gameOver(Ref* sender);
    void pauseGame();
};
#endif // __GAME_SCENE_H__
