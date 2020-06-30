#include "CaveTile.h"

namespace GameDev2D
{
	CaveTile::CaveTile(int index) : Tile(index)
	{
		m_CaveSprite = new SpriteAtlas("Tileset");
		m_CaveSprite->UseFrame("Door");
		m_CaveSprite->AttachTo(this);
	}

	CaveTile::~CaveTile()
	{
		SafeDelete(m_CaveSprite);
	}

	void CaveTile::Draw()
	{
		m_CaveSprite->Draw();
	}

	TileType CaveTile::GetTileType()
	{
		return TileType_Cave;
	}
	bool CaveTile::IsWalkable()
	{
		if (GetVariant() == TileVariant_0)
		{
			return true;
		}

		return false;
	}

	void CaveTile::RefreshSprite()
	{
		if (GetVariant() == TileVariant_0)
		{
			m_CaveSprite->UseFrame("Door");
		}
		else
		{
			m_CaveSprite->UseFrame("Cave");
		}
	}
}