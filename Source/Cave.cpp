#include "Cave.h"
#include "Constants.h"
#include "Link.h"


namespace GameDev2D
{
	Cave::Cave(Link* link, Game* game) : Region(CAVE, 0, 0, game)
	{
		m_Link = link;
		//Initialize the cave type
		m_CaveType = CaveType_WoodSword;

		//Initially all the caves are not cleared
		for (int i = 0; i < CaveType_Count; i++)
		{
			m_IsCaveCleared[i] = false;
		}

		//Add Fire
		SpawnEnemyAtIndex(100, Enemy_Fire);
		SpawnEnemyAtIndex(107, Enemy_Fire);

		m_OldMan = new SpriteAtlas("Tileset");
		m_OldMan->SetAnchor(Vector2(0.5f,0.5f));
		m_OldMan->SetPosition(Vector2(512.0f,384.0f));

		LoadFont("slkscr_42");

		m_Text = new SpriteFont("slkscr_42");
		m_Text->SetAnchor(Vector2(0.5f, 0.5f));
		m_Text->SetPosition(Vector2(512.0f, 512.0f));
		m_Text->SetJustification(SpriteFont::JustifyCenter);
		m_Text->SetColor(Color::WhiteColor());
	}
	Cave::~Cave()
	{
		SafeDelete(m_OldMan);
		SafeDelete(m_Text);
		UnloadFont("slkscr_42");
	}

	void Cave::SetCaveType(CaveType aCaveType)
	{
		//Set the cave type
		m_CaveType = aCaveType;
		m_OldMan->SetAlpha(1.0f);

		//Remove any pickups in the caves
		//GetTile(69)->RemovePickup();
		GetTile(71)->RemovePickup();
		//GetTile(74)->RemovePickup();

		//Setup the wood sword cave
		if (m_CaveType == CaveType_WoodSword)
		{
			m_OldMan->SetScale(Vector2(1.0f, 1.0f));
			m_Text->SetColor(Color::WhiteColor());
			if (m_IsCaveCleared[m_CaveType] == false)
			{
				m_OldMan->UseFrame("OldMan");
				Tile* tile = GetTile(71);
				tile->SetPickup(PickupType_WoodSword);
				m_Text->SetText("Go north to find my brother!\nTake this with you!");
			}
			else if (m_Link->IsVilain() == true)
			{
				m_OldMan->UseFrame("OldMan");
				m_Text->SetText("How Could You Loink??!!");
			}
		}
		else if (m_CaveType == CaveType_Bombs)
		{
			m_OldMan->SetScale(Vector2(1.0f, 1.0f));
			m_Text->SetColor(Color::WhiteColor());
			if (m_IsCaveCleared[m_CaveType] == false)
			{
				m_OldMan->UseFrame("OldMan");
				Tile* tile = GetTile(71);
				tile->SetPickup(PickupType_Bombs);
				m_Text->SetText("Go west to find my brother\'s hideout!\nTake these, but be carefull!");
			}
			else if (m_Link->IsVilain() == true)
			{
				m_OldMan->UseFrame("OldMan");
				m_Text->SetText("Now The Evil Has Won...");
			}
		}
		else if (m_CaveType == CaveType_OldLetter)
		{
			m_OldMan->SetScale(Vector2(1.0f, 1.0f));
			m_Text->SetColor(Color::WhiteColor());
			if (m_IsCaveCleared[m_CaveType] == false)
			{
				m_OldMan->UseFrame("OldLady");
				Tile* tile = GetTile(71);
				tile->SetPickup(PickupType_OldLetter);
				m_Text->SetText("My brother to the north \n must feel lonly,\n give him this to cheer him up!");
			}
			else if (m_Link->IsVilain() == true)
			{
				m_OldMan->UseFrame("OldLady");
				m_Text->SetText("Well Done Loink.. Now Hope Is No More...");
			}
		}
		else if (m_CaveType == CaveType_Choose)
		{
			m_OldMan->UseFrame("OldMan");
			m_OldMan->SetScale(Vector2(1.0f, 1.0f));
			m_Text->SetColor(Color::WhiteColor());
			m_HasRequiredItem = m_Link->HasOldLetter();
			if (m_IsCaveCleared[m_CaveType] == false)
			{
				if (m_HasRequiredItem)//ask the Hud if link has the love leter
				{
					Tile* tile = GetTile(71);
					tile->SetPickup(PickupType_Bracelet);
					tile = GetTile(72);
					tile->SetPickup(PickupType_Candle);
					m_Text->SetText("Thank you young man!\nChoose a reward!\nBut maybe you should head north before choosing...");
				}
				else
				{
					m_Text->SetText("I wonder how is the Old Lady doing...");
				}
			}
			else if (m_Link->IsVilain() == true)
			{
				m_OldMan->UseFrame("OldMan");
				m_Text->SetText("I Hope The Evil Paid You Well \n For Your Betrail...");
			}
		}
		else if (m_CaveType == CaveType_ETRed)
		{
			m_Text->SetColor(Color::WhiteColor());
			if (m_IsCaveCleared[m_CaveType] == false && m_Link->IsVilain()==false)
			{
				m_OldMan->UseFrame("OldMan");
				m_OldMan->SetScale(Vector2(1.0f, 1.0f));
				m_OldMan->SetAlpha(0.0f);
				Tile* tile = GetTile(71);
				tile->SetPickup(PickupType_Candle);
				m_Text->SetText("");
			}
			else if (m_Link->IsVilain() == true)
			{
				m_OldMan->UseFrame("Ganon");
				m_OldMan->SetScale(Vector2(0.4f, 0.4f));
				m_Text->SetColor(Color::RedColor());
				m_Text->SetText("Go My Minion, Get The \nTriforce Of Courage That I Locked Away \nAnd Help Me Bring Havock \nTo The World!!!");
			}
		}
		else if (m_CaveType == CaveType_ETGreen)
		{
			if (m_IsCaveCleared[m_CaveType] == false)
			{
				m_OldMan->UseFrame("OldMan");
				m_OldMan->SetAlpha(0.0f);
				Tile* tile = GetTile(71);
				tile->SetPickup(PickupType_Triforce);
				m_Text->SetText("");
			}
		}
	}

	void Cave::SetCaveCleared()
	{
		if (m_CaveType == CaveType_Choose)
		{
			if (m_HasRequiredItem==true)
			{
				//Clear the cave
				m_IsCaveCleared[m_CaveType] = true;

				//Remove the pickups
				GetTile(71)->RemovePickup();
				GetTile(72)->RemovePickup();
				m_HasRequiredItem = false;
				m_Link->SetHasOldLetter(false);
			}
		}
		else
		{
			//Clear the cave
			m_IsCaveCleared[m_CaveType] = true;

			//Remove the pickups
			GetTile(71)->RemovePickup();
		}
	}

	void Cave::Draw()
	{
		Region::Draw();
		if (m_CaveType == CaveType_Choose)
		{
			if (m_HasRequiredItem==false && m_IsCaveCleared[m_CaveType]==false)
			{
				m_OldMan->Draw();
				m_Text->Draw();
			}
			else
			{
				if (GetTile(71)->HasPickup() == true && GetTile(72)->HasPickup() == true)
				{
					m_OldMan->Draw();
					m_Text->Draw();
				}
				else
				{
					if (m_IsCaveCleared[m_CaveType]==false)
					{
						SetCaveCleared();
					}
				}
			}
		}
		else
		{
			if (GetTile(71)->HasPickup() == true)
			{
				m_OldMan->Draw();
				m_Text->Draw();
			}
		}
		if (m_Link->IsVilain())
		{
			m_OldMan->Draw();
			m_Text->Draw();
		}
	}
}