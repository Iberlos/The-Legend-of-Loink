#include "WaterTile.h"

namespace GameDev2D
{
	WaterTile::WaterTile(int index) : Tile(index)
	{
		m_WaterTile = new SpriteAtlas("Tileset");
		m_WaterTile->UseFrame("Water-Green-1");
		m_WaterTile->AttachTo(this);
	}

	WaterTile::~WaterTile()
	{
		SafeDelete(m_WaterTile);
	}

	void WaterTile::Draw()
	{
		m_WaterTile->Draw();
	}

	TileType WaterTile::GetTileType()
	{
		return TileType_Water;
	}

	bool WaterTile::IsWalkable()
	{
		return false;
	}
	void WaterTile::RefreshSprite()
	{
		std::string frame = "Water-Green-";

		switch (GetVariant())
		{
			case TileVariant_0:
			{
				frame += "1";
			}
			break;

			case TileVariant_1:
			{
				frame += "2";
			}
			break;

			case TileVariant_2:
			{
				frame += "3";
			}
			break;

			case TileVariant_3:
			{
				frame += "4";
			}
			break;

			case TileVariant_4:
			{
				frame += "5";
			}
			break;

			case TileVariant_5:
			{
				frame += "6";
			}
			break;

			case TileVariant_6:
			{
				frame += "7";
			}
			break;

			case TileVariant_7:
			{
				frame += "8";
			}
			break;

			case TileVariant_8:
			{
				frame += "9";
			}
			break;

			case TileVariant_9:
			{
				frame += "10";
			}
			break;

			case TileVariant_10:
			{
				frame += "11";
			}
			break;

			case TileVariant_11:
			{
				frame += "12";
			}
			break;

			case TileVariant_12:
			{
				frame += "13";
			}
			break;
		}

		m_WaterTile->UseFrame(frame);
	}
}