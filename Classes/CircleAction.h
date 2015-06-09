//
//  CircleAction.h
//  fly_and_spin
//
//  Created by bin on 15/6/8.
//
//

#ifndef __fly_and_spin__CircleAction__
#define __fly_and_spin__CircleAction__

#include <stdio.h>
#include "cocos2d.h"
USING_NS_CC;

class CircleAction:public ActionInterval{
public:
    static CircleAction *create(float t, Point center, float radius, float angle, int clockwise);
    bool init(float t, Point center, float radius, float angle, int clockwise);
    virtual void update(float time);
    virtual void startWithTarget(Node *target);

protected:
    Point m_center;
    float m_radius;
    float m_unit;
    float m_unit_angle;

    float m_time;
    float m_radian;
    float m_beginRadian;
    int m_dirction;
};
#endif /* defined(__fly_and_spin__CircleAction__) */
