//
//  SceneManager.h
//  fly_and_spin
//
//  Created by bin on 15/6/9.
//
//

#ifndef __fly_and_spin__SceneManager__
#define __fly_and_spin__SceneManager__

#include "cocos2d.h"

USING_NS_CC;

class SceneManager : public Ref
{
public:
    //以下是场景枚举
    enum EnumSceneType {
        en_MainScene,               //主画面
        en_GameScene,               //游戏画面
        en_GameoverScene,           //gameover界面        
    };
    
    static SceneManager* sharedSceneManager();
    virtual bool init();
    //改变场景
    void changeScene(EnumSceneType enScenType);
    
private:
    static SceneManager* _SceneManager;
};

#endif /* defined(__fly_and_spin__SceneManager__) */
