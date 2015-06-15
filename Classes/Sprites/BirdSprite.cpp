//
//  BirdSprite.cpp
//  fly_and_spin
//
//  Created by bin on 15/6/10.
//
//

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
            path = "bird/bird_A.png";
            tag = 100;
            break;
        case 2:
            path = "bird/bird_B.png";
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
    body->setCollisionBitmask(0xff);
    body->setContactTestBitmask(0xff);
    body->getShape(0)->setRestitution(1.0f);
    body->getShape(0)->setDensity(1.0f);
    
    this->setPhysicsBody(body);
    blink_times = 0;
    old_direction = 1;
    return true;
}


void BirdSprite::becomeSuperBird(){
    this->stopAllActions();
    this->getPhysicsBody()->setCategoryBitmask(0);
    this->getPhysicsBody()->setContactTestBitmask(0);
    this->spin(1, spin_center);
}

void BirdSprite::becomeNormalBird(){
    this->stopAllActions();
    this->schedule(schedule_selector(BirdSprite::blink), 0.25f);
}



void BirdSprite::becomeElectricShock(){
    auto animation = Animation::create();
    animation->addSpriteFrameWithFile("bird/bird_black.png");
    animation->addSpriteFrameWithFile("bird/bird_black_2.png");
    animation->setDelayPerUnit(0.2f / 4.0f);
    animation->setRestoreOriginalFrame(true);
    auto shock_action = Animate::create(animation);
    auto go_down_action = Spawn::create(RotateTo::create(0.3, 180), MoveTo::create(1.0f, Vec2(this->getPosition().x, 0)), NULL);
    auto action = Sequence::create(Repeat::create(shock_action, 5), CallFunc::create([&](){this->setTexture("bird_black_3.png");}), go_down_action, CallFunc::create([&](){ NotificationCenter::getInstance()->postNotification("gameover");}), NULL);
    this->runAction(action); 

}

void BirdSprite::becomeFlying(){
    Vect force=Vect(0, -5000000.0f);
    getPhysicsBody()->setAngularVelocity(200);
    auto action = Sequence::create(DelayTime::create(1.0f), CallFunc::create([&](){ NotificationCenter::getInstance()->postNotification("gameover");}), NULL);
    this->runAction(action);
}


// 取代Action的Blink，Blink过程中小鸟会因玩家单击产生spin动作，由于两者的异步性，无法通过spwan组合起来，故重新以非Action的方式实现blink
void BirdSprite::blink(float dt){
    this->setVisible(blink_times % 2);
    blink_times++;
    if(blink_times == 8){
        this->setVisible(true);
        this->unscheduleAllCallbacks();
        blink_times = 0;
        this->getPhysicsBody()->setCategoryBitmask(0xff);
        this->getPhysicsBody()->setContactTestBitmask(0xff);
    }
}


void BirdSprite::spin(int direction, Vec2 center){
    spin_center = center;
    if(direction != old_direction){
        this->runAction(RotateBy::create(0.1, 180));
        this->runAction(RotateBy::create(0.1, 180));
        old_direction = direction;
    }
    this->runAction(CCRepeatForever::create(CircleAction::create(2, center, RADIUS, 360, direction)));
}