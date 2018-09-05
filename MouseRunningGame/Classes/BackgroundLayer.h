#pragma once
#include <cocos2d.h>

USING_NS_CC;

class BackgroundLayer : public Layer
{
	Sprite* m_backgroundSprite[2];
	Size m_visibleSize;
	float m_speed;
	int m_frontIdx;

public:
	BackgroundLayer();
	~BackgroundLayer();

	CREATE_FUNC(BackgroundLayer);

	/*virtual bool onTouchBegan(Touch *touch, Event *unused_event);
	virtual void onTouchMoved(Touch *touch, Event *unused_event);
	virtual void onTouchEnded(Touch *touch, Event *unused_event);
	virtual void onTouchCancelled(Touch *touch, Event *unused_event);*/

	void setSprite(std::string spriteName);

	void updateBackGround(float deltaTime);

	bool init();

	void setSpeed(float speed);
};

