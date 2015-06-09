//
//  CircleAction.cpp
//  fly_and_spin
//
//  Created by bin on 15/6/8.
//
//

#include "CircleAction.h"

CircleAction *CircleAction::create(float t, Point center, float radius, float angle, int dirction){
    CircleAction *action = new CircleAction();
    action->init(t, center, radius, angle, dirction);
    action->autorelease();
    return action;
}

bool CircleAction::init(float t, Point center, float radius, float angle, int dirction){
    if(ActionInterval::initWithDuration(t)){
        m_center = center;
        m_radius = radius;
        m_radian = angle /360 * 2 * M_PI;
        m_unit = Director::getInstance()->getAnimationInterval() * m_radian / t;
        m_time = 1;
        m_dirction = dirction;
//        m_beginRadian = M_PI + atan2f(m_center.y,m_center.x);

//        m_unit = 2.0 * M_PI / (t/Director::getInstance()->getAnimationInterval());
//        CCLOG("%f", m_unit);
//        m_time = 1;
//        m_radian = 2.0 * M_PI * init_angle / 360;
        m_unit_angle = 360 / (t/Director::getInstance()->getAnimationInterval());
        return true;
    }
    return false;
}

void CircleAction::startWithTarget(Node * target){
    ActionInterval::startWithTarget(target);
    if(m_time == 1 ){
        float x = target->getPosition().x - m_center.x;
        float y = target->getPosition().y - m_center.y;
        m_beginRadian = atan2f(x, y);
//        CCLOG("%f", m_beginRadian);
    }
}


void CircleAction::update(float time){
    auto radian = m_dirction * m_unit * m_time + m_beginRadian;
    float x = m_radius * sin(radian);
    float y = m_radius * cos(radian);
    Point newPos = Point(m_center.x + x, m_center.y + y);
    _target->setPosition(newPos);
    _target->setRotation(_target->getRotation() + m_dirction * m_unit_angle);
    m_time += 1;
//    CCLOG("%f", radian);
}

