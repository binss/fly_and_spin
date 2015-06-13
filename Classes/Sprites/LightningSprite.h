//
//  LightningSprite.h
//  fly_and_spin
//
//  Created by bin on 15/6/10.
//
//

#ifndef __fly_and_spin__LightningSprite__
#define __fly_and_spin__LightningSprite__

#include <stdio.h>
#include "cocos2d.h"

USING_NS_CC;

class LightningSprite : public Sprite{
public:
    static LightningSprite * create();
    bool init();
//    static int speed;
};

#endif /* defined(__fly_and_spin__LightningSprite__) */
