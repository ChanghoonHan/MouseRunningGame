#include "RankingLayer.h"
#include "./../../proj.win32/BackgroundLayer.h"
#include "./../../proj.win32/ScoreBoard.h"
#include "./../../proj.win32/SoundManager.h"
#include "MenuScene.h"

bool RankingLayer::init()
{
	m_visibleSize = Director::getInstance()->getVisibleSize();

	Sprite* rankingText = Sprite::create("MenuSceneSprite/RankingButton1.png");
	rankingText->setPosition(Vec2(m_visibleSize.width / 2, m_visibleSize.height - 100));
	addChild(rankingText, 1);

	InitLayers();
	int tempSpeed = 0;

	for (size_t i = 0; i < 7; i++)
	{
		tempSpeed = 100 - ((7 - i) * 10);
		if (tempSpeed > 0)
		{
			m_backgroundLayer[i]->setSpeed(tempSpeed);
		}
		else
		{
			m_backgroundLayer[i]->setSpeed(0);
		}
	}

	ScoreBoard::GetInstance()->Print(Vec2(m_visibleSize.width / 2, m_visibleSize.height / 2), this);

	MenuItemImage* homeMenuItem = MenuItemImage::create
	(
		"./Ranking/HomeButton1.png",
		"./Ranking/HomeButton2.png",
		CC_CALLBACK_1(RankingLayer::SceneChangeToHome, this)
	);
	Menu* homeButton = Menu::createWithItem(homeMenuItem);
	homeButton->setPosition(Vec2(m_visibleSize.width / 2, 100));
	addChild(homeButton, 1);

	scheduleUpdate();

	return true;
}

void RankingLayer::update(float deltaTime)
{
	for (size_t i = 0; i < 7; i++)
	{
		m_backgroundLayer[i]->updateBackGround(deltaTime);
	}
}

void RankingLayer::InitLayers()
{
	for (size_t i = 0; i < 7; i++)
	{
		m_backgroundLayer[i] = BackgroundLayer::create();
		m_backgroundLayer[i]->setSpeed(0);
		m_backgroundLayer[i]->setSprite(StringUtils::format("back%d.png", i + 1));
		addChild(m_backgroundLayer[i], -7 + i);
	}
}

void RankingLayer::SceneChangeToHome(Ref* sender)
{
	SoundManager::GetInstance()->PlayEffect(1);
	Director::getInstance()->replaceScene(TransitionPageTurn::create(1, MenuScene::create(), true));
}

RankingLayer::RankingLayer()
{
}


RankingLayer::~RankingLayer()
{
}
