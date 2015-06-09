//
//  GameOverScene.cpp
//  fly_and_spin
//
//  Created by bin on 15/6/9.
//
//

#include "GameOverScene.h"

bool GameOverScene::init()
{
    bool bRet = true;
    do
    {
        if ( !CCLayer::init() )
        {
            return false;
        }
        Size visibleSize = Director::getInstance()->getVisibleSize();
        Vec2 origin = Director::getInstance()->getVisibleOrigin();

//        this->setTouchEnabled(true);
//        this->setTouchMode(Touch::DispatchMode::ONE_BY_ONE);
        auto label = Label::createWithTTF("Game Over", "fonts/Marker Felt.ttf", 40);
        
        label->setPosition(Vec2(origin.x + visibleSize.width/2, origin.y + visibleSize.height - label->getContentSize().height));
        
        this->addChild(label, 1);
        
    } while (0);
    
    return bRet;
}

Scene* GameOverScene::shareGameOverScene()
{
    Scene *_shareGameOverScene = Scene::create();
    
    GameOverScene *layer = GameOverScene::create();
    
    if (!layer)
    {
        CC_SAFE_DELETE(layer);
    }
    
    _shareGameOverScene->addChild(layer);
    
    return _shareGameOverScene;
}