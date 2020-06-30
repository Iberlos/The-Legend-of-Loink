#pragma once

#include "Tile.h"


namespace GameDev2D
{
	class WaterfallTile : public Tile
	{
	public:
		WaterfallTile(int index);
		~WaterfallTile();

		void Draw() override;
		TileType GetTileType() override;

		bool IsWalkable() override;

	private:
		AnimatedSprite* m_WaterfallTile;
	};
}