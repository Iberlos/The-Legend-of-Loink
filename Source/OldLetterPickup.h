#pragma once

#include "Pickup.h"


namespace GameDev2D
{
	class OldLetterPickup : public Pickup
	{
	public:
		OldLetterPickup(Tile* tile);
		~OldLetterPickup();

		void Draw();
		float GetWidth();
		float GetHeight();
		PickupType GetPickupType();

	private:
		SpriteAtlas * m_OldLetter;
	};
}