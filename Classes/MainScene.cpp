//
//  MainScene.cpp
//  fly_and_spin
//
//  Created by bin on 15/6/13.
//
//

#include "MainScene.h"
#include "SceneManager.h"

bool MainScene::init()
{
    if ( !Layer::init() )
    {
        return false;
    }
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    auto title_label = Label::createWithTTF("Fly & Spin", "fonts/Marker Felt.ttf", 160);
    title_label->setPosition(Vec2(origin.x + visibleSize.width/2, origin.y + visibleSize.height * 0.7));
    
    this->addChild(title_label, 1);
    
    MenuItemFont::setFontSize(80);
    MenuItemFont::setFontName("fonts/Marker Felt.ttf");
    
    auto replayItem = MenuItemFont::create("Start", CC_CALLBACK_1(MainScene::startMenuCallback, this));
    auto backItem = MenuItemFont::create("Help", CC_CALLBACK_1(MainScene::helpMenuCallback, this));
    
    replayItem->setPosition(Vec2(origin.x + visibleSize.width / 2,
                                 origin.y + + visibleSize.height / 2 - replayItem->getContentSize().height/2 - 300) );
    backItem->setPosition(Vec2(origin.x + visibleSize.width / 2,
                               origin.y + + visibleSize.height / 2 - replayItem->getContentSize().height/2 - 400));
    
    menu = Menu::create(replayItem, backItem, NULL);
    menu->setPosition(Vec2::ZERO);
    addChild(menu, 1);
    
    return true;
}

Scene* MainScene::shareMainScene()
{
    Scene *_shareMainScene = Scene::create();
    
    MainScene *layer = MainScene::create();
    
    if (!layer)
    {
        CC_SAFE_DELETE(layer);
    }
    
    _shareMainScene->addChild(layer);
    
    return _shareMainScene;
}

void MainScene::startMenuCallback(Ref* pSender)
{
    SceneManager::sharedSceneManager()->changeScene(SceneManager::en_GameScene);

}

void MainScene::helpMenuCallback(Ref* pSender)
{
    menu->setEnabled(false);
    
    Size visibleSize = Director::getInstance()->getVisibleSize();

    help_sprite = Sprite::create("help.png");
    help_sprite->setPosition(help_sprite->getContentSize().width/2, help_sprite->getContentSize().height/2);
    this->addChild(help_sprite, 20);
    auto backItem = MenuItemFont::create("back", CC_CALLBACK_1(MainScene::backMenuCallback, this));
    
    backItem->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2 - backItem->getContentSize().height/2 - 500));
    
    auto help_menu = Menu::create(backItem, NULL);
    help_menu->setPosition(Vec2::ZERO);
    help_sprite->addChild(help_menu, 21);
}

void MainScene::backMenuCallback(Ref* pSender)
{
    help_sprite->removeFromParent();
    menu->setEnabled(true);

}
