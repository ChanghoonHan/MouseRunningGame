#include "SoundManager.h"
#include "audio\include\AudioEngine.h"

USING_NS_CC;
using namespace experimental;

SoundManager* SoundManager::S = NULL;

void SoundManager::Init()
{
	curBackGroundMusicIdx = 0;
	playIdx = -1;
	gameOverIdx = -1;
	
	AudioEngine::preload("./sound/MenuSound.mp3");
	AudioEngine::preload("./sound/GameSound.mp3");

	AudioEngine::preload("./sound/BookFlip.mp3");
	AudioEngine::preload("./sound/GetItem.mp3");
	AudioEngine::preload("./sound/JumpSound.mp3");
	AudioEngine::preload("./sound/FallPlayer.mp3");
	AudioEngine::preload("./sound/GameOver.mp3");
	AudioEngine::preload("./sound/ReadyRun.mp3");
}

void SoundManager::PlayBgm(int idx)
{
	switch (idx)
	{
	case 1:
		if (curBackGroundMusicIdx != 1)
		{
			curBackGroundMusicIdx = 1;
			if (gameOverIdx != -1)
			{
				AudioEngine::stop(gameOverIdx);
				gameOverIdx = -1;
			}

			if (playIdx != -1)
			{
				AudioEngine::stop(playIdx);
			}
			
			playIdx = AudioEngine::play2d("./sound/MenuSound.mp3", true, 0.4);
		}

		break;
	case 2:
		curBackGroundMusicIdx = 2;
		if (gameOverIdx != -1)
		{
			AudioEngine::stop(gameOverIdx);
			gameOverIdx = -1;
		}

		if (playIdx != -1)
		{
			AudioEngine::stop(playIdx);
		}
		playIdx = AudioEngine::play2d("./sound/GameSound.mp3", true, 0.2);

		break;
	default:
		break;
	}
}

void SoundManager::PlayEffect(int idx)
{
	switch (idx)
	{
	case 1:
		AudioEngine::play2d("./sound/BookFlip.mp3");
		break;

	case 2:
		AudioEngine::play2d("./sound/GetItem.mp3", false, 0.5f);
		break;

	case 3:
		AudioEngine::play2d("./sound/JumpSound.mp3");
		break;

	case 4:
		AudioEngine::play2d("./sound/FallPlayer.mp3");
		break;

	case 5:
		gameOverIdx = AudioEngine::play2d("./sound/GameOver.mp3");
		break;

	case 6:
		gameOverIdx = AudioEngine::play2d("./sound/ReadyRun.mp3");
		break;
	default:
		break;
	}
}

SoundManager* SoundManager::GetInstance()
{
	if (S == NULL)
	{
		S = new SoundManager();
	}

	return S;
}

void SoundManager::Destroy()
{
	if (S != NULL)
	{
		delete(S);
	}

	S = NULL;
}

SoundManager::SoundManager()
{
}


SoundManager::~SoundManager()
{
	AudioEngine::end();
}
