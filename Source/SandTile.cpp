#include "SandTile.h"

namespace GameDev2D
{
	SandTile::SandTile(int index) : Tile(index)
	{
		m_SandTile = new SpriteAtlas("Tileset");
		m_SandTile->UseFrame("Sand-Red");
		m_SandTile->AttachTo(this);
	}

	SandTile::~SandTile()
	{
		SafeDelete(m_SandTile);
	}

	void SandTile::Draw()
	{
		m_SandTile->Draw();
	}

	TileType SandTile::GetTileType()
	{
		return TileType_Sand;
	}
}