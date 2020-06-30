#pragma once
#include <GameDev2D.h>
#include "Constants.h"

namespace GameDev2D
{
	class LinkSoundManager
	{
	public:
		LinkSoundManager();
		~LinkSoundManager();
		void PlayAudio(SoundType index);
		void PauseAudio(SoundType index);
		bool IsAudioPlaying(SoundType index);
	private:
		Audio* m_Sounds[ALL_SOUND_EFFECTS];
	};
}