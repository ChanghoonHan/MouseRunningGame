#include "EnemyLayer.h"

bool EnemyLayer::init()
{
	m_speed = 0;
	m_frontIdx = 0;
	m_visibleSize = Director::getInstance()->getVisibleSize();

	for (size_t i = 0; i < 2; i++)
	{
		m_enemySprites[i] = Sprite::create("./Resource/enemy.png");
		m_enemySprites[i]->setScale(0.75);
		m_enemySprites[i]->setAnchorPoint(Vec2(0, 0));
		m_enemySprites[i]->setPosition(Vec2(m_visibleSize.width * (i + 1), 0));
		this->addChild(m_enemySprites[i]);
	}

	return true;
}

void EnemyLayer::updateGround(float deltaTime)
{
	for (size_t i = 0; i < 2; i++)
	{
		float xPos = m_enemySprites[i]->getPosition().x - m_speed * deltaTime;
		m_enemySprites[i]->setPosition(Vec2(xPos, 0));

		if (m_frontIdx == i)
		{
			if (xPos <= -m_visibleSize.width)
			{
				m_frontIdx = (i + 1) % 2;
				m_enemySprites[i]->setPosition(Vec2(m_visibleSize.width + (xPos + m_visibleSize.width), 0));
			}
		}
	}
}

void EnemyLayer::setSpeed(float speed)
{
	m_speed = speed;
}

EnemyLayer::EnemyLayer()
{
}


EnemyLayer::~EnemyLayer()
{
}
