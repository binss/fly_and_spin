//
//  BatterySprite.cpp
//  fly_and_spin
//
//  Created by bin on 15/6/11.
//
//

#include "BatterySprite.h"

BatterySprite * BatterySprite::create(){
    BatterySprite *sprite = new BatterySprite();
    if (sprite && sprite->init())
    {
        sprite->autorelease();
        return sprite;
    }
    CC_SAFE_DELETE(sprite);
    return nullptr;
}


bool BatterySprite::init(){
    condition = 0;
    Sprite::initWithFile("battery/battery_0.png");
    Size visibleSize = Director::getInstance()->getVisibleSize();
    this->setScale(0.6f);
    this->setPosition(Vec2(visibleSize.width - getContentSize().width / 2, visibleSize.height - getContentSize().height / 2));
    this->setTag(200);
    return true;
}

int BatterySprite::nextCondition(){
    condition ++;
    if(condition > 3)
        condition = 0;
    char path[50];
    sprintf(path,"battery/battery_%d.png", condition);
    this->setTexture(path);
    
    return condition;
}

int BatterySprite::getCondition(){
    return condition;
}