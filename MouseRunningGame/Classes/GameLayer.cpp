#include "GameLayer.h"
#include "./../proj.win32/FootBoard.h"
#include "./../proj.win32/BackgroundLayer.h"
#include "./../proj.win32/StartGroundLayer.h"
#include "./../proj.win32/EnemyLayer.h"
#include "./../proj.win32/Player.h"
#include "./../proj.win32/CollManager.h"
#include "./../proj.win32/ScoreBoard.h"
#include "./../proj.win32/GameItem.h"
#include "./../proj.win32/SoundManager.h"
#include "GameScene.h"
#include "MenuScene.h"

bool GameLayer::init()
{
	m_gameState = READY;

	SoundManager::GetInstance()->PlayBgm(2);

	m_visibleSize = Director::getInstance()->getVisibleSize();

	m_newRecord = false;

	m_score = 0;
	m_hightScore = ScoreBoard::GetInstance()->GetHightScore();

	m_scoreTimer = 0;
	m_increaseScore = 10;

	m_level = 0;

	CollManager::GetInstance()->Init();
	m_Timer = 30;

	m_timerBarCase[0] = Sprite::create("./Resource/timerBarCaseBottom.png");
	m_timerBarCase[0]->setAnchorPoint(Vec2(0, 1));
	m_timerBarCase[0]->setPosition(Vec2(0, m_visibleSize.height));
	addChild(m_timerBarCase[0], 3);

	m_timerBar = Sprite::create("./Resource/timerBar.png");
	m_timerBar->setAnchorPoint(Vec2(0, 1));
	m_timerBar->setPosition(Vec2(43, m_visibleSize.height));
	addChild(m_timerBar, 3);

	m_timerBarCase[1] = Sprite::create("./Resource/timerBarCaseTop.png");
	m_timerBarCase[1]->setAnchorPoint(Vec2(0, 1));
	m_timerBarCase[1]->setPosition(Vec2(0, m_visibleSize.height));
	addChild(m_timerBarCase[1], 3);

	m_gameStartSprite = Sprite::create("./Ranking/Ready.png");
	SoundManager::GetInstance()->PlayEffect(6);
	m_gameStartSprite->setPosition(Vec2(m_visibleSize.width / 2, m_visibleSize.height / 2));
	addChild(m_gameStartSprite, 3);
	ScaleBy* gameTextScaleToBig = ScaleBy::create(0.5, 2.0);
	ScaleBy* gameTextScaleToSmall = ScaleBy::create(0.5, 0.0);
	CallFunc* gameTextChangeFunc = CallFunc::create(CC_CALLBACK_0(GameLayer::changeGameStartText, this));
	ScaleTo* startTextScaleToBig = ScaleTo::create(0.5, 2.0);
	CallFunc* chageGameStateToGameFunc = CallFunc::create(CC_CALLBACK_0(GameLayer::changeGameStateToGame, this));
	Sequence* gameTextSequence = Sequence::create(gameTextScaleToBig, gameTextScaleToSmall, gameTextChangeFunc, startTextScaleToBig, chageGameStateToGameFunc, NULL);
	
	m_gameStartSprite->runAction(gameTextSequence);

	m_scoreLabel = Label::create(StringUtils::format("Score         : %08d", m_score), "fonts/koverwatch.ttf", 50);
	m_scoreLabel->setAnchorPoint(Vec2(1, 1));
	m_scoreLabel->setPosition(Vec2(m_visibleSize.width - 10, m_visibleSize.height - 60));
	addChild(m_scoreLabel, 3);

	m_highScoreLabel = Label::create(StringUtils::format("High Score : %08d", m_hightScore), "fonts/koverwatch.ttf", 50);
	m_highScoreLabel->setAnchorPoint(Vec2(1, 1));
	m_highScoreLabel->setPosition(Vec2(m_visibleSize.width - 10, m_visibleSize.height - 10));
	addChild(m_highScoreLabel, 3);

	for (size_t i = 0; i < 8; i++)
	{
		m_foodboard[i] = FootBoard::create();
		m_foodboard[i]->setPosition(Vec2(0, 0));
		addChild(m_foodboard[i], 1);
	}

	for (size_t i = 0; i < 20; i++)
	{
		m_gameItem[i] = GameItem::create();
		m_gameItem[i]->setPosition(Vec2(0, 0));
		addChild(m_gameItem[i], 1);
	}

	CollManager::GetInstance()->SetFootBoards(m_foodboard);
	m_foodboard[0]->move();
	m_foodboard[0]->setBoardPosY(200);

	CollManager::GetInstance()->SetGameItems(m_gameItem);
	m_gameItem[0]->move();
	m_gameItem[0]->setBoardPosY(400);
	
	m_player = Player::create();
	m_player->setGameLayer(this);
	addChild(m_player, 2);

	m_gameSpeed = 300;

	InitLayers();

	SetLayersSpeed();

	auto keyboardListner = EventListenerKeyboard::create();
	keyboardListner->onKeyPressed = CC_CALLBACK_2(GameLayer::onKeyPressed, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(keyboardListner, this);

	scheduleUpdate();
	return true;
}

void GameLayer::update(float deltaTime)
{
	SetLayersSpeed();

	switch (m_gameState)
	{
	case GameLayer::READY:

		break;

	case GameLayer::GAMEOVERREADY:
		m_player->updatePlayer(deltaTime);
		break;

	case GameLayer::GAMEOVER:
		m_player->updatePlayer(deltaTime);
		break;

	case GameLayer::GAME:
		m_scoreTimer += deltaTime;
		if (m_scoreTimer > 1)
		{
			m_scoreTimer = 0;
			IncreaseScore(m_increaseScore);
		}

		m_Timer -= deltaTime;
		if (m_Timer < 0)
		{
			m_Timer = 0;
			SetGameOver();
			m_player->Kill();
		}
		m_timerBar->setTextureRect(Rect(0, 0, 745 * (m_Timer / MAX_TIMER), 70));


		if (m_startGroundLayer != NULL)
		{
			m_startGroundLayer->updateGround(deltaTime);

			if (m_startGroundLayer->isEndOfScreen())
			{
				removeChild(m_startGroundLayer);
				m_startGroundLayer = NULL;
				CollManager::GetInstance()->EndGround();
			}
		}

		for (size_t i = 0; i < 8; i++)
		{
			m_foodboard[i]->updateBoard(deltaTime);

			if (m_foodboard[i]->getBoardPosX() < m_visibleSize.width - 300 - (m_gameSpeed - 300))
			{
				m_foodboard[(i + 1) % 8]->move();
			}
		}

		for (size_t i = 0; i < 20; i++)
		{
			m_gameItem[i]->updateBoard(deltaTime);

			if (m_gameItem[i]->getBoardPosX() < m_visibleSize.width - 150 - (m_gameSpeed - 100))
			{
				m_gameItem[(i + 1) % 20]->move();
			}
		}

		m_enemyLayer->updateGround(deltaTime);

		m_player->updatePlayer(deltaTime);

		for (size_t i = 0; i < 6; i++)
		{
			m_backgroundLayer[i]->updateBackGround(deltaTime);
		}
		break;

	default:
		break;
	}
}

void GameLayer::IncreaseScore(int score)
{
	m_score += score;

	if (m_score > m_hightScore)
	{
		m_hightScore = m_score;
		m_newRecord = true;
	}

	if (m_level < m_score / 2000)
	{
		m_level = m_score / 2000;
		m_gameSpeed += 50;
		if (m_gameSpeed > 700)
		{
			m_gameSpeed = 700;
		}
		m_increaseScore += 5;
	}

	m_scoreLabel->setString(StringUtils::format("Score         : %08d", m_score));
	m_highScoreLabel->setString(StringUtils::format("High Score : %08d", m_hightScore));
}

void GameLayer::InitLayers()
{
	for (size_t i = 0; i < 6; i++)
	{
		m_backgroundLayer[i] = BackgroundLayer::create();
		m_backgroundLayer[i]->setSpeed(0);
		m_backgroundLayer[i]->setSprite(StringUtils::format("back%d.png", i + 1));
		addChild(m_backgroundLayer[i], -7 + i);
	}

	m_startGroundLayer = StartGroundLayer::create();
	addChild(m_startGroundLayer, 0);

	CollManager::GetInstance()->SetGround(m_startGroundLayer);

	m_enemyLayer = EnemyLayer::create();
	addChild(m_enemyLayer, 0);
	CollManager::GetInstance()->SetEnemy(m_enemyLayer);
}

void GameLayer::SetLayersSpeed()
{
	int tempSpeed = 0;

	for (size_t i = 0; i < 6; i++)
	{
		tempSpeed = m_gameSpeed - ((6 - i) * 120);
		if (tempSpeed > 0)
		{
			m_backgroundLayer[i]->setSpeed(tempSpeed);
		}
		else
		{
			m_backgroundLayer[i]->setSpeed(0);
		}
	}

	m_enemyLayer->setSpeed(m_gameSpeed);

	if (m_startGroundLayer != NULL)
	{
		m_startGroundLayer->setSpeed(m_gameSpeed);
	}

	for (size_t i = 0; i < 8; i++)
	{
		m_foodboard[i]->setSpeed(m_gameSpeed);
	}

	for (size_t i = 0; i < 20; i++)
	{
		m_gameItem[i]->setSpeed(m_gameSpeed - 50);
	}
}

void GameLayer::IncreaseTimer(float time)
{
	m_Timer += time;
	if (m_Timer > MAX_TIMER)
	{
		m_Timer = MAX_TIMER;
	}
}

void GameLayer::DecreaseTimer(float time)
{
	m_Timer -= time;
}

void GameLayer::onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event)
{
	switch (m_gameState)
	{
	case GameLayer::READY:
		break;
	case GameLayer::GAME:
		m_player->onKeyPressed(keyCode, event);
		break;
	case GameLayer::GAMEOVERREADY:
		break;
	case GameLayer::GAMEOVER:
		break;
	default:
		break;
	}
}

void GameLayer::SetGameOver()
{
	m_gameState = GAMEOVERREADY;

	ScoreBoard::GetInstance()->SetScore(m_score);
	SoundManager::GetInstance()->PlayEffect(5);
	m_gameOverSprite = Sprite::create("./Ranking/GameOver.png");
	m_gameOverSprite->setPosition(Vec2(m_visibleSize.width / 2, m_visibleSize.height / 2 + 320));
	addChild(m_gameOverSprite, 3);
	m_gameOverSprite->setScale(0.6);
	ScaleBy* gameTextScaleToBig = ScaleBy::create(1, 1.5);
	CallFunc* SetGameStateToGameOverFunc = CallFunc::create(CC_CALLBACK_0(GameLayer::SetGameStateToGameOver, this));
	Sequence* gameTextSequence = Sequence::create(gameTextScaleToBig, SetGameStateToGameOverFunc, NULL);
	m_gameOverSprite->runAction(gameTextSequence);
}

void GameLayer::SetGameStateToGameOver()
{
	ScoreBoard::GetInstance()->Print(Vec2(m_visibleSize.width / 2, m_visibleSize.height / 2), this);

	MenuItemImage* restartMenuItem = MenuItemImage::create
	(
		"./Ranking/RestartButton1.png",
		"./Ranking/RestartButton2.png",
		CC_CALLBACK_1(GameLayer::RestartGame, this)
	);
	Menu* restartGameButton = Menu::createWithItem(restartMenuItem);
	restartGameButton->setPosition(Vec2(m_visibleSize.width / 2 - 120, 100));
	addChild(restartGameButton, 5);

	MenuItemImage* homeMenuItem = MenuItemImage::create
	(
		"./Ranking/HomeButton1.png",
		"./Ranking/HomeButton2.png",
		CC_CALLBACK_1(GameLayer::SceneChangeToHome, this)
	);
	Menu* homeButton = Menu::createWithItem(homeMenuItem);
	homeButton->setPosition(Vec2(m_visibleSize.width / 2 + 150, 100));
	addChild(homeButton, 5);

	m_gameState = GAMEOVER;
}

void GameLayer::RestartGame(Ref* sender)
{

	Director::getInstance()->replaceScene(GameScene::create());
}

void GameLayer::SceneChangeToHome(Ref* sender)
{
	SoundManager::GetInstance()->PlayEffect(1);
	Director::getInstance()->replaceScene(TransitionPageTurn::create(1, MenuScene::create(), true));
}

void GameLayer::changeGameStateToGame()
{
	m_gameState = GAME;
	removeChild(m_gameStartSprite);
	m_player->GameStart();
}

void GameLayer::changeGameStartText()
{
	m_gameStartSprite->setTexture("./Ranking/Run.png");
}

GameLayer::GameLayer()
{

}

GameLayer::~GameLayer()
{
	
}
