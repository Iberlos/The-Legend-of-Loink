#include "PowerBraceletPickup.h"

namespace GameDev2D
{
	PowerBraceletPickup::PowerBraceletPickup(Tile* tile) : Pickup(tile)
	{
		m_Bracelet = new SpriteAtlas("Tileset");
		m_Bracelet->UseFrame("PowerBracelet");
		m_Bracelet->SetAnchor(Vector2(0.5f, 0.5f));
		m_Bracelet->AttachTo(this);
	}

	PowerBraceletPickup::~PowerBraceletPickup()
	{
		SafeDelete(m_Bracelet);
	}

	void PowerBraceletPickup::Draw()
	{
		m_Bracelet->Draw();
	}

	float PowerBraceletPickup::GetWidth()
	{
		return m_Bracelet->GetWidth();
	}

	float PowerBraceletPickup::GetHeight()
	{
		return m_Bracelet->GetHeight();
	}

	PickupType PowerBraceletPickup::GetPickupType()
	{
		return PickupType_Bracelet;
	}
}