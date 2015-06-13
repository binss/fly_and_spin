//
//  LightningSprite.cpp
//  fly_and_spin
//
//  Created by bin on 15/6/10.
//
//

#define LIGHTNING_A_TAG 20
#define LIGHTNING_B_TAG 21

#include "LightningSprite.h"

//int LightningSprite::speed = -250;

LightningSprite * LightningSprite::create(){
    LightningSprite *sprite = new LightningSprite();
    if (sprite && sprite->init())
    {
        sprite->autorelease();
        return sprite;
    }
    CC_SAFE_DELETE(sprite);
    return nullptr;
}


bool LightningSprite::init(){
    char type;
    int tag;
    if(CCRANDOM_0_1() <= 0.5){
        type = 'a';
        tag = LIGHTNING_A_TAG;
    }
    else{
        type = 'b';
        tag = LIGHTNING_B_TAG;
    }

    Sprite::initWithFile("lightning/lightning_a_1.png");
    auto animation = Animation::create();
    for( int i=1;i<5;i++)
    {
        char szName[100] = {0};
        sprintf(szName, "lightning/lightning_%c_%d.png", type, i);
        animation->addSpriteFrameWithFile(szName);
    }
    animation->setDelayPerUnit(0.2f / 4.0f);
    animation->setRestoreOriginalFrame(true);
    auto action = Animate::create(animation);
    this->runAction(RepeatForever::create(Sequence::create(action, action->reverse(), NULL)));
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    int x = CCRANDOM_0_1() * (visibleSize.width -  this->getContentSize().width/2) + this->getContentSize().width / 2;
    this->setPosition(Vec2(x, visibleSize.height));
    this->setTag(tag);

    auto body = PhysicsBody::createBox(this->getContentSize());
    body->setDynamic(false);
    body->setCategoryBitmask(0xff);
    body->setCollisionBitmask(0);
    body->setContactTestBitmask(0xff);
//    body->setVelocity(Vec2(0, speed));
    this->setPhysicsBody(body);
    return true;
}