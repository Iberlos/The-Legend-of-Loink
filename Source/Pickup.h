#pragma once

#include <GameDev2D.h>
#include "Constants.h"


namespace GameDev2D
{
	//Forward declaration
	class Tile;

	class Pickup : public Drawable
	{
	public:
		Pickup(Tile* tile);
		virtual ~Pickup();

		virtual void Draw() = 0;
		virtual float GetWidth() = 0;
		virtual float GetHeight() = 0;

		virtual PickupType GetPickupType() = 0;

		virtual Tile* GetTile();

	private:
		Tile* m_Tile;
	};
}