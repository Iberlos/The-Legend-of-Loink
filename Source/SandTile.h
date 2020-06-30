#pragma once

#include "Tile.h"

namespace GameDev2D
{
	class SandTile : public Tile
	{
	public:
		SandTile(int index);
		~SandTile();

		void Draw() override;
		TileType GetTileType() override;

	private:
		SpriteAtlas* m_SandTile;
	};
}