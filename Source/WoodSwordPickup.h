#pragma once

#include "Pickup.h"

namespace GameDev2D
{
	class WoodSwordPickup : public Pickup
	{
	public:
		WoodSwordPickup(Tile* tile);
		~WoodSwordPickup();

		void Draw() override;
		float GetWidth() override;
		float GetHeight() override;

		PickupType GetPickupType() override;

	private:
		SpriteAtlas * m_WoodSword;
	};
}