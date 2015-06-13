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
    if ( !Layer::init() )
    {
        return false;
    }
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    auto label = Label::createWithTTF("Game Over", "fonts/Marker Felt.ttf", 160);
    
    label->setPosition(Vec2(origin.x + visibleSize.width/2, origin.y + visibleSize.height * 0.7));
    
    this->addChild(label, 1);
    
    char score[50];
    sprintf(score, "Your Height: %d \n\n Highest: 9999", UserDefault::getInstance()->getIntegerForKey("current_score"));
    auto score_label = Label::createWithTTF(score, "fonts/Marker Felt.ttf", 60);

    score_label->setPosition(Vec2(origin.x + visibleSize.width/2, origin.y + visibleSize.height / 2 - label->getContentSize().height + 100));
    
    this->addChild(score_label, 1);
    
    MenuItemFont::setFontSize(80);
    MenuItemFont::setFontName("fonts/Marker Felt.ttf");

    auto replayItem = MenuItemFont::create("Restart", CC_CALLBACK_1(GameOverScene::replayMenuCallback, this));
    auto backItem = MenuItemFont::create("Menu", CC_CALLBACK_1(GameOverScene::backMenuCallback, this));

    replayItem->setPosition(Vec2(origin.x + visibleSize.width / 2,
                                origin.y + + visibleSize.height / 2 - replayItem->getContentSize().height/2 - 300) );
    backItem->setPosition(Vec2(origin.x + visibleSize.width / 2,
                                 origin.y + + visibleSize.height / 2 - replayItem->getContentSize().height/2 - 400));
    
    // create menu, it's an autorelease object
    auto menu = Menu::create(replayItem, backItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);
    
    return true;
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
    SceneManager::sharedSceneManager()->changeScene(SceneManager::en_MainScene);
}

void GameOverScene::replayMenuCallback(Ref* pSender)
{
    SceneManager::sharedSceneManager()->changeScene(SceneManager::en_GameScene);

}