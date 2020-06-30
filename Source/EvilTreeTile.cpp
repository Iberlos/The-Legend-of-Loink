#include "EvilTreeTile.h"

namespace GameDev2D
{
	EvilTreeTile::EvilTreeTile(int index) : Tile(index)
	{
		m_EvilTree = new SpriteAtlas("Tileset");
		m_EvilTree->AttachTo(this);
		m_EvilTree->UseFrame("EvilTree-Green-1");
	}

	EvilTreeTile::~EvilTreeTile()
	{
		SafeDelete(m_EvilTree);
	}

	void EvilTreeTile::Draw()
	{
		m_EvilTree->Draw();
	}

	TileType EvilTreeTile::GetTileType()
	{
		return TileType_EvilTree;
	}

	void EvilTreeTile::RefreshSprite()
	{
		std::string frame = "EvilTree-";

		switch (GetColor())
		{
		case TileColor_Primary:
			frame += "Green-";
			break;
		case TileColor_Secondary:
			frame += "Red-";
			break;
		case TileColor_Tertiary:
			frame += "Grey-";
			break;
		}

		switch (GetVariant())
		{
		case TileVariant_0:
			frame += "1";
			break;
		case TileVariant_1:
			frame += "2";
			break;
		case TileVariant_2:
			frame += "3";
			break;
		case TileVariant_3:
			frame += "4";
			break;
		case TileVariant_4:
			frame += "5";
			break;
		}

		//Lastly set the Tile's frame
		m_EvilTree->UseFrame(frame);
	}

	bool EvilTreeTile::IsWalkable()
	{
		return false;
	}
}