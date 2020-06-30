#pragma once

#include "Tile.h"

namespace GameDev2D
{
	class GroundTile : public Tile
	{
	public:
		GroundTile(int index);
		~GroundTile();

		void Draw() override;
		TileType GetTileType() override;

		void RefreshSprite() override;

	private:
		SpriteAtlas* m_GroundTile;
	};
}