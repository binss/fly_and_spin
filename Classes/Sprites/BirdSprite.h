//
//  BirdSprite.h
//  fly_and_spin
//
//  Created by bin on 15/6/10.
//
//

#ifndef __fly_and_spin__BirdSprite__
#define __fly_and_spin__BirdSprite__

#include <stdio.h>
#include "cocos2d.h"

USING_NS_CC;

class BirdSprite : public Sprite{
public:
    static BirdSprite * createWithType(int type);
    bool initWithType(int type);
    int direction;
    int old_direction;
    void spin(int direction);
};
#endif /* defined(__fly_and_spin__BirdSprite__) */
