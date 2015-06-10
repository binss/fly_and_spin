//
//  GameOverScene.cpp
//  fly_and_spin
//
//  Created by bin on 15/6/9.
//
//

#include "GameOverScene.h"
#include "SceneManager.h"

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
        auto label = Label::createWithTTF("Game Over", "fonts/wawa.ttf", 40);
        
        label->setPosition(Vec2(origin.x + visibleSize.width/2, origin.y + visibleSize.height - label->getContentSize().height));
        
        this->addChild(label, 1);
        MenuItemFont::setFontSize(50);
        MenuItemFont::setFontName("fonts/Marker Felt.ttf");

        auto replayItem = MenuItemFont::create("Restart", CC_CALLBACK_1(GameOverScene::replayMenuCallback, this));
        auto backItem = MenuItemFont::create("Menu", CC_CALLBACK_1(GameOverScene::backMenuCallback, this));

        replayItem->setPosition(Vec2(origin.x + visibleSize.width / 2,
                                    origin.y + + visibleSize.height / 2 - replayItem->getContentSize().height/2));
        backItem->setPosition(Vec2(origin.x + visibleSize.width / 2,
                                     origin.y + + visibleSize.height / 2 - replayItem->getContentSize().height/2 - 100));
        
        // create menu, it's an autorelease object
        auto menu = Menu::create(replayItem, backItem, NULL);
        menu->setPosition(Vec2::ZERO);
        this->addChild(menu, 1);
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

void GameOverScene::backMenuCallback(Ref* pSender)
{
    Director::getInstance()->end();
}

void GameOverScene::replayMenuCallback(Ref* pSender)
{
    SceneManager::sharedSceneManager()->changeScene(SceneManager::en_MainScene);

}