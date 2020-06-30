#include "TreeTile.h"

namespace GameDev2D
{
	TreeTile::TreeTile(int index) : Tile(index)
	{
		m_TreeTile = new SpriteAtlas("Tileset");
		m_TreeTile->UseFrame("Tree-Green");
		m_TreeTile->AttachTo(this);
	}

	TreeTile::~TreeTile()
	{
		SafeDelete(m_TreeTile);
	}

	void TreeTile::Draw()
	{
		m_TreeTile->Draw();
	}

	TileType TreeTile::GetTileType()
	{
		return TileType_Tree;
	}

	bool TreeTile::IsWalkable()
	{
		return false;
	}
	void TreeTile::RefreshSprite()
	{
		if (GetColor() == TileColor_Primary)
		{
			m_TreeTile->UseFrame("Tree-Green");
		}
		else if (GetColor() == TileColor_Secondary)
		{
			m_TreeTile->UseFrame("Tree-Red");
		}
		else if (GetColor() == TileColor_Tertiary)
		{
			m_TreeTile->UseFrame("Tree-Grey");
		}
	}
}