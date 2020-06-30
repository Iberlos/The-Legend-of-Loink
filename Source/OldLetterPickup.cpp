#include "OldLetterPickup.h"

namespace GameDev2D
{
	OldLetterPickup::OldLetterPickup(Tile* tile) : Pickup(tile)
	{
		m_OldLetter = new SpriteAtlas("Tileset");
		m_OldLetter->UseFrame("Letter");
		m_OldLetter->SetAnchor(Vector2(0.5f, 0.5f));
		m_OldLetter->AttachTo(this);
	}

	OldLetterPickup::~OldLetterPickup()
	{
		SafeDelete(m_OldLetter);
	}

	void OldLetterPickup::Draw()
	{
		m_OldLetter->Draw();
	}

	float OldLetterPickup::GetWidth()
	{
		return m_OldLetter->GetWidth();
	}

	float OldLetterPickup::GetHeight()
	{
		return m_OldLetter->GetHeight();
	}

	PickupType OldLetterPickup::GetPickupType()
	{
		return PickupType_OldLetter;
	}
}