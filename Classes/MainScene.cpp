//
//  MainScene.cpp
//  fly_and_spin
//
//  Created by bin on 15/6/13.
//
//

#include "MainScene.h"
#include "SceneManager.h"
#include "SimpleAudioEngine.h"
#include "CircleAction.h"

#define RADIUS 250

bool MainScene::init()
{
    if ( !Layer::init() )
    {
        return false;
    }
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    auto title_label = Label::createWithTTF("Fly & Spin", "fonts/Marker Felt.ttf", 160);
    title_label->setPosition(Vec2(origin.x + visibleSize.width/2, origin.y + visibleSize.height * 0.85));
    this->addChild(title_label, 1);
    
    auto name_label = Label::createWithTTF("bin( www.binsite.me )", "fonts/Marker Felt.ttf", 40);
    name_label->setPosition(Vec2(origin.x + visibleSize.width/2 + 150, title_label->getPosition().y - 120));
    this->addChild(name_label, 1);
    
    std::string welcome_string = "欢迎你： " + UserDefault::getInstance()->getStringForKey("name");
    
    auto welcome_label = Label::createWithSystemFont(welcome_string, "createWithSystemFont", 30);
    welcome_label->setPosition(Vec2(visibleSize.width/2, 50));
    this->addChild(welcome_label, 1);
    
    
    MenuItemFont::setFontSize(80);
    MenuItemFont::setFontName("fonts/Marker Felt.ttf");
    
    auto replayItem = MenuItemFont::create("Start", CC_CALLBACK_1(MainScene::startMenuCallback, this));
    auto backItem = MenuItemFont::create("Help", CC_CALLBACK_1(MainScene::helpMenuCallback, this));
    
    replayItem->setPosition(Vec2(origin.x + visibleSize.width / 2,
                                 origin.y + visibleSize.height / 4 - replayItem->getContentSize().height/2 ));
    backItem->setPosition(Vec2(origin.x + visibleSize.width / 2,
                               origin.y + + visibleSize.height / 4 - backItem->getContentSize().height/2 - 100));
    
    menu = Menu::create(replayItem, backItem, NULL);
    menu->setPosition(Vec2::ZERO);
    addChild(menu, 1);
    
    bird_A = BirdSprite::createWithType(1);
    bird_A->setPosition(Vec2(visibleSize.width/2 - RADIUS, visibleSize.height * 0.7f - RADIUS));
    addChild(bird_A, 10);

    bird_B = BirdSprite::createWithType(2);
    bird_B->setPosition(Vec2(visibleSize.width/2 + RADIUS, visibleSize.height * 0.7f - RADIUS));
    addChild(bird_B, 10);

    spin_center = Vec2(visibleSize.width/2 , visibleSize.height * 0.7f - RADIUS);
    direction = -1;
    
    bird_A->spin(direction, spin_center);
    bird_B->spin(direction, spin_center);

    schedule(schedule_selector(MainScene::changeDirection), 3.0f);

    CocosDenshion::SimpleAudioEngine::getInstance()->preloadBackgroundMusic("sound/game_music.mp3");
    CocosDenshion::SimpleAudioEngine::getInstance()->stopBackgroundMusic();
    CocosDenshion::SimpleAudioEngine::getInstance()->setBackgroundMusicVolume(0.3f);
    CocosDenshion::SimpleAudioEngine::getInstance()->setEffectsVolume(1.0f);


    return true;
}

void MainScene::changeDirection(float dt){
    bird_A->stopAllActions();
    bird_B->stopAllActions();
    direction = -direction;
    bird_A->spin(direction, spin_center);
    bird_B->spin(direction, spin_center);
}

Scene* MainScene::shareMainScene()
{
    
    Scene *_shareMainScene = Scene::createWithPhysics();
    _shareMainScene->getPhysicsWorld()->setGravity(cocos2d::Vect(0,0));
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
    bird_A->stopAllActions();
    bird_B->stopAllActions();
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
    
    backItem->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 8 - backItem->getContentSize().height/2 ));
    
    auto help_menu = Menu::create(backItem, NULL);
    help_menu->setPosition(Vec2::ZERO);
    help_sprite->addChild(help_menu, 21);
}

void MainScene::backMenuCallback(Ref* pSender)
{
    help_sprite->removeFromParent();
    menu->setEnabled(true);
}
