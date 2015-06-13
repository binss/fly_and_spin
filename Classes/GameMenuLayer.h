//
//  GameMenuLayer.h
//  fly_and_spin
//
//  Created by bin on 15/6/10.
//
//

#ifndef __fly_and_spin__GameMenuLayer__
#define __fly_and_spin__GameMenuLayer__

#include "cocos2d.h"
#include <stdio.h>
USING_NS_CC;

class GameMenuLayer : public Layer
{
public:
    CREATE_FUNC(GameMenuLayer);
    virtual bool init();
    Label *scoreLabel;
    void updateScore(int score);

};

#endif /* defined(__fly_and_spin__GameMenuLayer__) */
