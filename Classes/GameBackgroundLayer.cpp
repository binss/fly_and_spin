//
//  GameBackgroundLayer.cpp
//  fly_and_spin
//
//  Created by bin on 15/6/13.
//
//

#include "GameBackgroundLayer.h"

bool GameBackgroundLayer::init()
{
    if(!Layer::init())
    {
        return false;
    }
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    background = Sprite::create("building/building_A_1.png");
    background->setTag(700);
    background->setScaleX(visibleSize.width / background->getContentSize().width);
    background->setAnchorPoint(Vec2(0,1));
    background->setPosition(Vec2(0,background->getContentSize().height));
    addChild(background, 0);
    
    background_copy = Sprite::create("building/building_A_2.png");
    background_copy->setScaleX(visibleSize.width / background->getContentSize().width);
    background_copy->setAnchorPoint(Vec2(0,1));
    background_copy->setPosition(Vec2(0, 2*background->getContentSize().height));
    addChild(background_copy, 0);
    
    
    return true;
}

void GameBackgroundLayer::updateBackground(int score, int speed){
    
    background->setPositionY(background->getPosition().y  - speed);
    background_copy->setPositionY(background_copy->getPosition().y  - speed);
    
    if(background ->getPosition().y < 0){
        if(background->getTag() == 700){
            background->setTag(701);
            background->setTexture("building/building_A_2.png");
        }
        if(score >= 1000){
            if(background->getTag() == 701){
                background->setTexture("building/building_A_3.png");
                background->setTag(702);
            }
            if(background->getTag() == 703){
                background->setTexture("building/building_A_4.png");
                background->setTag(704);
            }
        }
        background->setPositionY(background_copy ->getPosition().y + background->getContentSize().height - speed);
        
    }
    if(background_copy ->getPosition().y < 0){
        if(background->getTag() == 702){
            background_copy->setTexture("building/building_A_4.png");
            background->setTag(703);
        }
        background_copy->setPositionY(background ->getPosition().y + background->getContentSize().height - speed);
        
    }

}
