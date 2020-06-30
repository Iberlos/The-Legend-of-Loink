#include "CandlePickup.h"

namespace GameDev2D
{
	CandlePickup::CandlePickup(Tile* tile) : Pickup(tile)
	{
		m_Candle = new SpriteAtlas("Tileset");
		m_Candle->UseFrame("Candle-Red");
		m_Candle->SetAnchor(Vector2(0.5f, 0.5f));
		m_Candle->AttachTo(this);
	}

	CandlePickup::~CandlePickup()
	{
		SafeDelete(m_Candle);
	}

	void CandlePickup::Draw()
	{
		m_Candle->Draw();
	}

	float CandlePickup::GetWidth()
	{
		return m_Candle->GetWidth();
	}

	float CandlePickup::GetHeight()
	{
		return m_Candle->GetHeight();
	}

	PickupType CandlePickup::GetPickupType()
	{
		return PickupType_Candle;
	}
}