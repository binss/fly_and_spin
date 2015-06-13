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
//    Layer *create();
    CREATE_FUNC(GameSceneTouchLayer);
    virtual bool init();
    bool onTouchBegan(cocos2d::Touch *touch, cocos2d::Event* event);
    void onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* event);
    void createBarrier(float dt);
    void update(float dt);
    void garbageCollection(Ref *object);
    bool onContactBegin(PhysicsContact& contact);
    Vector<Sprite *> barrier_vector;
    int direction;
    int score;
    void addBatteryPower(BirdSprite *bird);

    MotionStreak* streak_A;
    MotionStreak* streak_B;
    
    BatterySprite *battery;
    BirdSprite * bird_A;
    BirdSprite * bird_B;
    void birdDead(int type, BirdSprite * bird);
    void enterSuperMode();
    void quitSuperMode(float dt);
    
    int score_unit;
    int barrier_speed;
    
    Sprite *background;
    Sprite *background_copy;
//    virtual void ccTouchesMoved(CCSet *pTouches, CCEvent *pEvent);
//    virtual void ccTouchesEnded(CCSet *pTouches, CCEvent *pEvent);
};
#endif /* defined(__fly_and_spin__GameSceneTouchLayer__) */
