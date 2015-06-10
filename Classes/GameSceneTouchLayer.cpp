//
//  GameSceneTouchLayer.cpp
//  fly_and_spin
//
//  Created by bin on 15/6/8.
//
//

#include "GameSceneTouchLayer.h"
#include "CircleAction.h"
#include "SceneManager.h"
#include "GameScene.h"
#include "LightningSprite.h"
#include "BrickSprite.h"
#include "BirdSprite.h"

//Layer * GameSceneTouchLayer::create(){
//    Layer *layer = GameSceneTouchLayer::init();
//    return layer;
//}
//
#define BIRD_A_TAG 100
#define BIRD_B_TAG 101
#define MAX_BARRIER 100
#define BARRIER_TAG 10
#define RADIUS 250
#define LIGHTNING_A_TAG 20
#define LIGHTNING_B_TAG 21

bool GameSceneTouchLayer::init()
{
    CCLOG("TouchTest call");

    if(!Layer::init())
    {
        return false;
    }
    //允许接收触摸事件
    this->setTouchEnabled(true);
    this->setTouchMode(Touch::DispatchMode::ONE_BY_ONE);
    EventDispatcher* eventDispatcher = Director::getInstance()->getEventDispatcher();
//    
//    auto listen = EventListenerTouchAllAtOnce::create();
//    listen->onTouchesBegan = CC_CALLBACK_2(GameSceneTouchLayer::onTouchesBegan,this);
////    listen->onTouchesMoved = CC_CALLBACK_2(TouchTest::onTouchesMoved,this);
//    listen->onTouchesEnded = CC_CALLBACK_2(GameSceneTouchLayer::onTouchesEnded,this);
////    listen->onTouchesCancelled = CC_CALLBACK_2(TouchTest::onTouchesCancelled,this);
//    eventDispatcher->addEventListenerWithSceneGraphPriority(listen,this);

    auto contactListener = EventListenerPhysicsContact::create();
    contactListener->onContactBegin = CC_CALLBACK_1(GameSceneTouchLayer::onContactBegin, this);
    eventDispatcher->addEventListenerWithSceneGraphPriority(contactListener, this);
    
    
    Size visibleSize = Director::getInstance()->getVisibleSize();

    BirdSprite * bird_A = BirdSprite::createWithType(1);
    bird_A->setPosition(Vec2(visibleSize.width/2 - RADIUS, visibleSize.height/2 - RADIUS));
    addChild(bird_A, 30);
    
    
    BirdSprite * bird_B = BirdSprite::createWithType(2);
    bird_B->setPosition(Vec2(visibleSize.width/2 + RADIUS, visibleSize.height/2 - RADIUS));
    addChild(bird_B, 30);
    
    barrier_vector = Vector<Sprite*>(MAX_BARRIER);
    
    
    score = 0;

    this->schedule(schedule_selector(GameSceneTouchLayer::createBarrier),3.0f);

    this->scheduleUpdate();
    

    return true;
}



bool GameSceneTouchLayer::onContactBegin(PhysicsContact& contact){
    CCLOG("crash");
    auto node_A = (Sprite*)contact.getShapeA()->getBody()->getNode();
    auto node_B = (Sprite*)contact.getShapeB()->getBody()->getNode();
    
    Sprite * bird_node;
    Sprite * other_node;
    if (node_A == NULL || node_B == NULL)
    {
        return true;
    }
    // 判断鸟节点
    if (node_A->getTag() >= BIRD_A_TAG){
        bird_node = node_A;
        other_node = node_B;
    }
    else{
        bird_node = node_B;
        other_node = node_A;
    }
    // 如果是闪电
    if( other_node->getTag() == LIGHTNING_A_TAG){
        if( bird_node->getTag() == BIRD_A_TAG){
            CCLOG("get power");
        }
        else{
            CCLOG("dead");
        }
    }
    else if( other_node->getTag() == LIGHTNING_B_TAG){
        if( bird_node->getTag() == BIRD_B_TAG){
            CCLOG("get power");
        }
        else{
            CCLOG("dead");
        }
    }
    
//    SceneManager::sharedSceneManager()->changeScene(SceneManager::en_GameoverScene);

    return true;
}

void GameSceneTouchLayer::createBarrier(float dt)
{
    Size visibleSize = Director::getInstance()->getVisibleSize();
    int randomType = CCRANDOM_0_1() * 100 + 1;
    if (randomType < 40)
    {
//        BrickSprite *barrier = BrickSprite::createWithType(1);
//        barrier_vector.pushBack(barrier);
//        addChild(barrier, 30);
        LightningSprite *lightning = LightningSprite::create();
        addChild(lightning, 30);
    }
    else if(randomType < 50){
        BrickSprite *barrier = BrickSprite::createWithType(3);
        barrier_vector.pushBack(barrier);
        addChild(barrier, 30);
    }
    else if (randomType < 80){
        BrickSprite *barrier = BrickSprite::createWithType(4);
        barrier_vector.pushBack(barrier);
        addChild(barrier, 30);
    }
    else{
        BrickSprite *barrier = BrickSprite::createWithType(2);
        barrier_vector.pushBack(barrier);
        addChild(barrier, 30);
    }
    
}

void GameSceneTouchLayer::update(float dt)
{
    score ++;
    GameScene::shareGameScene()->menuLayer->setScore(score);

    for(auto barrier : barrier_vector)
    {
        if(barrier->getPosition().y < -barrier->getContentSize().height){
            garbageCollection(barrier);
        }
    }
}



void GameSceneTouchLayer::garbageCollection(Ref *object){
    Sprite *sprite = (Sprite*)object;

    if (sprite->getTag() >= BARRIER_TAG && sprite->getTag() <= 20 )
    {
        barrier_vector.eraseObject(sprite);
        this->removeChild(sprite,true);
    }
}

void GameSceneTouchLayer::onEnter(){
    Layer::onEnter();

    Size visibleSize = Director::getInstance()->getVisibleSize();

    CCLOG("Enter layer");
}

bool GameSceneTouchLayer::onTouchBegan(Touch* touch, Event  *event)
{
    log("TouchTest onTouchBegan");
    auto location = touch->getLocation();
    Size visibleSize = Director::getInstance()->getVisibleSize();
    if (location.x <= visibleSize.width / 2){
        CCLOG("left span");
        direction = -1;
    }
    else{
        CCLOG("right span");
        direction = 1;
    }
    dynamic_cast<BirdSprite*>(getChildByTag(BIRD_A_TAG))->spin(direction);
    dynamic_cast<BirdSprite*>(getChildByTag(BIRD_B_TAG))->spin(direction);

    return true;
}

void GameSceneTouchLayer::onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *event){
    log("TouchTest onTouchesEnded");
    getChildByTag(BIRD_A_TAG)->stopAllActions();
    getChildByTag(BIRD_B_TAG)->stopAllActions();
}