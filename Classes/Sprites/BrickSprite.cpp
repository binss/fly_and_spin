//
//  BrickSprite.cpp
//  fly_and_spin
//
//  Created by bin on 15/6/10.
//
//

#include "BrickSprite.h"

int BrickSprite::speed = -250;

BrickSprite * BrickSprite::createWithType(int type){
    
    BrickSprite *sprite = new BrickSprite();
    if (sprite && sprite->initWithType(type))
    {
        sprite->autorelease();
        return sprite;
    }
    CC_SAFE_DELETE(sprite);
    return nullptr;
}


bool BrickSprite::initWithType(int type){
    Size visibleSize = Director::getInstance()->getVisibleSize();

    std::string path;
    int tag;
    switch (type) {
        case 1:
            path = "barrier_short.png";
            tag = 10;
            break;
        case 2:
            path = "barrier_short.png";
            tag = 11;
            break;
        case 3:
            path = "barrier_long.png";
            tag = 12;
            break;
        case 4:
            path = "barrier_long.png";
            tag = 12;
            break;
        default:
            break;
    }
    Sprite::initWithFile(path);
    this->setScale(0.8f);
    this->setTag(tag);
    
    int x;
    int width = this->getContentSize().width * 0.8f;
    switch (type) {
        case 1:
            x = CCRANDOM_0_1() * (visibleSize.width -  width) + width / 2;
            break;
        case 2:
            x = CCRANDOM_0_1() * (visibleSize.width -  width) + width / 2;
            break;
        case 3:
            x = width / 2;
            break;
        case 4:
            x = visibleSize.width - width / 2;
            break;
        default:
            break;
    }
    this->setPosition(Vec2(x, visibleSize.height));
    
    auto body = PhysicsBody::createBox(this->getContentSize() * 0.8f);
    body->setDynamic(true);
    body->setCategoryBitmask(0xff);
    body->setCollisionBitmask(0);
    body->setContactTestBitmask(0xff);
    body->setVelocity(Vec2(0, speed));
    this->setPhysicsBody(body);
    if(type == 2){
        this->runAction(CCRepeatForever::create(RotateBy::create(1.0, 180)));
    }
    return true;
}