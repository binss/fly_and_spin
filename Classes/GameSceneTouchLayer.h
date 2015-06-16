//
//  GameSceneTouchLayer.h
//  fly_and_spin
//
//  Created by bin on 15/6/8.
//
//

#ifndef __fly_and_spin__GameSceneTouchLayer__
#define __fly_and_spin__GameSceneTouchLayer__

#include "cocos2d.h"
#include <stdio.h>
#include "BatterySprite.h"
#include "BirdSprite.h"

USING_NS_CC;

class GameScene;


class GameSceneTouchLayer : public Layer{
public:
    virtual bool init();
    CREATE_FUNC(GameSceneTouchLayer);
    bool onTouchBegan(cocos2d::Touch *touch, cocos2d::Event* event);
    void onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* event);
    bool onContactBegin(PhysicsContact& contact);

    void update(float dt);
    void createBarrier(float dt);
    void speedUp(float dt);

    void garbageCollection(Ref *object);
    void addBatteryPower(BirdSprite *bird);
    void birdDead(int type, BirdSprite * bird);
    void enterSuperMode();
    void quitSuperMode(float dt);
    int score;

private:
    Vector<Sprite *> barrier_vector;

    int score_unit;
    int speed;
    float create_barrier_interval;
    int direction;
    Vec2 spin_center;
    
    BatterySprite *battery;
    MotionStreak* streak_A;
    MotionStreak* streak_B;
    
    BirdSprite * bird_A;
    BirdSprite * bird_B;


};
#endif /* defined(__fly_and_spin__GameSceneTouchLayer__) */
