#include "StartGroundLayer.h"

bool StartGroundLayer::init()
{
	m_speed = 0;
	m_visibleSize = Director::getInstance()->getVisibleSize();

	m_groundSprite = Sprite::create("./Resource/back7.png");
	m_groundSprite->setScale(0.75);
	m_groundSprite->setAnchorPoint(Vec2(0, 0));
	m_groundSprite->setPosition(Vec2(0, 0));
	this->addChild(m_groundSprite);

	return true;
}

void StartGroundLayer::updateGround(float deltaTime)
{
	float xPos = m_groundSprite->getPositionX() - m_speed * deltaTime;
	m_groundSprite->setPosition(Vec2(xPos, 0));
}

bool StartGroundLayer::isEndOfScreen()
{
	int xPos = m_groundSprite->getPositionX();
	if (xPos < -m_visibleSize.width)
	{
		return true;
	}

	return false;
}

void StartGroundLayer::setSpeed(float speed)
{
	m_speed = speed;
}

bool StartGroundLayer::CheckColl(Rect& rect, int* offsetTemp)
{
	Rect myRect = Rect(m_groundSprite->getPositionX(), 0, 1440, 100);
	if (myRect.intersectsRect(rect))
	{
		*offsetTemp = myRect.getMaxY() - rect.getMinY();
		return true;
	}

	*offsetTemp = -1;
	return false;
}

StartGroundLayer::StartGroundLayer()
{
}


StartGroundLayer::~StartGroundLayer()
{
}
