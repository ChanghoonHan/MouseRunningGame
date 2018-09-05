#include "ScoreBoard.h"

ScoreBoard* ScoreBoard::S = NULL;

void ScoreBoard::GetScoresFromFile()
{
	memset(m_scores, 0, sizeof(int) * 10);

	FILE* fp = fopen("ScoreBorad.txt", "r");
	
	if (fp != NULL)
	{
		fread(m_scores, sizeof(int), 10, fp);
		fclose(fp);
	}
}

void ScoreBoard::SetScoresToFile()
{
	FILE* fp = fopen("ScoreBorad.txt", "w");

	if (fp != NULL)
	{
		fwrite(m_scores, sizeof(int), 10, fp);
	}

	fclose(fp);
}

int ScoreBoard::GetHightScore()
{
	GetScoresFromFile();

	return m_scores[0];
}

void ScoreBoard::SetScore(int score)
{
	GetScoresFromFile();

	if (score < m_scores[9])
	{
		return;
	}

	for (size_t i = 0; i < 10; i++)
	{
		if (score < m_scores[i])
		{
			continue;
		}

		for (size_t j = 9; j > i; j--)
		{
			m_scores[j] = m_scores[j - 1];
		}

		m_scores[i] = score;
		break;
	}

	SetScoresToFile();
}

void ScoreBoard::Print(Vec2 point, Layer* layer)
{
	GetScoresFromFile();

	m_scoreBoardSprite = Sprite::create("./Resource/ScoreBoard.png");
	m_scoreBoardSprite->setPosition(point);
	layer->addChild(m_scoreBoardSprite, 4);

	for (size_t i = 0; i < 10; i++)
	{
		m_scoreLabel[i] = Label::create(StringUtils::format("%d", m_scores[i]), "fonts/koverwatch.ttf", 80);


		m_scoreLabel[i]->setAnchorPoint(Vec2(0, 0));
		if (i < 5)
		{
			m_scoreLabel[i]->setPosition(point.x - 190, point.y + 135 - (90 * i));
		}
		else
		{
			m_scoreLabel[i]->setPosition(point.x + 70, point.y + 135 - (90 * (i - 5)));
		}

		layer->addChild(m_scoreLabel[i], 4);
	}
}

void ScoreBoard::Init()
{
	m_visiableSize = Director::getInstance()->getVisibleSize();
}

ScoreBoard* ScoreBoard::GetInstance()
{
	if (S == NULL)
	{
		S = new ScoreBoard;
		S->Init();
	}

	return S;
}

void ScoreBoard::Destroy()
{
	if (S != NULL)
	{
		delete(S);
	}

	S = NULL;
}

ScoreBoard::ScoreBoard()
{
}


ScoreBoard::~ScoreBoard()
{
}
