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
    this->stopAllActions();
    this->getPhysicsBody()->setCategoryBitmask(0);
    this->getPhysicsBody()->setContactTestBitmask(0);
    this->spin(1);
}

void BirdSprite::becomeNormalBird(){
    this->stopAllActions();
    auto setBitmask = [&](){
        CCLOG("normalnormalnormalnormalnormalnormalnormalnormalnormalnormalnormalnormalnormalnormalnormalnormalnormal");
        this->setVisible(true);
        this->getPhysicsBody()->setCategoryBitmask(0xff);
        this->getPhysicsBody()->setContactTestBitmask(0xff);
    };
    auto action = Sequence::create(Blink::create(2.0f, 4), DelayTime::create(0.5f), CallFunc::create(setBitmask), NULL);
    this->runAction(action);
}

void BirdSprite::becomeElectricShock(){
    auto animation = Animation::create();
    animation->addSpriteFrameWithFile("bird_black.png");
    animation->addSpriteFrameWithFile("bird_black_2.png");
    animation->setDelayPerUnit(0.2f / 4.0f);
    animation->setRestoreOriginalFrame(true);
    auto shock_action = Animate::create(animation);
    auto go_down_action = Spawn::create(RotateTo::create(0.3, 180), MoveTo::create(1.0f, Vec2(this->getPosition().x, 0)), NULL);
    auto action = Sequence::create(Repeat::create(shock_action, 5), CallFunc::create([&](){this->setTexture("bird_black_3.png");}), go_down_action, CallFunc::create([&](){ NotificationCenter::getInstance()->postNotification("gameover");}), NULL);
    this->runAction(action);

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