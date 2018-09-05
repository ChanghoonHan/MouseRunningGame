#pragma once
#include <cocos2d.h>

USING_NS_CC;
class BackgroundLayer;

class MenuLayer : public Layer
{
	Size m_visibleSize;

	BackgroundLayer* m_backgroundLayer[7];
	Sprite* m_mouseSprite;
	Sprite* m_titleSprite;

	float m_mouseSpriteChangeTime;
	int m_mouseSpriteIdx;

	void InitLayers();
	void ChageSceneToGameScene(Ref* pSender);
	void ChageSceneToRankingScene(Ref* pSender);
	void GameQuit(Ref* pSender);

public:
	MenuLayer();
	~MenuLayer();

	CREATE_FUNC(MenuLayer);

	bool init();

	void update(float deltaTime);
};

