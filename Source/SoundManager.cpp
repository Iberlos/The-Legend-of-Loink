#include "SoundManager.h"

namespace GameDev2D
{
	LinkSoundManager::LinkSoundManager()
	{
		m_Sounds[Theme_Sound] = new Audio("OverworldTheme-Loop_01");
		m_Sounds[Theme_Sound]->SetDoesLoop(true);
		m_Sounds[DungeonTheme_Sound] = new Audio("DungeonTheme-Loop");
		m_Sounds[DungeonTheme_Sound]->SetDoesLoop(true);
		m_Sounds[Item_Sound] = new Audio("ItemPickup");
		m_Sounds[Secret_Sound] = new Audio("Fanfare");
		m_Sounds[Sword_Sound] = new Audio("Sword");
		m_Sounds[BombDrop_Sound] = new Audio("BombDrop");
		m_Sounds[BombExplosion_Sound] = new Audio("BombExplode");
		m_Sounds[Hurt_Sound] = new Audio("LinkHurt");
		m_Sounds[LowHealth_Sound] = new Audio("LinkLowHealth");
		m_Sounds[LowHealth_Sound]->SetDoesLoop(true);
		m_Sounds[Fire_Sound] = new Audio("Candle");
		m_Sounds[LinkDeath_Sound] = new Audio("LinkDeath");
	}
	LinkSoundManager::~LinkSoundManager()
	{
	}
	void LinkSoundManager::PlayAudio(SoundType index)
	{
		m_Sounds[index]->Play();
	}
	void LinkSoundManager::PauseAudio(SoundType index)
	{
		m_Sounds[index]->Stop();
	}
	bool LinkSoundManager::IsAudioPlaying(SoundType index)
	{
		return m_Sounds[index]->IsPlaying();
	}
}