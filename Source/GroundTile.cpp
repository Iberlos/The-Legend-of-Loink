#include "GroundTile.h"

namespace GameDev2D
{
	GroundTile::GroundTile(int index) : Tile(index)
	{
		m_GroundTile = new SpriteAtlas("Tileset");
		m_GroundTile->UseFrame("Ground-1");
		m_GroundTile->AttachTo(this);
	}

	GroundTile::~GroundTile()
	{
		SafeDelete(m_GroundTile);
	}

	void GroundTile::Draw()
	{
		m_GroundTile->Draw();
	}

	TileType GroundTile::GetTileType()
	{
		return TileType_Ground;
	}
	void GroundTile::RefreshSprite()
	{
		if (GetColor() == TileColor_Primary)
		{
			m_GroundTile->UseFrame("Ground-1");
		}
		else if (GetColor() == TileColor_Secondary)
		{
			m_GroundTile->UseFrame("Ground-2");
		}

	}
}