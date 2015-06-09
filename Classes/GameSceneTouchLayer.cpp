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

    auto bird_A = Sprite::create("bird_A.png");
    bird_A->setScale(0.3);
    bird_A->setTag(BIRD_A_TAG);
    bird_A->setPosition(Vec2(visibleSize.width/2 - RADIUS, visibleSize.height/2 - RADIUS));
    addBoxBodyForSprite(bird_A, 0.3, true);
    addChild(bird_A, 30);
    
    auto bird_B = Sprite::create("bird_B.png");
    bird_B->setScale(0.3);
    bird_B->setTag(BIRD_B_TAG);
    bird_B->setPosition(Vec2(visibleSize.width/2 + RADIUS, visibleSize.height/2 - RADIUS));
    addBoxBodyForSprite(bird_B, 0.3, true);
    addChild(bird_B, 30);
    barrier_vector = Vector<Sprite*>(MAX_BARRIER);
    old_direction = 1;
    
    this->schedule(schedule_selector(GameSceneTouchLayer::createBarrier),3.0f);

    this->scheduleUpdate();

    return true;
}

bool GameSceneTouchLayer::onContactBegin(PhysicsContact& contact){
    CCLOG("crash");
    auto node_A = (Sprite*)contact.getShapeA()->getBody()->getNode();
    auto node_B = (Sprite*)contact.getShapeB()->getBody()->getNode();
    
    if (node_A == NULL || node_B == NULL)
    {
        return true;
    }
    // 如果是鸟
    if (node_A->getTag() >= BIRD_A_TAG){
        CCLOG("bird");
    }
    SceneManager::sharedSceneManager()->changeScene(SceneManager::en_GameoverScene);

    return true;
}

void GameSceneTouchLayer::createBarrier(float dt)
{
    Size visibleSize = Director::getInstance()->getVisibleSize();
    char* pic;
    int tag;
    int randomType = CCRANDOM_0_1() * 100 + 1;
    if (randomType < 30)
    {
        tag = 10;
        pic = "barrier_short.png";     //砖A
        auto *barrier = Sprite::create(pic);
        barrier->setScale(0.8f);
        barrier->setTag(tag);
        barrier->setPosition(Vec2(visibleSize.width/2 - barrier->getContentSize().width * 0.4 ,visibleSize.height));
        barrier_vector.pushBack(barrier);
        addBoxBodyForSprite(barrier, 0.8, false);

        addChild(barrier, 30);
    }
    else{
        tag = 11;
        pic = "barrier_long.png";     //砖Long
        auto *barrier = Sprite::create(pic);
        barrier->setScale(0.8f);
        barrier->setTag(tag);
        barrier->setPosition(Vec2(barrier->getContentSize().width * 0.4, visibleSize.height));
        barrier_vector.pushBack(barrier);
        addBoxBodyForSprite(barrier, 0.8, false);

        addChild(barrier, 30);
    }
    
}

void GameSceneTouchLayer::update(float dt)
{
    for(auto barrier : barrier_vector)
    {
//        log("sprite tag = %d", barrier->getTag());
        barrier->setPosition(Vec2(barrier->getPosition().x, barrier->getPosition().y-5));
        if(barrier->getPosition().y < -barrier->getContentSize().height){
            garbageCollection(barrier);
        }
    }
//    CCLOG("%d", barrier_vector.size());
//    CCARRAY_FOREACH(crashArray,obj)
//    {
//        CCSprite *object = (CCSprite*)obj;
//        object->setPositionX(object->getPosition().x-1);
//        
//        if(object->getPosition().x >= 49 && object->getPosition().x <= 51 && actionNum == ACTION_RUN)
//        {
//            switch(object->getTag())
//            {
//                case 3:
//                {
//                    CCLOG("gameOver");
//                    gameOver();
//                    return;
//                }
//                case 1: score++;break;
//                case 2: score += 10;break;
//            }
//            SimpleAudioEngine::sharedEngine()->playEffect("sound/coin.mp3");
//            char char_score[6];
//            itoa(score, char_score, 10);
//            GameScene::shareGameScene()->menuLayer->setScore(char_score);
//            rubbishCollection(object);
//            
//            continue;
//        }
//        if(object->getPosition().x < 0)
//            rubbishCollection(object);
//    }
//    
//    if(backgroundCopy ->getPosition().x>=0)
//    {
//        background->setPosition(ccp(background->getPosition().x-1, 0));
//        backgroundCopy->setPosition(ccp(backgroundCopy->getPosition().x-1, 0));
//        shop->setPosition(ccp(shop->getPosition().x-1.5, shop->getPosition().y));
//        ground->setPosition(ccp(ground->getPosition().x-1, 0));
//        groundCopy->setPosition(ccp(groundCopy->getPosition().x-1, 0));
//    }
//    else
//    {
//        resetBackground();
//    }
}



void GameSceneTouchLayer::garbageCollection(Ref *object){
    Sprite *sprite = (Sprite*)object;

    if (sprite->getTag() >= BARRIER_TAG && sprite->getTag() <= 20 )
    {
        barrier_vector.eraseObject(sprite);
        this->removeChild(sprite,true);
    }
}

void GameSceneTouchLayer::addBoxBodyForSprite(Sprite* sprite, float scale, bool dynamic)
{
    auto body = PhysicsBody::createBox(sprite->getContentSize() * scale);
    body->setDynamic(dynamic);
//    body->setGroup(1);
    body->setCategoryBitmask(1);
    body->setCollisionBitmask(1);
    body->setContactTestBitmask(1);
    sprite->setPhysicsBody(body);
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
    if(direction != old_direction){
        getChildByTag(BIRD_A_TAG)->runAction(RotateBy::create(0.1, 180));
        getChildByTag(BIRD_B_TAG)->runAction(RotateBy::create(0.1, 180));

    }

    getChildByTag(BIRD_A_TAG)->runAction(CCRepeatForever::create(CircleAction::create(2, Point(visibleSize.width/2 , visibleSize.height/2 - RADIUS), RADIUS, 360, direction)));
    getChildByTag(BIRD_B_TAG)->runAction(CCRepeatForever::create(CircleAction::create(2, Point(visibleSize.width/2 , visibleSize.height/2 - RADIUS), RADIUS, 360, direction)));
    return true;
}

void GameSceneTouchLayer::onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *event){
    log("TouchTest onTouchesEnded");
    getChildByTag(BIRD_A_TAG)->stopAllActions();
    getChildByTag(BIRD_B_TAG)->stopAllActions();
    old_direction = direction;

//    bird->stopAction(repeat_circle);
//    auto location = touch->getLocation();
//    CCLOG("%f", location.x);
}