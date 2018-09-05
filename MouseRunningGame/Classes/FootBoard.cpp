#include "FootBoard.h"

bool FootBoard::init()
{
	m_visibleSize = Director::getInstance()->getVisibleSize();
	m_footBoardSprite = NULL;
	int randTemp = random() % 3;
	switch (randTemp)
	{
	case 0:
		m_boardColor = GREEN;
		m_footBoardSprite = Sprite::create("Resource/footboardGreen.png");
		break;
	case 1:
		m_boardColor = BLUE;
		m_footBoardSprite = Sprite::create("Resource/footboardBlue.png");
		break;
	case 2:
		m_boardColor = PINK;
		m_footBoardSprite = Sprite::create("Resource/footboardPink.png");
		break;
	default:
		break;
	}

	m_footBoardSprite->setScaleY(0.75);
	m_footBoardSprite->setAnchorPoint(Vec2(0, 0));
	
	randTemp = random(150, 550);

	m_footBoardSprite->setPosition(Vec2(m_visibleSize.width + 200, randTemp));
	addChild(m_footBoardSprite);
	m_speed = 0;
	m_isMove = false;

	return true;
}

bool FootBoard::initPos()
{
	int randTemp = random() % 3;
	switch (randTemp)
	{
	case 0:
		m_boardColor = GREEN;
		m_footBoardSprite->setTexture("Resource/footboardGreen.png");
		break;
	case 1:
		m_boardColor = BLUE;
		m_footBoardSprite->setTexture("Resource/footboardBlue.png");
		break;
	case 2:
		m_boardColor = PINK;
		m_footBoardSprite->setTexture("Resource/footboardPink.png");
		break;
	default:
		break;
	}

	randTemp = random(150, 550);

	m_footBoardSprite->setPosition(Vec2(m_visibleSize.width + 200, randTemp));
	m_speed = 0;
	m_isMove = false;

	return true;
}

Rect FootBoard::getSpriteBoundingBox()
{
	Rect rect = m_footBoardSprite->getBoundingBox();
	rect.origin += getPosition();
	return rect;
}

void FootBoard::updateBoard(float dt)
{
	if (m_isMove)
	{
		m_footBoardSprite->setPositionX(m_footBoardSprite->getPositionX() - m_speed * dt);
		if (m_footBoardSprite->getPositionX() < -400)
		{
			initPos();
		}
	}
}

void FootBoard::setBoardPosY(int y = 0)
{
	m_footBoardSprite->setPositionY(y);
}

void FootBoard::setSpeed(float speed)
{
	m_speed = speed;
}

void FootBoard::move()
{
	if (!m_isMove)
	{
		m_footBoardSprite->setPositionX(m_visibleSize.width + random(50, 350));
	}
	
	m_isMove = true;
}

float FootBoard::getBoardPosX()
{
	return m_footBoardSprite->getPositionX();
}

bool FootBoard::CheckColl(Rect& rect, int* offsetTemp, int color, bool* isSameColor)
{
	Rect myRect = m_footBoardSprite->getBoundingBox();
	if (myRect.intersectsRect(rect))
	{
		*offsetTemp = myRect.getMaxY() - rect.getMinY();
		if (*offsetTemp > 40)
		{
			*offsetTemp = -1;
			return false;
		}

		if (isSameColor != NULL)
		{
			if (color == m_boardColor)
			{
				*isSameColor = true;
			}
			else
			{
				*isSameColor = false;
			}
		}

		return true;
	}

	*offsetTemp = -1;
	return false;
}

FootBoard::FootBoard()
{
}


FootBoard::~FootBoard()
{
}
