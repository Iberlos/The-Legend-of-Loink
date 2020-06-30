#pragma once

#include "Pickup.h"


namespace GameDev2D
{
	class TriforcePickup : public Pickup
	{
	public:
		TriforcePickup(Tile* tile);
		~TriforcePickup();

		void Draw();
		float GetWidth();
		float GetHeight();
		PickupType GetPickupType();

	private:
		SpriteAtlas * m_Triforce;
	};
}