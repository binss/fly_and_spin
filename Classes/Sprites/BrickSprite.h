//
//  BrickSprite.h
//  fly_and_spin
//
//  Created by bin on 15/6/10.
//
//

#ifndef __fly_and_spin__BrickSprite__
#define __fly_and_spin__BrickSprite__

#include <stdio.h>
#include "cocos2d.h"

USING_NS_CC;

class BrickSprite : public Sprite{
public:
    static BrickSprite * createWithType(int type);
    bool initWithType(int type);

};
#endif /* defined(__fly_and_spin__BrickSprite__) */
