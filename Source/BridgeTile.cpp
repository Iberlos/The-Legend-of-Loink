#include "BridgeTile.h"

namespace GameDev2D
{
	BridgeTile::BridgeTile(int index) : Tile(index)
	{
		m_Bridge = new SpriteAtlas("Tileset");
		m_Bridge->UseFrame("Bridge-Green");
		m_Bridge->AttachTo(this);
	}

	BridgeTile::~BridgeTile()
	{
		SafeDelete(m_Bridge);
	}

	void BridgeTile::Draw()
	{
		m_Bridge->Draw();
	}

	TileType BridgeTile::GetTileType()
	{
		return TileType_Bridge;
	}

	void BridgeTile::RefreshSprite()
	{
		std::string frame = "Bridge-";

		switch (GetColor())
		{
		case TileColor_Primary:
			frame += "Green";
			break;
		case TileColor_Secondary:
			frame += "Red";
			break;
		case TileColor_Tertiary:
			frame += "Grey";
			break;
		}

		//Lastly set the Tile's frame
		m_Bridge->UseFrame(frame);
	}
}