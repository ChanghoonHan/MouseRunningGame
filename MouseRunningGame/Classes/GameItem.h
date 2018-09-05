#pragma once
#include <cocos2d.h>

USING_NS_CC;

class GameItem : public Node
{
	Sprite* m_ItemSprite;
	Size m_visibleSize;
	float m_speed;
	bool m_isMove;

public:
	GameItem();
	~GameItem();

	CREATE_FUNC(GameItem);
	void updateBoard(float dt);
	void setBoardPosY(int y);
	void setSpeed(float speed);
	float getBoardPosX();
	Rect getSpriteBoundingBox();
	bool CheckColl(Rect& rect);
	bool init();
	bool initPos();
	void move();
};

