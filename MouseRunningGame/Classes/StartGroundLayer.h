#pragma once
#include <cocos2d.h>

USING_NS_CC;

class StartGroundLayer : public Layer
{
	Sprite* m_groundSprite;
	Size m_visibleSize;
	int m_speed;

public:
	StartGroundLayer();
	~StartGroundLayer();

	CREATE_FUNC(StartGroundLayer);

	void updateGround(float deltaTime);

	bool isEndOfScreen();

	bool init();

	bool CheckColl(Rect& rect, int* offsetTemp);

	void setSpeed(float speed);
};

