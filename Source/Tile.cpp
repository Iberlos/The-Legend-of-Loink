#include "Tile.h"
#include "WoodSwordPickup.h"
#include "OldLetterPickup.h"
#include "PowerBraceletPickup.h"
#include "BombsPickup.h"
#include "CandlePickup.h"
#include "TriforcePickup.h"
#include "Region.h"


namespace GameDev2D
{
	Tile::Tile(int index)
	{
		m_Index = index;
		SetPosition(Vector2(GetColumn() * GetWidth(), GetRow() * GetHeight()));

		m_Variant = TileVariant_0;
		m_Color = TileColor_Primary;
		m_Pickup = nullptr;
		m_Region = nullptr;
	}

	Tile::~Tile()
	{
		RemovePickup();
	}

	void Tile::Update(double delta)
	{
	}

	float Tile::GetWidth()
	{
		return TILE_SIZE;
	}
	float Tile::GetHeight()
	{
		return TILE_SIZE;
	}
	bool Tile::IsWalkable()
	{
		return true; //By default every tile is walkable
	}

	int Tile::GetIndex()
	{
		return m_Index;
	}

	int Tile::GetRow()
	{
		return m_Index / NUM_COLUMNS;
	}

	int Tile::GetColumn()
	{
		return m_Index % NUM_COLUMNS;
	}
	Vector2 Tile::GetCenter()
	{
		return GetTransformMatrix().GetTranslation() + Vector2(GetWidth() * 0.5f, GetHeight() * 0.5f);
	}
	void Tile::SetVariant(TileVariant variant)
	{
		m_Variant = variant;
		RefreshSprite();
	}

	TileVariant Tile::GetVariant()
	{
		return m_Variant;
	}

	void Tile::SetColor(TileColor color)
	{
		m_Color = color;
		RefreshSprite();
	}

	TileColor Tile::GetColor()
	{
		return m_Color;
	}

	void Tile::RefreshSprite()
	{
		//Override this method for Tile's that have a variant
	}
	Pickup * Tile::GetPickup()
	{
		return m_Pickup;
	}
	void Tile::SetPickup(PickupType pickupType)
	{
		if (HasPickup() == false)
		{
			if (pickupType == PickupType_WoodSword)
			{
				m_Pickup = new WoodSwordPickup(this);
			}
			else if (pickupType == PickupType_Bombs)
			{
				m_Pickup = new BombsPickup(this);
			}
			else if (pickupType == PickupType_OldLetter)
			{
				m_Pickup = new OldLetterPickup(this);
			}
			else if (pickupType == PickupType_Bracelet)
			{
				m_Pickup = new PowerBraceletPickup(this);
			}
			else if (pickupType == PickupType_Candle)
			{
				m_Pickup = new CandlePickup(this);
			}else if(pickupType == PickupType_Triforce)
			{
				m_Pickup = new TriforcePickup(this);
			}
		}
	}

	void Tile::RemovePickup()
	{
		SafeDelete(m_Pickup);
	}

	bool Tile::HasPickup()
	{
		return m_Pickup != nullptr;
	}

	void Tile::SetRegion(Region * region)
	{
		m_Region = region;
	}

	Region * Tile::GetRegion()
	{
		return m_Region;
	}
}