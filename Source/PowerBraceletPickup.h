#pragma once

#include "Pickup.h"


namespace GameDev2D
{
	class PowerBraceletPickup : public Pickup
	{
	public:
		PowerBraceletPickup(Tile* tile);
		~PowerBraceletPickup();

		void Draw();
		float GetWidth();
		float GetHeight();
		PickupType GetPickupType();

	private:
		SpriteAtlas * m_Bracelet;
	};
}