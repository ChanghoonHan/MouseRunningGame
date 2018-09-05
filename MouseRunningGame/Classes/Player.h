#pragma once
#include <cocos2d.h>

USING_NS_CC;

class FootBoard;
class GameLayer;

class Player : public Layer
{
	enum PLAYER_COLOR
	{
		PINK,
		GREEN,
		BLUE,
	};

	enum PLAYER_STATE
	{
		STOP,
		RUN,
		JUMP,
		DEAD,
	};

	PLAYER_STATE m_playerState;
	PLAYER_COLOR m_color;
	Sprite* m_player;
	Animation* m_animation;
	Animate* m_animate;
	RepeatForever* m_animateRepeat;
	FootBoard* m_previouseFootBoard;

	GameLayer* m_pGameLayer;

	float m_dropSpeed;
	int m_jumpCount;
	const float m_dropincreaseSpeed = 2500;
	const float m_jumpSpeed = 1050;

	void SetJumpEnd();

	void GetPlayerCollRect(Rect* pRect);

public:
	Player();
	~Player();

	CREATE_FUNC(Player);

	bool init();
	void onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event);
	void updatePlayer(float dt);
	void setGameLayer(GameLayer* gameLayer);
	void Kill();
	void GameStart();
};

