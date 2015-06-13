//
//  GameBackgroundLayer.h
//  fly_and_spin
//
//  Created by bin on 15/6/13.
//
//

#ifndef __fly_and_spin__GameBackgroundLayer__
#define __fly_and_spin__GameBackgroundLayer__

#include "cocos2d.h"
#include <stdio.h>
USING_NS_CC;

class GameBackgroundLayer : public Layer
{
public:
    CREATE_FUNC(GameBackgroundLayer);
    virtual bool init();
    Sprite *background;
    Sprite *background_copy;
    void updateBackground(int score, int speed);
    int speed;
};

#endif /* defined(__fly_and_spin__GameBackgroundLayer__) */
