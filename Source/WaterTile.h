#pragma once

#include "Tile.h"

namespace GameDev2D
{
	class WaterTile : public Tile
	{
	public:
		WaterTile(int index);
		~WaterTile();

		void Draw() override;
		TileType GetTileType() override;

		bool IsWalkable() override;

		void RefreshSprite() override;

	private:
		SpriteAtlas* m_WaterTile;
	};
}