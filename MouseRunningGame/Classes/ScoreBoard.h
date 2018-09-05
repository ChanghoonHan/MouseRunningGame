#pragma once
#include <cocos2d.h>

USING_NS_CC;

class ScoreBoard
{
	static ScoreBoard* S;
	Size m_visiableSize;
	int m_scores[10];

	Sprite* m_scoreBoardSprite;
	Label* m_scoreLabel[10];

	ScoreBoard();
	~ScoreBoard();

	void GetScoresFromFile();
	void SetScoresToFile();
	void Init();

public:

	static ScoreBoard* GetInstance();
	static void Destroy();

	int GetHightScore();
	void SetScore(int score);
	void Print(Vec2 point, Layer* layer);
};

