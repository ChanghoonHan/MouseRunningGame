#include "BackgroundLayer.h"

bool BackgroundLayer::init()
{
	m_visibleSize = Director::getInstance()->getVisibleSize();
	m_speed = 0;
	m_frontIdx = 0;
	return true;
}

void BackgroundLayer::updateBackGround(float deltaTime)
{
	for (size_t i = 0; i < 2; i++)
	{
		float xPos = m_backgroundSprite[i]->getPosition().x - m_speed * deltaTime;
		m_backgroundSprite[i]->setPosition(Vec2(xPos, 0));

		if (m_frontIdx == i)
		{
			if (xPos <= -m_visibleSize.width)
			{
				m_frontIdx = (i + 1) % 2;
				m_backgroundSprite[i]->setPosition(Vec2(m_visibleSize.width + (xPos + m_visibleSize.width), 0));
			}
		}
	}
}

void BackgroundLayer::setSprite(std::string spriteName)
{
	std::string spritePath;
	spritePath = "./Resource/" + spriteName;

	for (size_t i = 0; i < 2; i++)
	{
		m_backgroundSprite[i] = Sprite::create(spritePath);
		m_backgroundSprite[i]->setScale(0.75);
		m_backgroundSprite[i]->setAnchorPoint(Vec2(0, 0));
		m_backgroundSprite[i]->setPosition(Vec2(m_visibleSize.width * i, 0));
		this->addChild(m_backgroundSprite[i]);
	}
}

void BackgroundLayer::setSpeed(float speed)
{
	m_speed = speed;
}

BackgroundLayer::BackgroundLayer()
{
}


BackgroundLayer::~BackgroundLayer()
{
}
