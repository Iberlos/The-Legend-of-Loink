#include "RockTile.h"

namespace GameDev2D
{
	RockTile::RockTile(int index) : Tile(index)
	{
		m_RockTile = new SpriteAtlas("Tileset");
		m_RockTile->UseFrame("Rock-Green-1");
		m_RockTile->AttachTo(this);
	}

	RockTile::~RockTile()
	{
		SafeDelete(m_RockTile);
	}

	void RockTile::Draw()
	{
		m_RockTile->Draw();
	}

	TileType RockTile::GetTileType()
	{
		return TileType_Rock;
	}

	void RockTile::RefreshSprite()
	{
		std::string frame = "Rock-";

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
		case TileVariant_5:
			frame += "6";
			break;
		}

		//Lastly set the Tile's frame
		m_RockTile->UseFrame(frame);
	}

	bool RockTile::IsWalkable()
	{
		return false;
	}
}