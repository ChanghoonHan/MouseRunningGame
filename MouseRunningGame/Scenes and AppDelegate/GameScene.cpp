#include "GameScene.h"
#include "SimpleAudioEngine.h"
#include "../../proj.win32/GameLayer.h"

USING_NS_CC;

Scene* GameScene::createScene()
{
    return GameScene::create();
}

// on "init" you need to initialize your instance
bool GameScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Scene::init() )
    {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

	GameLayer* pGameLayer = GameLayer::create();

	this->addChild(pGameLayer);
    
    return true;
}