//
//  SceneManager.cpp
//  fly_and_spin
//
//  Created by bin on 15/6/9.
//
//

#include "SceneManager.h"
#include "GameOverScene.h"
#include "GameScene.h"
#include "MainScene.h"
SceneManager* SceneManager::_SceneManager = NULL;

SceneManager* SceneManager::sharedSceneManager()
{
    if(_SceneManager == NULL)
    {
        _SceneManager = new SceneManager();
        if(_SceneManager && _SceneManager->init())
        {
            _SceneManager->autorelease();
        }
        else
        {
            CC_SAFE_DELETE(_SceneManager);
            _SceneManager = NULL;
        }
    }
    
    return _SceneManager;
}

bool SceneManager::init()
{
    return true;
}

void SceneManager::changeScene(EnumSceneType scene)
{
    switch (scene)
    {
        case en_MainScene:          //游戏主画面
        {
            Scene* current_scene = Director::getInstance()->getRunningScene();
            //如果当前没有在运行的场景的话，加载主场景，否则更换场景
            if(current_scene == NULL)
            {
                Director::getInstance()->runWithScene(MainScene::shareMainScene());
            }
            else{
                Director::getInstance()->replaceScene(TransitionProgressHorizontal::create(1.0f, MainScene::shareMainScene()));
            }
            break;
        }
        case en_GameScene:
        {
            GameScene::shareGameScene()->reset();
            Director::getInstance()->replaceScene(TransitionProgressHorizontal::create(1.0f, GameScene::shareGameScene()));
            break;
        }
        case en_GameoverScene:          //游戏界面
        {
            Director::getInstance()->replaceScene(TransitionCrossFade::create(1.0f, GameOverScene::shareGameOverScene()));
            CCLOG("gameover");
            break;
        }

            
    }
}

