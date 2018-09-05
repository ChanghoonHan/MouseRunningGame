#pragma once
#include <cocos2d.h>

USING_NS_CC;
class BackgroundLayer;

class RankingLayer : public Layer
{
	Size m_visibleSize;

	BackgroundLayer* m_backgroundLayer[7];

	void InitLayers();
	void SceneChangeToHome(Ref* sender);

public:
	RankingLayer();
	~RankingLayer();

	CREATE_FUNC(RankingLayer);

	bool init();

	void update(float deltaTime);
};

