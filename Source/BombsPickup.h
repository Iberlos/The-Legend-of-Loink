#pragma once

#include "Pickup.h"
#include "Timer.h"

namespace GameDev2D
{
	class BombsPickup : public Pickup, EventHandler
	{
	public:
		BombsPickup(Tile* tile);
		~BombsPickup();

		void Draw();
		float GetWidth();
		float GetHeight();
		PickupType GetPickupType();

		void HandleEvent(Event* event);

		void Arm();
		bool IsArmed();

	private:
		SpriteAtlas * m_Bombs;
		bool m_IsArmed;
		Timer m_Fuse;
	};
}