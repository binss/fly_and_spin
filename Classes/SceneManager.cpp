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
SceneManager* SceneManager::mSceneManager = NULL;

SceneManager* SceneManager::sharedSceneManager()
{
    if(mSceneManager == NULL)
    {
        mSceneManager = new SceneManager();
        if(mSceneManager && mSceneManager->init())
        {
            mSceneManager->autorelease();
        }
        else
        {
            CC_SAFE_DELETE(mSceneManager);
            mSceneManager = NULL;
        }
    }
    
    return mSceneManager;
}

bool SceneManager::init()
{
    return true;
}

void SceneManager::changeScene(EnumSceneType scene)
{
//    Director::getInstance()->runWithScene(GameOverScene::shareGameOverScene());
//    return;

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
                GameScene::shareGameScene()->reset();
                Director::getInstance()->replaceScene(CCTransitionProgressHorizontal::create(1.0f, MainScene::shareMainScene()));
            }
            break;
        }
        case en_GameScene:
        {
            GameScene::shareGameScene()->reset();
            Director::getInstance()->replaceScene(CCTransitionProgressHorizontal::create(1.0f, GameScene::shareGameScene()));
            break;
        }
        case en_GameoverScene:          //游戏界面
        {
            Director::getInstance()->replaceScene(CCTransitionCrossFade::create(1.0f, GameOverScene::shareGameOverScene()));
            CCLOG("gameover");
            break;
        }

            
    }
}

