#pragma once

#include "Tile.h"

namespace GameDev2D
{
	class TreeTile : public Tile
	{
	public:
		TreeTile(int index);
		~TreeTile();

		void Draw() override;
		TileType GetTileType()override;

		bool IsWalkable() override;

		void RefreshSprite() override;

	private:
		SpriteAtlas* m_TreeTile;
	};
}
