#pragma once

#include "Tile.h"

namespace GameDev2D
{
	class RockTile : public Tile
	{
	public:
		RockTile(int index);
		~RockTile();

		void Draw() override;
		TileType GetTileType() override;

		void RefreshSprite() override;
		bool IsWalkable() override;

	private:
		SpriteAtlas* m_RockTile;
	};
}