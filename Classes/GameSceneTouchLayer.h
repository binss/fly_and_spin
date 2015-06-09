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
USING_NS_CC;

class GameSceneTouchLayer : public Layer{
public:
//    Layer *create();
    CREATE_FUNC(GameSceneTouchLayer);
    virtual bool init();
    virtual void onEnter();
    bool onTouchBegan(cocos2d::Touch *touch, cocos2d::Event* event);
    void onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* event);
    void createBarrier(float dt);
    void update(float dt);
    void garbageCollection(Ref *object);
    bool onContactBegin(PhysicsContact& contact);
    Vector<Sprite *> barrier_vector;
    int old_direction;
    int direction;
    void addBoxBodyForSprite(Sprite* sprite, float scale, bool dynamic);
    void gameOver();

//    virtual void ccTouchesMoved(CCSet *pTouches, CCEvent *pEvent);
//    virtual void ccTouchesEnded(CCSet *pTouches, CCEvent *pEvent);
};
#endif /* defined(__fly_and_spin__GameSceneTouchLayer__) */
