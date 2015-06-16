//
//  GameMenuLayer.cpp
//  fly_and_spin
//
//  Created by bin on 15/6/10.
//
//

#include "GameMenuLayer.h"
#include "GameScene.h"

bool GameMenuLayer::init()
{
    if(!Layer::init())
    {
        return false;
    }
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    scoreLabel = Label::createWithTTF("0", "fonts/Marker Felt.ttf", 40);
    scoreLabel->setPosition(Vec2(origin.x + visibleSize.width/2, origin.y + visibleSize.height - scoreLabel->getContentSize().height));
    scoreLabel->setString("0");
    addChild(scoreLabel, 1);

    Sprite * pause = Sprite::create("pause.png");
    pause->setScale(0.5f);
    pause->setPosition(Vec2(pause->getContentSize().width, visibleSize.height - pause->getContentSize().height / 2));
    addChild(pause, 10);

    auto listener = EventListenerTouchOneByOne::create();
    // 吞没事件，在 onTouchBegan 方法返回 true 时吞没
    listener->setSwallowTouches(true);
    
    listener->onTouchBegan = [](Touch* touch, Event* event){
        // 获取事件所绑定的 target
        auto target = static_cast<Sprite*>(event->getCurrentTarget());
        // 获取当前点击点所在相对按钮的位置坐标
        Point locationInNode = target->convertToNodeSpace(touch->getLocation());
        Size s = target->getContentSize();
        Rect rect = Rect(0, 0, s.width, s.height);
        // 点击范围判断检测
        if (rect.containsPoint(locationInNode))
        {
            GameScene::shareGameScene()->pauseGame();
            return true;
        }
        return false;
    };
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, pause);

    return true;
}

void GameMenuLayer::updateScore(int score){
    char char_score[8];
    sprintf(char_score, "%d", score);
    scoreLabel->setString(char_score);
}

