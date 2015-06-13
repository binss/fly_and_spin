//
//  BatterySprite.h
//  fly_and_spin
//
//  Created by bin on 15/6/11.
//
//

#ifndef __fly_and_spin__BatterySprite__
#define __fly_and_spin__BatterySprite__

#include <stdio.h>
#include "cocos2d.h"

USING_NS_CC;

class BatterySprite : public Sprite{
public:
    static BatterySprite * create();
    bool init();
    int nextCondition();
    int getCondition();
private:
    int condition;
};

#endif /* defined(__fly_and_spin__BatterySprite__) */
