#include "LadderTile.h"

namespace GameDev2D
{
	LadderTile::LadderTile(int index) : Tile(index)
	{
		m_LadderTile = new SpriteAtlas("Tileset");
		m_LadderTile->UseFrame("Ladder-Green");
		m_LadderTile->AttachTo(this);
	}

	LadderTile::~LadderTile()
	{
		SafeDelete(m_LadderTile);
	}

	void LadderTile::Draw()
	{
		m_LadderTile->Draw();
	}

	TileType LadderTile::GetTileType()
	{
		return TileType_Ground;
	}
	void LadderTile::RefreshSprite()
	{
	}
}