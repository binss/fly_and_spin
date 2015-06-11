//
//  BirdSprite.cpp
//  fly_and_spin
//
//  Created by bin on 15/6/10.
//
//
#define BIRD_A_TAG 100
#define BIRD_B_TAG 101
#define RADIUS 250

#include "BirdSprite.h"
#include "CircleAction.h"

BirdSprite * BirdSprite::createWithType(int type){
    
    BirdSprite *sprite = new BirdSprite();
    if (sprite && sprite->initWithType(type))
    {
        sprite->autorelease();
        return sprite;
    }
    CC_SAFE_DELETE(sprite);
    return nullptr;
}


bool BirdSprite::initWithType(int type){
    std::string path;
    int tag;
    switch (type) {
        case 1:
            path = "bird_A.png";
            tag = 100;
            break;
        case 2:
            path = "bird_B.png";
            tag = 101;
            break;
        default:
            break;
    }
    Sprite::initWithFile(path);
    
    this->setScale(0.3f);
    this->setTag(tag);
    auto body = PhysicsBody::createBox(this->getContentSize() * 0.3f);
    body->setDynamic(true);
    body->setCategoryBitmask(0xff);
    body->setCollisionBitmask(0);
    body->setContactTestBitmask(0xff);
    this->setPhysicsBody(body);
    
    old_direction = 1;
    return true;
}


void BirdSprite::becomeSuperBird(){
    
}

void BirdSprite::spin(int direction){
    Size visibleSize = Director::getInstance()->getVisibleSize();
    if(direction != old_direction){
        this->runAction(RotateBy::create(0.1, 180));
        this->runAction(RotateBy::create(0.1, 180));
        old_direction = direction;
    }
    this->runAction(CCRepeatForever::create(CircleAction::create(2, Point(visibleSize.width/2 , visibleSize.height/2 - RADIUS), RADIUS, 360, direction)));
}