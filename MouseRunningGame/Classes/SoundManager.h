#pragma once
#include <cocos2d.h>



class SoundManager
{
	static SoundManager* S;
	int curBackGroundMusicIdx;
	int playIdx;
	int gameOverIdx;

	SoundManager();
	~SoundManager();

public:
	static SoundManager* GetInstance();
	static void Destroy();

	void PlayBgm(int idx);
	void PlayEffect(int idx);
	void Init();
};

