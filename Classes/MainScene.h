//
//  MainScene.h
//  fly_and_spin
//
//  Created by bin on 15/6/13.
//
//

#ifndef __fly_and_spin__MainScene__
#define __fly_and_spin__MainScene__

#include <stdio.h>
#include "cocos2d.h"
USING_NS_CC;


class MainScene : public Layer
{
public:
    virtual bool init();
    CREATE_FUNC(MainScene);
    static Scene* shareMainScene();
    void startMenuCallback(Ref* pSender);
    void helpMenuCallback(Ref* pSender);
    void backMenuCallback(Ref* pSender);
    Sprite *help_sprite;
    Menu *menu;
};

#endif /* defined(__fly_and_spin__MainScene__) */
