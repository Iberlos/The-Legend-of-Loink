#pragma once

#include "Pickup.h"


namespace GameDev2D
{
	class CandlePickup : public Pickup
	{
	public:
		CandlePickup(Tile* tile);
		~CandlePickup();

		void Draw();
		float GetWidth();
		float GetHeight();
		PickupType GetPickupType();

	private:
		SpriteAtlas * m_Candle;
	};
}