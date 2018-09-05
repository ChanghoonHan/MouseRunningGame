#include "CollManager.h"

CollManager* CollManager::S = NULL;

CollManager* CollManager::GetInstance()
{
	if (S == nullptr)
	{
		S = new CollManager();
	}

	return S;
}

void CollManager::Destroy()
{
	if (S != nullptr)
	{
		delete(S);
	}

	S = nullptr;
}

void CollManager::SetFootBoards(FootBoard** footBoards)
{
	m_footBoards = footBoards;
}

void CollManager::SetGameItems(GameItem** gameItems)
{
	m_gameItems = gameItems;
}

void CollManager::SetEnemy(EnemyLayer* enemyLayer)
{
	m_enemyLayer = enemyLayer;
}

void CollManager::SetGround(StartGroundLayer* startGroundLayer)
{
	m_startGroundLayer = startGroundLayer;
}

GameItem** CollManager::GetGameItems()
{
	return m_gameItems;
}

FootBoard** CollManager::GetFootBoards()
{
	return m_footBoards;
}

StartGroundLayer* CollManager::GetGround()
{
	if (m_bEndGround)
	{
		return NULL;
	}

	return m_startGroundLayer;
}

void CollManager::Init()
{
	m_bEndGround = false;
}

void CollManager::EndGround()
{
	m_bEndGround = true;
}

CollManager::CollManager()
{
}


CollManager::~CollManager()
{
}
