#pragma once
#include <cocos2d.h>

USING_NS_CC;

class FootBoard;
class GameItem;
class BackgroundLayer;
class StartGround;
class StartGroundLayer;
class EnemyLayer;
class Player;

class GameLayer : public Layer
{
	enum GAMESTATE
	{
		READY,
		GAME,
		GAMEOVERREADY,
		GAMEOVER,
	};

	GAMESTATE m_gameState;

	const float MAX_TIMER = 30;
	float m_Timer;

	Sprite* m_timerBarCase[2];
	Sprite* m_timerBar;
	Sprite* m_gameOverSprite;
	Sprite* m_gameStartSprite;

	Label* m_scoreLabel;
	Label* m_highScoreLabel;
	Size m_visibleSize;
	Player* m_player;
	BackgroundLayer* m_backgroundLayer[6];
	FootBoard* m_foodboard[8];
	GameItem* m_gameItem[20];
	EnemyLayer* m_enemyLayer;
	StartGroundLayer* m_startGroundLayer;

	int m_gameSpeed;
	int m_score;
	int m_hightScore;
	
	int m_level;

	int m_increaseScore;

	float m_scoreTimer;

	bool m_newRecord;

	void InitLayers();
	void SetLayersSpeed();
	void RestartGame(Ref* sender);
	void SceneChangeToHome(Ref* sender);
	void onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event);
	void changeGameStartText();
	void changeGameStateToGame();
	void SetGameStateToGameOver();

public:
	GameLayer();
	~GameLayer();

	CREATE_FUNC(GameLayer);

	void SetGameOver();

	void update(float deltaTime);
	void IncreaseTimer(float time);
	void DecreaseTimer(float time);
	void IncreaseScore(int score);
	bool init();
};

