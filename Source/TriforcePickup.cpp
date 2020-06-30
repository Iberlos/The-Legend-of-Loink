#include "TriforcePickup.h"

namespace GameDev2D
{
	TriforcePickup::TriforcePickup(Tile* tile) : Pickup(tile)
	{
		m_Triforce = new SpriteAtlas("Tileset");
		m_Triforce->UseFrame("TriforcePiece-1");
		m_Triforce->SetAnchor(Vector2(0.5f, 0.5f));
		m_Triforce->AttachTo(this);
	}

	TriforcePickup::~TriforcePickup()
	{
		SafeDelete(m_Triforce);
	}

	void TriforcePickup::Draw()
	{
		m_Triforce->Draw();
	}

	float TriforcePickup::GetWidth()
	{
		return m_Triforce->GetWidth();
	}

	float TriforcePickup::GetHeight()
	{
		return m_Triforce->GetHeight();
	}

	PickupType TriforcePickup::GetPickupType()
	{
		return PickupType_Triforce;
	}
}