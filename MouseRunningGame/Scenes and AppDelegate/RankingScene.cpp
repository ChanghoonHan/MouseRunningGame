#include "RankingScene.h"
#include "./../../proj.win32/RankingLayer.h"

USING_NS_CC;

Scene* RankingScene::createScene()
{
    return RankingScene::create();
}

// on "init" you need to initialize your instance
bool RankingScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Scene::init() )
    {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

	RankingLayer* pRankingLayer = RankingLayer::create();

	this->addChild(pRankingLayer);

    return true;
}