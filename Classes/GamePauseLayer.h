//
//  GamePauseLayer.h
//  fly_and_spin
//
//  Created by bin on 15/6/16.
//
//

#ifndef __fly_and_spin__GamePauseLayer__
#define __fly_and_spin__GamePauseLayer__

#include "cocos2d.h"
#include <stdio.h>
#include "SimpleAudioEngine.h"
USING_NS_CC;

class GamePauseLayer : public Layer
{
public:
    CREATE_FUNC(GamePauseLayer);
    virtual bool init();
    void replayMenuCallback(Ref* pSender);
    void backMenuCallback(Ref* pSender);
    void resumeMenuCallback(Ref* pSender);

private:

};


#endif /* defined(__fly_and_spin__GamePauseLayer__) */
