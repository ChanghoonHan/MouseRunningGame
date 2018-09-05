#pragma once
#include <cocos2d.h>

USING_NS_CC;

class FootBoard : public Node
{
	enum BOARD_COLOR
	{
		PINK,
		GREEN,
		BLUE,
	};

	BOARD_COLOR m_boardColor;
	Sprite* m_footBoardSprite;
	Size m_visibleSize;
	float m_speed;
	bool m_isMove;

public:
	FootBoard();
	~FootBoard();

	CREATE_FUNC(FootBoard);
	void updateBoard(float dt);
	void setBoardPosY(int y);
	void setSpeed(float speed);
	float getBoardPosX();
	Rect getSpriteBoundingBox();
	bool CheckColl(Rect& rect, int* offsetTemp, int color = 0, bool* isSameColor = NULL);
	bool init();
	bool initPos();
	void move();
};

