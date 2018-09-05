#pragma once
#include <cocos2d.h>

class FootBoard;
class GameItem;
class EnemyLayer;
class StartGroundLayer;

class CollManager
{
	static CollManager* S;
	FootBoard** m_footBoards;
	GameItem** m_gameItems;
	EnemyLayer* m_enemyLayer;
	StartGroundLayer* m_startGroundLayer;

	bool m_bEndGround;
	
	CollManager();
	~CollManager();
public:
	static CollManager* GetInstance();
	static void Destroy();

	void Init();
	void EndGround();

	void SetFootBoards(FootBoard** footBoards);
	void SetGameItems(GameItem** gameItems);
	void SetEnemy(EnemyLayer* enemyLayer);
	void SetGround(StartGroundLayer* startGroundLayer);

	StartGroundLayer* GetGround();
	FootBoard** GetFootBoards();
	GameItem** GetGameItems();
};

