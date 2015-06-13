#include "GameScene.h"
#include "CircleAction.h"
#include "GameSceneTouchLayer.h"
#include "SceneManager.h"
USING_NS_CC;

//Scene* GameScene::createScene()
//{
//    // 'scene' is an autorelease object
//    auto scene = Scene::createWithPhysics();
//    scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
//    scene->getPhysicsWorld()->setGravity(cocos2d::Vect(0,0));
//    // 'layer' is an autorelease object
//    auto layer = GameScene::create();
//    // add layer as a child to scene
//    scene->addChild(layer);
//    
//    // return the scene
//    return scene;
//}

static GameScene *_sharedGameScene = NULL;
GameScene* GameScene::shareGameScene()
{
    if(!_sharedGameScene){
        _sharedGameScene = new GameScene();
        if (_sharedGameScene && _sharedGameScene->initWithPhysics())
        {
//            _sharedGameScene->autorelease();
            _sharedGameScene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
            _sharedGameScene->getPhysicsWorld()->setGravity(cocos2d::Vect(0,0));
            
            _sharedGameScene->initLayer();
        }
        

    }

    return _sharedGameScene;
}

void GameScene::initLayer(){
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    

    gameLayer = GameSceneTouchLayer::create();
    gameLayer->setContentSize(Size(visibleSize.width, visibleSize.height));
    gameLayer->setPosition(Point(0, 0));
    _sharedGameScene->addChild(gameLayer, 10);
    
    menuLayer = GameMenuLayer::create();
    menuLayer->setContentSize(Size(visibleSize.width, visibleSize.height));
    menuLayer->setPosition(Point(0, 0));
    _sharedGameScene->addChild(menuLayer, 12);
    
    backgroundLayer = GameBackgroundLayer::create();
    backgroundLayer->setContentSize(Size(visibleSize.width, visibleSize.height));
    backgroundLayer->setPosition(Point(0, 0));
    _sharedGameScene->addChild(backgroundLayer, 0);
    
    NotificationCenter::getInstance()->addObserver(this, callfuncO_selector(GameScene::gameOver), "gameover", NULL);
}

void GameScene::reset(){
    NotificationCenter::getInstance()->removeObserver(this, "gameover");
    removeAllChildrenWithCleanup(true);
    _sharedGameScene = NULL;
}

void GameScene::gameOver(Ref* sender){
    UserDefault::getInstance()->setIntegerForKey("current_score", gameLayer->score);
    SceneManager::sharedSceneManager()->changeScene(SceneManager::en_GameoverScene);


}
