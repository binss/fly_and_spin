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
#include "BirdSprite.h"

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
    void changeDirection(float dt);
    
private:
    Sprite *help_sprite;
    Menu *menu;
    
    BirdSprite * bird_A;
    BirdSprite * bird_B;
    Vec2 spin_center;

    int direction;
};

#endif /* defined(__fly_and_spin__MainScene__) */
