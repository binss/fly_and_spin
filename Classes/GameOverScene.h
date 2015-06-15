//
//  GameOverScene.h
//  fly_and_spin
//
//  Created by bin on 15/6/9.
//
//

#ifndef __fly_and_spin__GameOverScene__
#define __fly_and_spin__GameOverScene__

#include <stdio.h>
#include "cocos2d.h"
USING_NS_CC;


class GameOverScene : public Layer
{
public:
    virtual bool init();
    CREATE_FUNC(GameOverScene);
    static Scene* shareGameOverScene();
    
    void replayMenuCallback(Ref* pSender);
    void backMenuCallback(Ref* pSender);
};

#endif /* defined(__fly_and_spin__GameOverScene__) */
