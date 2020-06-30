#include "Fire.h"
#include "Region.h"
#include "Tile.h"
#include "Game.h"

namespace GameDev2D
{
	Fire::Fire(Region* region):m_SpreadTimer(3.0f)
	{
		m_CanSpread = true;
		m_DeleteMe = false;
		m_Region = region;
		m_Fire = new AnimatedSprite("Tileset");
		m_Fire->AddFrame("Fire-1");
		m_Fire->AddFrame("Fire-2");
		m_Fire->SetAnchor(Vector2(0.5f,0.5f));
		m_Fire->AttachTo(this);
		m_Fire->SetDoesLoop(true);
		m_Fire->SetFrameSpeed(8.0f);
		m_SpreadTimer.Start();
	}
	Fire::~Fire()
	{
		SafeDelete(m_Fire);
	}
	void Fire::Draw()
	{
		m_Fire->Draw();
	}
	float Fire::GetWidth()
	{
		return m_Fire->GetWidth();
	}
	float Fire::GetHeight()
	{
		return m_Fire->GetHeight();
	}
	EnemyType Fire::GetEnemyType()
	{
		return Enemy_Fire;
	}
	float Fire::GetCollisionRadius()
	{
		return GetWidth()*0.5f;
	}
	int Fire::GetAttackDamage()
	{
		return 1;
	}
	void Fire::Update(double delta)
	{
		m_Region->GetTile(GetPosition());
		//Check if someone is playing audio and play
		if (m_Region->GetGame()->GetSoundManager()->IsAudioPlaying(Fire_Sound) == false)
		{
			m_Region->GetGame()->GetSoundManager()->PlayAudio(Fire_Sound);
		}

		if (m_CanSpread && m_SpreadTimer.IsRunning() == false)
		{
			m_CanSpread = false;
			bool willSpread = false;
			for (int i = -1; i <= 1; i++)
			{
				for (int j = -1; j <= 1; j++)
				{
					if (m_Region->GetTile(GetPosition() + Vector2(i * 64, j * 64)) == nullptr)
					{
						continue;
					}
					if (m_Region->GetTile(GetPosition() + Vector2(i * 64, j * 64))->GetTileType() == TileType_Tree || m_Region->GetTile(GetPosition() + Vector2(i * 64, j * 64))->GetTileType() == TileType_Bridge)
					{
						Tile* spreadTile = m_Region->GetTile(GetPosition() + Vector2(i * 64, j * 64));
						if (spreadTile->GetColor()!=TileColor_Secondary)
						{
							willSpread = true;
							for (int k = 0; k<m_Region->GetNumberOfEnemies(); k++)
							{
								if (m_Region->GetEnemy(k) != nullptr)
								{
									if (m_Region->GetEnemy(k)->GetPosition().DistanceSquared(spreadTile->GetCenter())<10*10)
									{
										willSpread = false;
									}
								}
							}
							if (willSpread == true)
							{
								m_Region->SpawnEnemyAtIndex(spreadTile->GetIndex(), Enemy_Fire);
								m_SpreadTimer.Reset();
								m_SpreadTimer.Start();
								m_CanSpread = true;
							}
						}
					}
				}
			}
		}
		else
		{
			if (m_SpreadTimer.IsRunning()==true)
			{
				m_SpreadTimer.Update(delta);
			}
			else
			{
				if ((m_Region->GetRow() == 0 && m_Region->GetColumn() == 0) || (m_Region->GetRow() == 1 && m_Region->GetColumn() == 4) || (m_Region->GetRow() == 1 && m_Region->GetColumn() == 5))
				{
					//in these regions don't do anything just hang there
				}
				else
					if (m_Region->GetRow() == 2 && m_Region->GetColumn() == 1) //Trap area, burn trees and desapear but burn bridge and hang there
					{
						if (m_Region->GetTile(GetPosition())->GetTileType() == TileType_Tree)
						{
							m_Region->SetTileAtIndex(m_Region->GetTile(GetPosition())->GetIndex(), TileType_Sand, TileVariant_0, TileColor_Primary, true);
							m_DeleteMe = true;
						}
						else if (m_Region->GetTile(GetPosition())->GetTileType() != TileType_Bridge)
						{
							m_DeleteMe = true;
						}
					}
					else
					{//All other areas, conver tree into burned tree and set delete flag
						if (m_Region->GetTile(GetPosition())->GetTileType() == TileType_Tree)
						{
							m_Region->SetTileAtIndex(m_Region->GetTile(GetPosition())->GetIndex(), TileType_Tree, TileVariant_0, TileColor_Secondary, true);
							m_DeleteMe = true;
						}
						else if (m_Region->GetTile(GetPosition())->GetTileType() != TileType_Bridge)
						{
							m_DeleteMe = true;
						}
					}
				if (m_Region->GetRow() == 0 && m_Region->GetColumn() == 2)
				{
					if (m_Region->GetTile(GetPosition())->GetIndex() == 86)
					{
						//m_Region->SetTileAtIndex(86, TileType_Sand, TileVariant_0, TileColor_Primary, true);
						m_Region->GetTile(GetPosition())->SetPickup(PickupType_Bombs);
						m_Region->GetGame()->GetSoundManager()->PlayAudio(Secret_Sound);
					}
				}
				if (m_DeleteMe == true)
				{
					m_Region->GetGame()->GetSoundManager()->PauseAudio(Fire_Sound);
				}
			}
		}
	}
	bool Fire::DeleteMe()
	{
		return m_DeleteMe;
	}
}
