#include "MenuScene.h"
#include "SimpleAudioEngine.h"
#include "GameScene.h"
#include "../../proj.win32/MenuLayer.h"

USING_NS_CC;

Scene* MenuScene::createScene()
{
    return MenuScene::create();
}

// on "init" you need to initialize your instance
bool MenuScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Scene::init() )
    {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

	MenuLayer* pMenuLayer = MenuLayer::create();

	this->addChild(pMenuLayer);

    return true;
}