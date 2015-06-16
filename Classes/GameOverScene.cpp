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
    addChild(label, 1);
    
    
    char score[50];
    int highest = UserDefault::getInstance()->getIntegerForKey("highest_score", 0);
    int current = UserDefault::getInstance()->getIntegerForKey("current_score");
    if( current > highest){
        highest = current;
        UserDefault::getInstance()->setIntegerForKey("highest_score", highest);
    }
    sprintf(score, "Your Height: %d \n\n Highest: %d", current, highest);
    auto score_label = Label::createWithTTF(score, "fonts/Marker Felt.ttf", 60);
    score_label->setPosition(Vec2(origin.x + visibleSize.width/2, origin.y + visibleSize.height / 2 - score_label->getContentSize().height + 100));
    addChild(score_label, 1);
    
    
    MenuItemFont::setFontSize(80);
    MenuItemFont::setFontName("fonts/Marker Felt.ttf");
    auto replayItem = MenuItemFont::create("Restart", CC_CALLBACK_1(GameOverScene::replayMenuCallback, this));
    auto backItem = MenuItemFont::create("Menu", CC_CALLBACK_1(GameOverScene::backMenuCallback, this));
    replayItem->setPosition(Vec2(origin.x + visibleSize.width / 2,
                                origin.y + + visibleSize.height / 2 - replayItem->getContentSize().height/2 - 300) );
    backItem->setPosition(Vec2(origin.x + visibleSize.width / 2,
                                 origin.y + + visibleSize.height / 2 - backItem->getContentSize().height/2 - 400));
    auto menu = Menu::create(replayItem, backItem, NULL);
    menu->setPosition(Vec2::ZERO);
    addChild(menu, 1);
    
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
    CCLOG("back");
    SceneManager::sharedSceneManager()->changeScene(SceneManager::en_MainScene);
}

void GameOverScene::replayMenuCallback(Ref* pSender)
{
    CCLOG("replay");
    SceneManager::sharedSceneManager()->changeScene(SceneManager::en_GameScene);

}