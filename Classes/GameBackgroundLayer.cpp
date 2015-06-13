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
    
    Sprite *background = Sprite::create("building/building_A_1.png");
    
    return true;
}
