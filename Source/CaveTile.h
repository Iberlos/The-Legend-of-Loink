#pragma once

#include "Tile.h"

namespace GameDev2D
{
	class CaveTile : public Tile
	{
	public:
		CaveTile(int index);
		~CaveTile();

		void Draw() override;
		TileType GetTileType() override;

		bool IsWalkable() override;
		void RefreshSprite() override;

	private:
		SpriteAtlas * m_CaveSprite;
	};
}