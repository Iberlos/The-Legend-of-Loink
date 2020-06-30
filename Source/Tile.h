#pragma once

#include <GameDev2D.h>
#include "Constants.h"
#include "Pickup.h"


namespace GameDev2D
{
	class Region;

	class Tile : public Drawable
	{
	public:
		Tile(int index);
		virtual ~Tile();

		virtual void Update(double delta);
		virtual void Draw() = 0;

		virtual TileType GetTileType() = 0;

		virtual float GetWidth() override;
		virtual float GetHeight() override;

		virtual bool IsWalkable();

		virtual int GetIndex();
		virtual int GetRow();
		virtual int GetColumn();

		virtual Vector2 GetCenter();

		virtual void SetVariant(TileVariant variant);
		virtual TileVariant GetVariant();

		virtual void SetColor(TileColor color);
		virtual TileColor GetColor();

		virtual void RefreshSprite();

		virtual Pickup* GetPickup();
		virtual void SetPickup(PickupType pickupType);
		virtual void RemovePickup();
		virtual bool HasPickup();

		virtual void SetRegion(Region* region);
		virtual Region* GetRegion();

	private:
		int m_Index;
		TileVariant m_Variant;
		TileColor m_Color;
		Pickup* m_Pickup;
		Region* m_Region;
	};
}