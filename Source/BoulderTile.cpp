#include "BoulderTile.h"


namespace GameDev2D
{
	BoulderTile::BoulderTile(int index) : Tile(index)
	{
		m_BoulderTile = new SpriteAtlas("Tileset");
		m_BoulderTile->UseFrame("Boulder-Green");
		m_BoulderTile->AttachTo(this);
	}

	BoulderTile::~BoulderTile()
	{
		SafeDelete(m_BoulderTile);
	}

	void BoulderTile::Draw()
	{
		m_BoulderTile->Draw();
	}

	TileType BoulderTile::GetTileType()
	{
		return TileType_Boulder;
	}

	bool BoulderTile::IsWalkable()
	{
		return false;
	}
}