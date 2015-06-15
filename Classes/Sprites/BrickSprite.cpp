//
//  BrickSprite.cpp
//  fly_and_spin
//
//  Created by bin on 15/6/10.
//
//

#include "BrickSprite.h"


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
            path = "brick/brick_short.png";
            tag = 10;
            break;
        case 2:
            path = "brick/brick_short.png";
            tag = 11;
            break;
        case 3:
            path = "brick/brick_long.png";
            tag = 12;
            break;
        case 4:
            path = "brick/brick_long.png";
            tag = 13;
            break;
        case 5:
            path = "brick/brick_square.png";
            tag = 14;
            break;
        default:
            break;
    }
    Sprite::initWithFile(path);
    this->setScale(0.8f);
    this->setTag(tag);
    
    int x;
    int width = getContentSize().width * 0.8f;
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
        case 5:
            x = CCRANDOM_0_1() * (visibleSize.width -  width) + width / 2;
        default:
            break;
    }
    this->setPosition(Vec2(x, visibleSize.height));
    
    auto body = PhysicsBody::createBox(this->getContentSize() * 0.8f);
    body->setDynamic(false);
    body->setCategoryBitmask(0xff);
    body->setCollisionBitmask(0xff);
    body->setContactTestBitmask(0xff);
    body->getShape(0)->setRestitution(1.0f);
    body->getShape(0)->setDensity(1.0f);
//    body->setVelocity(Vec2(0, speed));
    
    this->setPhysicsBody(body);
    if(type == 2){
        this->runAction(CCRepeatForever::create(RotateBy::create(1.0, 180)));
    }
    return true;
}