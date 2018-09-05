#include "MenuLayer.h"
#include "../../proj.win32/BackgroundLayer.h"
#include "RankingScene.h"
#include "../../proj.win32/ScoreBoard.h"
#include "./../proj.win32/SoundManager.h"
#include "GameScene.h"

bool MenuLayer::init()
{
	m_visibleSize = Director::getInstance()->getVisibleSize();
	SoundManager::GetInstance()->PlayBgm(1);

	InitLayers();
	int tempSpeed = 0;
	m_mouseSpriteIdx = 0;
	m_mouseSpriteChangeTime = 0;

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

	m_mouseSprite = Sprite::create("./MenuSceneSprite/RedMouse.png");
	m_mouseSprite->setAnchorPoint(Vec2(0, 0));
	m_mouseSprite->setPosition(Vec2(0, 0));
	addChild(m_mouseSprite);

	m_titleSprite = Sprite::create("./MenuSceneSprite/title.png");
	m_titleSprite->setAnchorPoint(Vec2(1, 1));
	m_titleSprite->setPosition(Vec2(1440, 810));
	addChild(m_titleSprite);

	MenuItemImage* gameStartMenuItem = MenuItemImage::create
	(
		"./MenuSceneSprite/GameStartButton1.png",
		"./MenuSceneSprite/GameStartButton2.png",
		CC_CALLBACK_1(MenuLayer::ChageSceneToGameScene, this)
	);
	Menu* gameStartMenu = Menu::createWithItem(gameStartMenuItem);
	gameStartMenu->setPosition(Vec2(m_visibleSize.width - 395, m_visibleSize.height / 2 + 50));
	addChild(gameStartMenu);

	MenuItemImage* rankMenuItem = MenuItemImage::create
	(
		"./MenuSceneSprite/RankingButton1.png",
		"./MenuSceneSprite/RankingButton2.png",
		CC_CALLBACK_1(MenuLayer::ChageSceneToRankingScene, this)
	);
	Menu* rankMenu = Menu::createWithItem(rankMenuItem);
	rankMenu->setPosition(Vec2(m_visibleSize.width - 395, m_visibleSize.height / 2 - 80));
	addChild(rankMenu);

	MenuItemImage* quitMenuItem = MenuItemImage::create
	(
		"./MenuSceneSprite/QuitButton1.png",
		"./MenuSceneSprite/QuitButton2.png",
		CC_CALLBACK_1(MenuLayer::GameQuit, this)
	);
	Menu* quitMenu = Menu::createWithItem(quitMenuItem);
	quitMenu->setPosition(Vec2(m_visibleSize.width - 395, m_visibleSize.height / 2 - 210));
	addChild(quitMenu);

	scheduleUpdate();

	return true;
}

void MenuLayer::update(float deltaTime)
{
	m_mouseSpriteChangeTime += deltaTime;
	if (m_mouseSpriteChangeTime > 1)
	{
		m_mouseSpriteChangeTime = 0;
		m_mouseSpriteIdx = (m_mouseSpriteIdx + 1) % 3;
		switch (m_mouseSpriteIdx)
		{
		case 0:
			m_mouseSprite->setTexture("./MenuSceneSprite/RedMouse.png");
			break;
		case 1:
			m_mouseSprite->setTexture("./MenuSceneSprite/GreenMouse.png");
			break;
		case 2:
			m_mouseSprite->setTexture("./MenuSceneSprite/BlueMouse.png");
			break;
		default:
			break;
		}
	}

	for (size_t i = 0; i < 7; i++)
	{
		m_backgroundLayer[i]->updateBackGround(deltaTime);
	}
}

void MenuLayer::InitLayers()
{
	for (size_t i = 0; i < 7; i++)
	{
		m_backgroundLayer[i] = BackgroundLayer::create();
		m_backgroundLayer[i]->setSpeed(0);
		m_backgroundLayer[i]->setSprite(StringUtils::format("back%d.png", i + 1));
		addChild(m_backgroundLayer[i], -7 + i);
	}
}

void MenuLayer::ChageSceneToRankingScene(Ref* pSender)
{
	SoundManager::GetInstance()->PlayEffect(1);
	Director::getInstance()->replaceScene(TransitionPageTurn::create(1, RankingScene::create(), false));
}

void MenuLayer::ChageSceneToGameScene(Ref* pSender)
{
	SoundManager::GetInstance()->PlayEffect(1);
	Director::getInstance()->replaceScene(TransitionPageTurn::create(1, GameScene::create(), false));
}

void MenuLayer::GameQuit(Ref* pSender)
{
	Director::getInstance()->end();
}

MenuLayer::MenuLayer()
{
}


MenuLayer::~MenuLayer()
{
}
