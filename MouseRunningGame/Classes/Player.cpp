#include "Player.h"
#include "./../proj.win32/CollManager.h"
#include "./../proj.win32/StartGroundLayer.h"
#include "./../proj.win32/FootBoard.h"
#include "./../proj.win32/GameLayer.h"
#include "./../proj.win32/GameItem.h"
#include "./../proj.win32/SoundManager.h"

bool Player::init()
{
	char spritePath[100];

	m_previouseFootBoard = NULL;
	m_color = BLUE;
	m_playerState = STOP;

	m_dropSpeed = 0;
	m_jumpCount = 2;

	m_player = Sprite::create(StringUtils::format("./blueMouse/blue7.png"));
	m_player->setAnchorPoint(Vec2(0, 0));
	m_player->setPosition(Vec2(100, 100));

	this->addChild(m_player);

	return true;
}

void Player::onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event)
{
	m_animation = Animation::create();
	m_animation->setDelayPerUnit(0.1f);

	switch (keyCode)
	{
	case EventKeyboard::KeyCode::KEY_L:
		m_color = BLUE;

		if (m_playerState == JUMP)
		{
			m_player->setTexture("./blueMouse/blue2.png");
		}
		else
		{
			for (size_t i = 0; i < 6; i++)
			{
				m_animation->addSpriteFrameWithFile(StringUtils::format("./blueMouse/blue%d.png", i + 1));
			}
			m_animate->setAnimation(m_animation);
		}
		break;

	case EventKeyboard::KeyCode::KEY_J:
		m_color = PINK;
		if (m_playerState == JUMP)
		{
			m_player->setTexture("./pinkMouse/pink2.png");
		}
		else
		{
			for (size_t i = 0; i < 6; i++)
			{
				m_animation->addSpriteFrameWithFile(StringUtils::format("./pinkMouse/pink%d.png", i + 1));
			}
			m_animate->setAnimation(m_animation);
		}
		break;

	case EventKeyboard::KeyCode::KEY_K:
		m_color = GREEN;
		if (m_playerState == JUMP)
		{
			m_player->setTexture("./greenMouse/green2.png");
		}
		else
		{
			for (size_t i = 0; i < 6; i++)
			{
				m_animation->addSpriteFrameWithFile(StringUtils::format("./greenMouse/green%d.png", i + 1));
			}
			m_animate->setAnimation(m_animation);
		}
		break;

	case EventKeyboard::KeyCode::KEY_A:
		if (m_jumpCount == 0)
		{
			break;
		}

		SoundManager::GetInstance()->PlayEffect(3);
		m_playerState = JUMP;
		m_dropSpeed = m_jumpSpeed;
		if (m_jumpCount == 2)
		{
			m_player->stopAction(m_animateRepeat);
		}
		m_jumpCount--;

		switch (m_color)
		{
		case Player::BLUE:
			m_player->setTexture("./blueMouse/blue2.png");
			break;
		case Player::PINK:
			m_player->setTexture("./pinkMouse/pink2.png");
			break;
		case Player::GREEN:
			m_player->setTexture("./greenMouse/green2.png");
			break;
		default:
			break;
		}

		break;

	default:
		break;
	}
}



void Player::SetJumpEnd()
{
	m_playerState = RUN;
	m_jumpCount = 2;

	m_animation = Animation::create();
	m_animation->setDelayPerUnit(0.1f);

	switch (m_color)
	{
	case BLUE:
		for (size_t i = 0; i < 6; i++)
		{
			m_animation->addSpriteFrameWithFile(StringUtils::format("./blueMouse/blue%d.png", i + 1));
		}
		break;

	case PINK:
		for (size_t i = 0; i < 6; i++)
		{
			m_animation->addSpriteFrameWithFile(StringUtils::format("./pinkMouse/pink%d.png", i + 1));
		}
		break;

	case GREEN:
		for (size_t i = 0; i < 6; i++)
		{
			m_animation->addSpriteFrameWithFile(StringUtils::format("./greenMouse/green%d.png", i + 1));
		}
		break;
	default:
		break;
	}

	m_animate = Animate::create(m_animation);
	m_animate->setAnimation(m_animation);

	m_animateRepeat = RepeatForever::create(m_animate);
	m_player->runAction(m_animateRepeat);
}

void Player::updatePlayer(float dt)
{
	int yOffset = 0;
	FootBoard** FootBoardtemp = NULL;
	GameItem** gameItemTemp = NULL;

	Rect playerRect;
	GetPlayerCollRect(&playerRect);

	switch (m_playerState)
	{
	case Player::STOP:
		break;

	case Player::RUN:
	{
		m_dropSpeed -= m_dropincreaseSpeed * dt;

		if (m_dropSpeed < -700)
		{
			m_dropSpeed = -700;
		}

		m_player->setPositionY(m_player->getPositionY() + m_dropSpeed * dt);

		if (CollManager::GetInstance()->GetGround() != NULL)
		{
			if (CollManager::GetInstance()->GetGround()->CheckColl(m_player->getBoundingBox(), &yOffset))
			{
				m_player->setPositionY(m_player->getPositionY() + yOffset);
			}
		}

		FootBoardtemp = CollManager::GetInstance()->GetFootBoards();
		bool isSameColor = false;
		for (size_t i = 0; i < 8; i++)
		{
			if (FootBoardtemp[i]->CheckColl(playerRect, &yOffset, m_color, &isSameColor))
			{
				m_player->setPositionY(m_player->getPositionY() + yOffset);

				if (m_previouseFootBoard != FootBoardtemp[i])
				{
					SoundManager::GetInstance()->PlayEffect(4);
					m_previouseFootBoard = FootBoardtemp[i];
					if (isSameColor)
					{
						m_pGameLayer->IncreaseTimer(2.0f);
					}
					else
					{
						m_pGameLayer->DecreaseTimer(5.0f);
					}
				}
			}
		}

		gameItemTemp = CollManager::GetInstance()->GetGameItems();
		for (size_t i = 0; i < 20; i++)
		{
			if (gameItemTemp[i]->CheckColl(playerRect))
			{
				SoundManager::GetInstance()->PlayEffect(2);
				m_pGameLayer->IncreaseScore(100);
			}
		}

		if (m_player->getPositionY() < 50)
		{
			m_player->setPositionY(m_player->getPositionY() + (50 - m_player->getPositionY()));
			Kill();
		}
	}
		break;

	case Player::JUMP:
	{
		bool isSameColor = false;

		m_dropSpeed -= m_dropincreaseSpeed * dt;

		m_player->setPositionY(m_player->getPositionY() + m_dropSpeed * dt);

		if (CollManager::GetInstance()->GetGround() != NULL)
		{
			if (CollManager::GetInstance()->GetGround()->CheckColl(m_player->getBoundingBox(), &yOffset))
			{
				SoundManager::GetInstance()->PlayEffect(4);
				m_player->setPositionY(m_player->getPositionY() + yOffset);
				SetJumpEnd();
			}
		}

		if (m_dropSpeed < 0)
		{
			FootBoardtemp = CollManager::GetInstance()->GetFootBoards();
			for (size_t i = 0; i < 8; i++)
			{
				if (FootBoardtemp[i]->CheckColl(playerRect, &yOffset, m_color, &isSameColor))
				{
					SoundManager::GetInstance()->PlayEffect(4);
					m_player->setPositionY(m_player->getPositionY() + yOffset);
					SetJumpEnd();
				}
			}
		}

		gameItemTemp = CollManager::GetInstance()->GetGameItems();
		for (size_t i = 0; i < 20; i++)
		{
			if (gameItemTemp[i]->CheckColl(playerRect))
			{
				SoundManager::GetInstance()->PlayEffect(2);
				m_pGameLayer->IncreaseScore(100);
			}
		}

		if (m_player->getPositionY() < 50)
		{
			m_player->setPositionY(m_player->getPositionY() + (50 - m_player->getPositionY()));
			Kill();
		}
	}
		break;

	case Player::DEAD:
		break;
	default:
		break;
	}
} 

void Player::GetPlayerCollRect(Rect* pRect)
{
	Rect rect = m_player->getBoundingBox();
	pRect->setRect(rect.getMinX() + 15, rect.getMinY() - 2, 90, 140);
}

void Player::setGameLayer(GameLayer* gameLayer)
{
	m_pGameLayer = gameLayer;
}

void Player::Kill()
{
	m_playerState = DEAD;

	m_player->stopAction(m_animateRepeat);

	m_pGameLayer->SetGameOver();

	switch (m_color)
	{
	case Player::BLUE:
		m_player->setTexture("./blueMouse/blue8.png");
		break;
	case Player::PINK:
		m_player->setTexture("./pinkMouse/pink8.png");
		break;
	case Player::GREEN:
		m_player->setTexture("./greenMouse/green8.png");
		break;
	default:
		break;
	}
}

void Player::GameStart()
{
	m_playerState = RUN;

	m_animation = Animation::create();
	m_animation->setDelayPerUnit(0.1f);

	for (size_t i = 0; i < 6; i++)
	{
		m_animation->addSpriteFrameWithFile(StringUtils::format("./blueMouse/blue%d.png", i + 1));
	}

	m_animate = Animate::create(m_animation);
	m_animateRepeat = RepeatForever::create(m_animate);
	m_player->runAction(m_animateRepeat);
}

Player::Player()
{
}


Player::~Player()
{
}
