#pragma once
#include <cocos2d.h>

USING_NS_CC;

class EnemyLayer : public Layer
{
	Sprite* m_enemySprites[2];
	Size m_visibleSize;
	float m_speed;
	int m_frontIdx;

public:
	EnemyLayer();
	~EnemyLayer();

	CREATE_FUNC(EnemyLayer);

	void updateGround(float deltaTime);

	bool init();

	void setSpeed(float speed);
};

