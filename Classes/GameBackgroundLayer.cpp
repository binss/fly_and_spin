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
//    background->setTag(700);
    background->setScaleX(visibleSize.width / background->getContentSize().width);
    background->setAnchorPoint(Vec2(0,1));
    background->setPosition(Vec2(0,background->getContentSize().height));
    addChild(background, 0);
    
    background_copy = Sprite::create("building/building_A_2.png");
    background_copy->setScaleX(visibleSize.width / background->getContentSize().width);
    background_copy->setAnchorPoint(Vec2(0,1));
    background_copy->setPosition(Vec2(0, 2*background->getContentSize().height));
    addChild(background_copy, 0);
    
    stage = 0;
    
    return true;
}

void GameBackgroundLayer::updateBackground(int score, int speed){
    
    background->setPositionY(background->getPosition().y  - speed);
    background_copy->setPositionY(background_copy->getPosition().y  - speed);
    
    if(background ->getPosition().y < 0){
        if(stage == 0){
            background->setTexture("building/building_A_2.png");
            stage = 1;
        }
        if(score >= 1000){
            if(stage == 1){
                background->setTexture("building/building_A_3.png");
                stage = 2;
            }
            if(stage == 3){
                background->setTexture("building/building_A_4.png");
                stage = 4;
            }
        }
        if(score >= 5000){
            if(stage == 4){
                background->setTexture("building/building_A_5.png");
                stage = 5;
            }
        }
        background->setPositionY(background_copy ->getPosition().y + background->getContentSize().height - speed);
        
    }
    if(background_copy ->getPosition().y < 0){
        if(stage == 2){
            background_copy->setTexture("building/building_A_4.png");
            stage = 3;
        }
        if(stage == 5){
            background_copy->setTexture("building/building_A_5.png");
            stage = 6;
        }
        background_copy->setPositionY(background ->getPosition().y + background->getContentSize().height - speed);
        
    }

}
