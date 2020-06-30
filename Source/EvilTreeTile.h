#pragma once

#include "Tile.h"


namespace GameDev2D
{
	class EvilTreeTile : public Tile
	{
	public:
		EvilTreeTile(int index);
		~EvilTreeTile();

		void Draw() override;
		TileType GetTileType() override;

		void RefreshSprite() override;
		bool IsWalkable() override;

	private:
		SpriteAtlas * m_EvilTree;
	};
}
