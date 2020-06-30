#include "Pickup.h"
#include "Tile.h"


namespace GameDev2D
{
	Pickup::Pickup(Tile * tile)
	{
		m_Tile = tile;
		SetPosition(tile->GetCenter());
	}

	Pickup::~Pickup()
	{
	}
	Tile * Pickup::GetTile()
	{
		return m_Tile;
	}
}