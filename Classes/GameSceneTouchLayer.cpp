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
#define BATTERY_TAG 200

#define NORMAL_SPEED 4
#define SUPER_SPEED 16


bool GameSceneTouchLayer::init()
{
    CCLOG("TouchTest call");

    if(!Layer::init())
    {
        return false;
    }
    // 监听触摸事件
    EventDispatcher* eventDispatcher = Director::getInstance()->getEventDispatcher();
    auto touchListener = EventListenerTouchOneByOne::create();
    touchListener->onTouchBegan = CC_CALLBACK_2(GameSceneTouchLayer::onTouchBegan, this);
    touchListener->onTouchEnded = CC_CALLBACK_2(GameSceneTouchLayer::onTouchEnded, this);
    eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);

    // 监听碰撞事件
    auto contactListener = EventListenerPhysicsContact::create();
    contactListener->onContactBegin = CC_CALLBACK_1(GameSceneTouchLayer::onContactBegin, this);
    eventDispatcher->addEventListenerWithSceneGraphPriority(contactListener, this);
    
    
    Size visibleSize = Director::getInstance()->getVisibleSize();

    bird_A = BirdSprite::createWithType(1);
    bird_A->setPosition(Vec2(visibleSize.width/2 - RADIUS, visibleSize.height/2 - RADIUS));
    addChild(bird_A, 30);
    
    
    bird_B = BirdSprite::createWithType(2);
    bird_B->setPosition(Vec2(visibleSize.width/2 + RADIUS, visibleSize.height/2 - RADIUS));
    addChild(bird_B, 30);
    
    
    barrier_vector = Vector<Sprite*>(MAX_BARRIER);
    
    battery = BatterySprite::create();
    addChild(battery, 40);
    
    score = 0;
    score_unit = 1;
    barrier_speed = NORMAL_SPEED;
    streak_A = MotionStreak::create(1.0f, 50, 100, Color3B::RED, "Particles/streak_2.png");
    streak_B = MotionStreak::create(1.0f, 50, 100, Color3B::BLUE, "Particles/streak_2.png");

    addChild(streak_A);
    addChild(streak_B);

    background = Sprite::create("building/building_A_1.png");
    background->setAnchorPoint(Vec2(0,0));
    background->setPosition(Vec2(0,0));
    addChild(background, 0);
    
    background_copy = Sprite::create("building/building_A_1.png");
    background_copy->setAnchorPoint(Vec2(0,0));
    background_copy->setPosition(Vec2(0, background->getContentSize().height - 1));
    addChild(background_copy, 0);
    
    this->schedule(schedule_selector(GameSceneTouchLayer::createBarrier), 3.0f);
//    this->schedule(schedule_selector(GameSceneTouchLayer::update), 0.02f);
    this->scheduleUpdate();

    return true;
}



bool GameSceneTouchLayer::onContactBegin(PhysicsContact& contact){
    CCLOG("crash");
    auto node_A = (Sprite*)contact.getShapeA()->getBody()->getNode();
    auto node_B = (Sprite*)contact.getShapeB()->getBody()->getNode();
    
    BirdSprite * bird_node;
    Sprite * other_node;
    if (node_A == NULL || node_B == NULL)
    {
        return true;
    }
    // 判断鸟节点
    if (node_A->getTag() >= BIRD_A_TAG){
        bird_node = dynamic_cast<BirdSprite*>(node_A);
        other_node = node_B;
    }
    else{
        bird_node = dynamic_cast<BirdSprite*>(node_B);
        other_node = node_A;
    }
    
    // 如果是闪电
    if( other_node->getTag() == LIGHTNING_A_TAG){
        if( bird_node->getTag() == BIRD_A_TAG){
            auto action = Sequence::create(ScaleTo::create(0.2f, 0, 1, 1), CallFuncN::create(CC_CALLBACK_1(GameSceneTouchLayer::garbageCollection, this)), NULL);
            other_node->runAction(action);
            addBatteryPower(bird_node);
        }
        else{
            birdDead(2, bird_node);
        }
    }
    else if( other_node->getTag() == LIGHTNING_B_TAG){
        if( bird_node->getTag() == BIRD_B_TAG){
            auto action = Sequence::create(ScaleTo::create(0.2f, 0, 1, 1), CallFuncN::create(CC_CALLBACK_1(GameSceneTouchLayer::garbageCollection, this)), NULL);
            other_node->runAction(action);

            addBatteryPower(bird_node);
        }
        else{
            birdDead(2, bird_node);
        }
    }
    // 如果是砖头
    else{
        birdDead(1, bird_node);
    }


    return true;
}

void GameSceneTouchLayer::birdDead(int type, BirdSprite * bird){
    switch (type) {
        case 1:
            Director::getInstance()->getEventDispatcher()->pauseEventListenersForTarget(this);
            bird_A->stopAllActions();
            bird_B->stopAllActions();
            unscheduleAllCallbacks();
            bird->becomeFlying();
            break;
        // 触电死
        case 2:
//            setTouchEnabled(false);
            Director::getInstance()->getEventDispatcher()->pauseEventListenersForTarget(this);
            bird_A->stopAllActions();
            bird_B->stopAllActions();
            unscheduleAllCallbacks();
            Director::getInstance()->getRunningScene()->getPhysicsWorld()->setSpeed(0);
            bird->becomeElectricShock();
            break;
        default:
            break;
    }
}

void GameSceneTouchLayer::addBatteryPower(BirdSprite *bird){
    // 创建粒子
    ParticleSystemQuad *particle = ParticleSystemQuad::create("Particles/Phoenix.plist");
    particle->setPosition(bird->getPosition());
    particle->setDuration(1.0f);
    addChild(particle);
    
    // 创建粒子移动轨迹（飞向电池）
    ccBezierConfig config;
    config.endPosition = battery->getPosition();
    config.controlPoint_1 = Vec2(0, bird->getPosition().y);
    config.controlPoint_2 = Vec2(0, Director::getInstance()->getVisibleSize().height);
    ActionInterval* bezier = BezierTo::create(1.0f, config);
    auto addPower = [&]{
        if( battery->getCondition() == 3)
            return;
        if( battery->nextCondition() == 3){
            battery->runAction(RepeatForever::create(Blink::create(1.0f, 2)));
        }
    };
    auto particle_action = Sequence::create(bezier, DelayTime::create(1.5f),  CallFunc::create(addPower), NULL);
    particle->runAction(particle_action);
    
}

void GameSceneTouchLayer::enterSuperMode(){
    Director::getInstance()->getEventDispatcher()->pauseEventListenersForTarget(this);

    bird_A->becomeSuperBird();
    bird_B->becomeSuperBird();
    barrier_speed = SUPER_SPEED;
    unscheduleAllCallbacks();
    score_unit = 4;
    schedule(schedule_selector(GameSceneTouchLayer::createBarrier), 0.75f);
    scheduleUpdate();
    scheduleOnce(schedule_selector(GameSceneTouchLayer::quitSuperMode), 10.0f);
}


void GameSceneTouchLayer::quitSuperMode(float dt){
    battery->nextCondition();
    barrier_speed = NORMAL_SPEED;
    unscheduleAllCallbacks();
    score_unit = 1;
    schedule(schedule_selector(GameSceneTouchLayer::createBarrier), 3.0f);
    scheduleUpdate();
    
    bird_A->becomeNormalBird();
    bird_B->becomeNormalBird();
    Director::getInstance()->getEventDispatcher()->resumeEventListenersForTarget(this);
}

void GameSceneTouchLayer::createBarrier(float dt)
{
    int randomType = CCRANDOM_0_1() * 100 + 1;
    if (randomType < 40)
    {
//        BrickSprite *barrier = BrickSprite::createWithType(1);
//        barrier_vector.pushBack(barrier);
//        addChild(barrier, 30);
        LightningSprite *lightning = LightningSprite::create();
        barrier_vector.pushBack(lightning);
        addChild(lightning, 30);
    }
    else if(randomType < 80){
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
    Size visibleSize = Director::getInstance()->getVisibleSize();

    score += score_unit;
    GameScene::shareGameScene()->menuLayer->setScore(score);
    
    if(background_copy ->getPosition().y >= 0)
    {
        background->setPositionY(background->getPosition().y  - barrier_speed);
        background_copy->setPositionY(background_copy->getPosition().y  - barrier_speed);
        
    }
    else{
        background->setPositionY(0);
        background_copy->setPositionY(background->getContentSize().height - 1);
    }
    
    for(auto barrier : barrier_vector)
    {
        barrier->setPositionY(barrier->getPosition().y  - barrier_speed);
        if(barrier->getPosition().y < -barrier->getContentSize().height){
            garbageCollection(barrier);
        }
    }
    
    streak_A->setPosition(getChildByTag(BIRD_A_TAG)->getPosition());
    streak_B->setPosition(getChildByTag(BIRD_B_TAG)->getPosition());
}



void GameSceneTouchLayer::garbageCollection(Ref *object){
    Sprite *sprite = (Sprite*)object;

    if (sprite->getTag() >= BARRIER_TAG)
    {
        barrier_vector.eraseObject(sprite);
        this->removeChild(sprite,true);
        CCLOG("clean object");

    }
}


bool GameSceneTouchLayer::onTouchBegan(Touch* touch, Event  *event)
{
//    CCLOG("TouchTest onTouchBegan");
    auto location = touch->getLocation();
    Rect battery_rect = battery->getBoundingBox();
    if (battery_rect.containsPoint(location))
    {
        if(battery->getCondition() == 3){
            battery->stopAllActions();
            battery->setVisible(true);
            enterSuperMode();
        }
        return true;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    if (location.x <= visibleSize.width / 2){
        CCLOG("left span");
        direction = -1;
    }
    else{
        CCLOG("right span");
        direction = 1;
    }
    bird_A->spin(direction);
    bird_B->spin(direction);

    return true;
}

void GameSceneTouchLayer::onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *event){
//    CCLOG("TouchTest onTouchesEnded");
    bird_A->stopAllActions();
    bird_B->stopAllActions();
}