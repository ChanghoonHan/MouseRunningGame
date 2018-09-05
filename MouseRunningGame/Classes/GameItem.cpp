#include "GameItem.h"

bool GameItem::init()
{
	m_visibleSize = Director::getInstance()->getVisibleSize();
	m_ItemSprite = Sprite::create("Item/cheese1.png");

	m_ItemSprite->setAnchorPoint(Vec2(0, 0));
	m_ItemSprite->setScale(1.5);

	int randTemp = random(150, 550);

	Animation* cheeseAnimation = Animation::create();
	cheeseAnimation->addSpriteFrameWithFileName("Item/cheese1.png");
	cheeseAnimation->addSpriteFrameWithFileName("Item/cheese2.png");
	cheeseAnimation->setDelayPerUnit(0.2);
	Animate* cheesAnimate = Animate::create(cheeseAnimation);

	m_ItemSprite->runAction(RepeatForever::create(cheesAnimate));
	m_ItemSprite->setPosition(Vec2(m_visibleSize.width + 800, randTemp));
	addChild(m_ItemSprite);
	m_speed = 0;
	m_isMove = false;

	return true;
}

bool GameItem::initPos()
{
	int randTemp = random(400, 600);

	m_ItemSprite->setPosition(Vec2(m_visibleSize.width + 300, randTemp));
	m_speed = 0;
	m_isMove = false;

	return true;
}

void GameItem::updateBoard(float dt)
{
	if (m_isMove)
	{
		m_ItemSprite->setPositionX(m_ItemSprite->getPositionX() - m_speed * dt);
		if (m_ItemSprite->getPositionX() < -400)
		{
			initPos();
		}
	}
}

void GameItem::setBoardPosY(int y = 0)
{
	m_ItemSprite->setPositionY(y);
}

void GameItem::setSpeed(float speed)
{
	m_speed = speed;
}

float GameItem::getBoardPosX()
{
	return m_ItemSprite->getPositionX();
}

Rect GameItem::getSpriteBoundingBox()
{
	Rect rect = m_ItemSprite->getBoundingBox();
	rect.origin += getPosition();
	return rect;
}

bool GameItem::CheckColl(Rect& rect)
{
	Rect myRect = m_ItemSprite->getBoundingBox();
	myRect.setRect(myRect.getMinX() + 5, myRect.getMinY(), myRect.getMaxX() - myRect.getMinX() - 14, myRect.getMaxY() - myRect.getMinY());
	if (myRect.intersectsRect(rect))
	{
		initPos();
		return true;
	}
	return false;
}

void GameItem::move()
{
	if (!m_isMove)
	{
		m_ItemSprite->setPositionX(m_visibleSize.width + random(50, 500));
	}

	m_isMove = true;
}

GameItem::GameItem()
{
}


GameItem::~GameItem()
{
}
