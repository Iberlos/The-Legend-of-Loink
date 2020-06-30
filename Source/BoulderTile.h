#pragma once

#include "Tile.h"


namespace GameDev2D
{
	class BoulderTile : public Tile
	{
	public:
		BoulderTile(int index);
		~BoulderTile();

		void Draw() override;
		TileType GetTileType() override;

		bool IsWalkable() override;

	private:
		SpriteAtlas* m_BoulderTile;
	};
}
