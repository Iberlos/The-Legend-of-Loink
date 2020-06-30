#include "WaterfallTile.h"


namespace GameDev2D
{
	WaterfallTile::WaterfallTile(int index) : Tile(index)
	{
		m_WaterfallTile = new AnimatedSprite("Tileset");
		m_WaterfallTile->AddFrame("WaterFall-1");
		m_WaterfallTile->AddFrame("WaterFall-2");
		m_WaterfallTile->SetFrameSpeed(5);
		m_WaterfallTile->SetDoesLoop(true);
		m_WaterfallTile->AttachTo(this);
	}

	WaterfallTile::~WaterfallTile()
	{
		SafeDelete(m_WaterfallTile);
	}

	void WaterfallTile::Draw()
	{
		m_WaterfallTile->Draw();
	}

	TileType WaterfallTile::GetTileType()
	{
		return TileType_Waterfall;
	}

	bool WaterfallTile::IsWalkable()
	{
		return false;
	}
}