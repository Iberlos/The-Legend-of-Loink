#pragma once

#include "Tile.h"


namespace GameDev2D
{
	class BridgeTile : public Tile
	{
	public:
		BridgeTile(int index);
		~BridgeTile();

		void Draw() override;
		TileType GetTileType() override;

		void RefreshSprite() override;

	private:
		SpriteAtlas * m_Bridge;
	};
}
