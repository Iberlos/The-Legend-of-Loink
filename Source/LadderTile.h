#pragma once

#include "Tile.h"

namespace GameDev2D
{
	class LadderTile : public Tile
	{
	public:
		LadderTile(int index);
		~LadderTile();

		void Draw() override;
		TileType GetTileType() override;

		void RefreshSprite() override;

	private:
		SpriteAtlas* m_LadderTile;
	};
}