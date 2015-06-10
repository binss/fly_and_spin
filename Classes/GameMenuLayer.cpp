//
//  GameMenuLayer.cpp
//  fly_and_spin
//
//  Created by bin on 15/6/10.
//
//

#include "GameMenuLayer.h"

bool GameMenuLayer::init()
{
    if(!Layer::init())
    {
        return false;
    }
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    scoreLabel = Label::createWithTTF("0", "fonts/wawa.ttf", 40);
    scoreLabel->setPosition(Vec2(origin.x + visibleSize.width/2, origin.y + visibleSize.height - scoreLabel->getContentSize().height));
//    scoreLabel->setString("000000000");
    scoreLabel->setString("0000");
    this->addChild(scoreLabel, 1);

    return true;
}

void GameMenuLayer::setScore(int score){
    char char_score[6];
    sprintf(char_score, "%d", score);
    scoreLabel->setString(char_score);
}