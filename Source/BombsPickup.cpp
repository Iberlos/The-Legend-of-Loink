#include "BombsPickup.h"
#include "Framework\Events\UpdateEvent.h"
#include "Region.h"
#include "Game.h"

namespace GameDev2D
{
	BombsPickup::BombsPickup(Tile* tile) : Pickup(tile), EventHandler(), m_Fuse(1.0)
	{
		m_Bombs = new SpriteAtlas("Tileset");
		m_Bombs->UseFrame("Bomb");
		m_Bombs->SetAnchor(Vector2(0.5f, 0.5f));
		m_Bombs->AttachTo(this);

		m_IsArmed = false;

		Services::GetApplication()->AddEventListener(this, UPDATE_EVENT);
	}

	BombsPickup::~BombsPickup()
	{
		SafeDelete(m_Bombs);

		Services::GetApplication()->RemoveEventListener(this, UPDATE_EVENT);
	}

	void BombsPickup::Draw()
	{
		m_Bombs->Draw();
	}

	float BombsPickup::GetWidth()
	{
		return m_Bombs->GetWidth();
	}

	float BombsPickup::GetHeight()
	{
		return m_Bombs->GetHeight();
	}

	PickupType BombsPickup::GetPickupType()
	{
		return PickupType_Bombs;
	}
	void BombsPickup::HandleEvent(Event * event)
	{
		if (event->GetEventCode() == UPDATE_EVENT)
		{
			UpdateEvent* updateEvent = (UpdateEvent*)event;
			double delta = updateEvent->GetDelta();

			if (m_Fuse.IsRunning() == true)
			{
				m_Fuse.Update(delta);

				//Fuse is done explode the bomb
				if (m_Fuse.GetPercentage() == 1.0f)
				{
					Region* region = GetTile()->GetRegion();
					bool removePickup = true;
					if (region->GetRow() == 0 && region->GetColumn() == 0)
					{
						//Play bom explosion
						GetTile()->GetRegion()->GetGame()->GetSoundManager()->PlayAudio(BombExplosion_Sound);
						if (GetTile()->GetIndex() == 151)
						{
							region->GetGame()->GetSoundManager()->PlayAudio(Secret_Sound);
							region->SetTileAtIndex(151, TileType_Cave, TileVariant_0, TileColor_Primary, true);
							removePickup = false;
						}
						if (removePickup == true)
						{
							GetTile()->RemovePickup();
						}

						//Camera explosion 
						Services::GetGraphics()->GetActiveCamera()->Shake(2.5, 0.5);
					}
					if (region->GetRow()==1 && region->GetColumn()==0)
					{
						//Play bom explosion
						GetTile()->GetRegion()->GetGame()->GetSoundManager()->PlayAudio(BombExplosion_Sound);
						if (GetTile()->GetIndex() == 153)
						{
							region->GetGame()->GetSoundManager()->PlayAudio(Secret_Sound);
							region->SetTileAtIndex(153, TileType_Cave, TileVariant_0, TileColor_Primary, true);
							removePickup = false;
						}
						if (removePickup == true)
						{
							GetTile()->RemovePickup();
						}
						//Camera explosion 
						Services::GetGraphics()->GetActiveCamera()->Shake(2.5, 0.5);
					}
				}
			}
		}
	}
	void BombsPickup::Arm()
	{
		m_IsArmed = true;
		m_Fuse.Reset();
		m_Fuse.Start();
	}
	bool BombsPickup::IsArmed()
	{
		return m_IsArmed;
	}
}