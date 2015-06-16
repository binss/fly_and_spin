//
//  GamePauseLayer.cpp
//  fly_and_spin
//
//  Created by bin on 15/6/16.
//
//

#include "GamePauseLayer.h"
#include "SceneManager.h"

bool GamePauseLayer::init()
{
    if(!Layer::init())
    {
        return false;
    }
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    MenuItemFont::setFontSize(80);
    MenuItemFont::setFontName("fonts/Marker Felt.ttf");
    auto replayItem = MenuItemFont::create("Restart", CC_CALLBACK_1(GamePauseLayer::replayMenuCallback, this));
    auto backItem = MenuItemFont::create("Menu", CC_CALLBACK_1(GamePauseLayer::backMenuCallback, this));
    auto resumeItem = MenuItemFont::create("Resume", CC_CALLBACK_1(GamePauseLayer::resumeMenuCallback, this));

    replayItem->setPosition(Vec2(origin.x + visibleSize.width / 2,
                                 origin.y + + visibleSize.height / 2 - replayItem->getContentSize().height/2 - 300) );
    backItem->setPosition(Vec2(origin.x + visibleSize.width / 2,
                               origin.y + + visibleSize.height / 2 - replayItem->getContentSize().height/2 - 400));
    resumeItem->setPosition(Vec2(origin.x + visibleSize.width / 2,
                               origin.y + + visibleSize.height / 2 - replayItem->getContentSize().height/2 - 500));
    auto menu = Menu::create(replayItem, backItem, resumeItem, NULL);
    menu->setPosition(Vec2::ZERO);
    addChild(menu, 1);

    return true;
}

void GamePauseLayer::replayMenuCallback(Ref* pSender)
{
    Director::getInstance()->resume();
    SceneManager::sharedSceneManager()->changeScene(SceneManager::en_GameScene);
}

void GamePauseLayer::backMenuCallback(Ref* pSender)
{
    Director::getInstance()->resume();
    SceneManager::sharedSceneManager()->changeScene(SceneManager::en_MainScene);
}



void GamePauseLayer::resumeMenuCallback(Ref* pSender)
{
    Director::getInstance()->resume();
    CocosDenshion::SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
    setVisible(false);
}