#include "WoodSwordPickup.h"

namespace GameDev2D
{
	WoodSwordPickup::WoodSwordPickup(Tile * tile) : Pickup(tile)
	{
		m_WoodSword = new SpriteAtlas("Tileset");
		m_WoodSword->UseFrame("Sword-Wood");
		m_WoodSword->SetAnchor(Vector2(0.5f, 0.5f));
		m_WoodSword->AttachTo(this);
	}

	WoodSwordPickup::~WoodSwordPickup()
	{
		SafeDelete(m_WoodSword);
	}

	void WoodSwordPickup::Draw()
	{
		m_WoodSword->Draw();
	}

	float WoodSwordPickup::GetWidth()
	{
		return m_WoodSword->GetWidth();
	}

	float WoodSwordPickup::GetHeight()
	{
		return m_WoodSword->GetHeight();
	}

	PickupType WoodSwordPickup::GetPickupType()
	{
		return PickupType_WoodSword;
	}
}