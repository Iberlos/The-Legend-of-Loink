#include "Game.h"


namespace GameDev2D
{
	Game::Game() :
		m_CameraTimer(CAMERA_TRANSITION_DURATION)
	{
		//Only initialize your member variables here - DON'T load any 
		//resources or create any objects that will be done in the Load method
		m_Link = nullptr;
		m_ActiveRegion = nullptr;
		m_TransitionRegion = nullptr;
		m_HeadsUpDisplay = nullptr;
		m_DebugDraw = nullptr;
		m_LoadStep = LoadTextures;
		m_GameState = StateLoading;
		m_ActiveRegion = 0;
		m_Cave = nullptr;
		m_IsWon = false;
	}

	Game::~Game()
	{
		//Delete the Link object
		SafeDelete(m_Link);

		//Delete the HUD
		SafeDelete(m_HeadsUpDisplay);

		//Delete the Debug Draw object
		SafeDelete(m_DebugDraw);

		for (int i = 0; i < NUM_REGIONS; i++)
		{
			SafeDelete(m_Regions[i]);
		}

		SafeDelete(m_Cave);

		//Unload the Link Texture
		UnloadTexture("Tileset");

		//Uload Audio
		UnloadAudio("BombDrop");
		UnloadAudio("BombExplode");
		UnloadAudio("Candle");
		UnloadAudio("DungeonDoorUnlock");
		UnloadAudio("DungeonKeyAppear");
		UnloadAudio("DungeonTheme-Loop");
		UnloadAudio("EnemyDeath");
		UnloadAudio("EnemyHit");
		UnloadAudio("Fanfare");
		UnloadAudio("HeartPickup");
		UnloadAudio("ItemPickup");
		UnloadAudio("LinkDeath");
		UnloadAudio("LinkHurt");
		UnloadAudio("LinkLowHealth");
		UnloadAudio("MagicalRod");
		UnloadAudio("OverworldTheme-Intro_01");
		UnloadAudio("OverworldTheme-Loop_01");
		UnloadAudio("Recorder");
		UnloadAudio("RupeePickup");
		UnloadAudio("Secret");
		UnloadAudio("ShieldDeflect");
		UnloadAudio("Sword");
		UnloadAudio("SwordShoot");
	}

	void Game::Update(double delta)
	{
		if (delta>=0.5)
		{
			delta = 0.5;
		}
		if (IsLoading() == true)
		{
			Load();
			return;
		}

		if (m_GameState == StateGame)
		{
			//Play music if paused & link is not dead
			if (m_Link->IsDead() == false && m_IsWon == false)
			{
				if (GetSoundManager()->IsAudioPlaying(Theme_Sound) == false)
				{
					GetSoundManager()->PlayAudio(Theme_Sound);
				}
			}
			else
			{
				float temp = m_EndFade->GetAlpha();
				m_EndFade->SetAlpha(m_EndFade->GetAlpha() + 1.0f/120);
			}
			if (m_Link->IsDead() == true && GetSoundManager()->IsAudioPlaying(Theme_Sound) == true)
			{
				GetSoundManager()->PauseAudio(Theme_Sound);
			}

			//Get the previous region
			Region* previousRegion = GetRegion(m_Link->GetPosition());

			//Block movement and set music if game is won
			if (m_IsWon == false)
			{
				//Update link
				m_Link->Update(delta);
			}else
			{
				if (m_Link->IsVilain()==true && (GetSoundManager()->IsAudioPlaying(Theme_Sound) == true || GetSoundManager()->IsAudioPlaying(DungeonTheme_Sound) == false))
				{
					//Update link one last time
					m_Link->Update(delta);
					m_Link->Pause();
					m_EndFade->SetColor(Color::BlackColor(0.0f));
					GetSoundManager()->PauseAudio(Theme_Sound);
					GetSoundManager()->PlayAudio(DungeonTheme_Sound);
				}
				if (m_Link->IsVilain() == false && (GetSoundManager()->IsAudioPlaying(Theme_Sound) == false || GetSoundManager()->IsAudioPlaying(DungeonTheme_Sound) == true))
				{
					//Update link one last time
					m_Link->Update(delta);
					m_Link->Pause();
					m_EndFade->SetColor(Color::WhiteColor(0.0f));
					GetSoundManager()->PauseAudio(DungeonTheme_Sound);
					GetSoundManager()->PlayAudio(Theme_Sound);
				}
				float temp = m_EndFade->GetAlpha();
				m_EndFade->SetAlpha(m_EndFade->GetAlpha() + 1.0f / 120);
			}


			//Get the current region
			Region* currentRegion = GetRegion(m_Link->GetPosition());

			//Is the current subsection different from the previous subsection
			if (currentRegion != nullptr && currentRegion != previousRegion)
			{
				ShiftCamera(currentRegion);
			}
			else if (currentRegion == previousRegion)
			{
				if (currentRegion->GetRow() == 0 && currentRegion->GetColumn() == 0)
				{
					if (currentRegion->GetTile(m_Link->GetPosition())->GetIndex() == 151)
					{
						m_Cave->SetCaveType(CaveType_OldLetter);
						SetState(StateCave);
						return;
					}
				}
				else if (currentRegion->GetRow() == 0 && currentRegion->GetColumn() == 1)
				{
					if (currentRegion->GetTile(m_Link->GetPosition())->GetIndex() == 148)
					{
						m_Cave->SetCaveType(CaveType_WoodSword);
						SetState(StateCave);
						return;
					}
				}
				else if (currentRegion->GetRow() == 1 && currentRegion->GetColumn() == 1)
				{
					if (currentRegion->GetTile(m_Link->GetPosition())->GetIndex() == 151)
					{
						m_Cave->SetCaveType(CaveType_Bombs);
						SetState(StateCave);
						return;
					}
				}
				else if (currentRegion->GetRow() == 1 && currentRegion->GetColumn() == 0)
				{
					if (currentRegion->GetTile(m_Link->GetPosition())->GetIndex() == 153)
					{
						m_Cave->SetCaveType(CaveType_Choose);
						SetState(StateCave);
						return;
					}
				}
				else if (currentRegion->GetRow() == 1 && currentRegion->GetColumn() == 5)
				{
					if (currentRegion->GetTile(m_Link->GetPosition())->GetIndex() == 103)
					{
						m_Cave->SetCaveType(CaveType_ETRed);
						SetState(StateCave);
						return;
					}
				}
				else if (currentRegion->GetRow() == 2 && currentRegion->GetColumn() == 2)
				{
					if (currentRegion->GetTile(m_Link->GetPosition())->GetIndex() == 104)
					{
						m_Cave->SetCaveType(CaveType_ETGreen);
						SetState(StateCave);
						return;
					}
				}
			}

			//Update the camera transition
			m_CameraTimer.Update(delta);
			if (m_CameraTimer.IsRunning() == true)
			{
				Vector2 deltaPosition = m_ActiveRegion->GetPosition() - m_TransitionRegion->GetPosition();
				Vector2 position = m_TransitionRegion->GetPosition() + deltaPosition * m_CameraTimer.GetPercentage();
				Vector2 halfScreenSize = Vector2(GetScreenWidth(), GetScreenHeight()) * 0.5f;
				Services::GetGraphics()->GetActiveCamera()->SetPosition(position + halfScreenSize);
			}
			else
			{
				m_TransitionRegion = nullptr;

				Vector2 position = m_ActiveRegion->GetPosition();
				Vector2 halfScreenSize = Vector2(GetScreenWidth(), GetScreenHeight()) * 0.5f;
				Services::GetGraphics()->GetActiveCamera()->SetPosition(position + halfScreenSize);
			}

			//Update the subsections
			m_ActiveRegion->Update(delta);
			if (m_TransitionRegion != nullptr)
			{
				m_TransitionRegion->Update(delta);
			}
		}
		else if (m_GameState == StateCave)
		{
			//Stop music if playing
			if (GetSoundManager()->IsAudioPlaying(Theme_Sound)==true)
			{
				GetSoundManager()->PauseAudio(Theme_Sound);
			}
			m_Link->Update(delta);
			if (m_Link->GetPosition().y <= 0.0f)
			{
				SetState(StateGame);
				return;
			}

			m_Cave->Update(delta);
		}
	}

	void Game::Draw()
	{
		if (IsLoading() == true)
		{
			Vector2 screenSize = Vector2(GetScreenWidth(), GetScreenHeight());

			//Draw a Black background
			Services::GetGraphics()->DrawRectangle(Vector2::Zero, screenSize, Rotation::Degrees(0.0f), Vector2::Zero, Color::BlackColor(), true);

			Vector2 loadingBarSize = Vector2(screenSize.x * 0.25f, screenSize.y * 0.06f);
			Vector2 loadingBarAnchor = Vector2(0.0f, 0.5f);
			Vector2 loadingBarPosition = Vector2((screenSize.x - loadingBarSize.x) * 0.5f, screenSize.y * 0.5f);

			//Draw the loading Bar outline
			Services::GetGraphics()->DrawRectangle(loadingBarPosition, loadingBarSize, Rotation::Degrees(0.0f), loadingBarAnchor, Color::WhiteColor(), false);

			float percentageLoaded = (float)m_LoadStep / (float)LoadStepCount;
			Vector2 innerBarSize = Vector2(loadingBarSize.x * percentageLoaded, loadingBarSize.y);
			Services::GetGraphics()->DrawRectangle(loadingBarPosition, innerBarSize, Rotation::Degrees(0.0f), loadingBarAnchor, Color::WhiteColor(), true);

			//Don't proceed with the rest of the Draw function until loading is complete
			return;
		}

		if (m_GameState == StateGame)
		{
			//Draw the active region
			if (Services::GetGraphics()->GetActiveCamera()->GetScale() == Vector2(1.0f, 1.0f))
			{
				//Update the subsections
				m_ActiveRegion->Draw();
				if (m_TransitionRegion != nullptr)
				{
					m_TransitionRegion->Draw();
				}
			}
			else
			{
				for (int i = 0; i < NUM_REGIONS; i++)
				{
					m_Regions[i]->Draw();
				}
			}
		}
		else if (m_GameState == StateCave)
		{
			m_Cave->Draw();
		}

		//Draw the debug Draw
		m_DebugDraw->Draw();

		//Draw Link
		m_Link->Draw();

		//Draw the HUD
		m_HeadsUpDisplay->Draw();

		//FadeScreen
		m_EndFade->Draw();
	}

	void Game::HandleLeftMouseClick(float mouseX, float mouseY)
	{
	}

	void Game::HandleRightMouseClick(float mouseX, float mouseY)
	{

	}

	void Game::HandleMouseMoved(float mouseX, float mouseY, float previousX, float previousY)
	{

	}

	void Game::HandleKeyPress(Keyboard::Key key)
	{
		Graphics* g = Services::GetGraphics();
		Vector2 halfScreenSize = Vector2(GetScreenWidth(), GetScreenHeight()) * 0.5f;

		if (key == Keyboard::One)
		{
			m_ActiveRegion = m_Regions[0];
			g->GetActiveCamera()->SetPosition(halfScreenSize);
		}
		if (key == Keyboard::Two)
		{
			m_ActiveRegion = m_Regions[1];
			g->GetActiveCamera()->SetPosition(halfScreenSize + Vector2(REGION_SIZE.x, 0.0f));
		}
		if (key == Keyboard::Three)
		{
			m_ActiveRegion = m_Regions[2];
			g->GetActiveCamera()->SetPosition(halfScreenSize + Vector2(REGION_SIZE.x * 2.0f, 0.0f));
		}
		if (key == Keyboard::Four)
		{
			m_ActiveRegion = m_Regions[3];
			g->GetActiveCamera()->SetPosition(halfScreenSize + Vector2(0.0f, REGION_SIZE.y));
		}
		if (key == Keyboard::Five)
		{
			m_ActiveRegion = m_Regions[4];
			g->GetActiveCamera()->SetPosition(halfScreenSize + REGION_SIZE);
		}
		if (key == Keyboard::Six)
		{
			m_ActiveRegion = m_Regions[5];
			g->GetActiveCamera()->SetPosition(halfScreenSize + Vector2(REGION_SIZE.x * 2.0f, REGION_SIZE.y));
		}
		if (key == Keyboard::Seven)
		{
			m_ActiveRegion = m_Regions[6];
			g->GetActiveCamera()->SetPosition(halfScreenSize + Vector2(0.0f, REGION_SIZE.y * 2.0f));
		}
		if (key == Keyboard::Eight)
		{
			m_ActiveRegion = m_Regions[7];
			g->GetActiveCamera()->SetPosition(halfScreenSize + Vector2(REGION_SIZE.x, REGION_SIZE.y * 2.0f));
		}
		if (key == Keyboard::Nine)
		{
			m_ActiveRegion = m_Regions[8];
			g->GetActiveCamera()->SetPosition(halfScreenSize + Vector2(REGION_SIZE.x * 2.0f, REGION_SIZE.y * 2.0f));
		}

		if (key == Keyboard::Q)
		{
			Vector2 scale = g->GetActiveCamera()->GetScale();
			scale *= 2.0f;
			g->GetActiveCamera()->SetScale(scale);
		}

		if (key == Keyboard::E)
		{
			Vector2 scale = g->GetActiveCamera()->GetScale();
			scale *= 0.5f;
			g->GetActiveCamera()->SetScale(scale);
		}

		if (key == Keyboard::Tab)
		{
			m_DebugDraw->ToggleState();
		}
	}

	void Game::Load()
	{
		switch (m_LoadStep)
		{
		case LoadTextures:
		{
			LoadTexture("Tileset");
			m_LoadStep = LoadLink;
		}
		break;

		case LoadLink:
		{
			m_Link = new Link(this);
			m_Link->SetPosition(LINK_INITIAL_POSITION);
			m_LoadStep = LoadDebugDrawing;
		}
		break;

		case LoadDebugDrawing:
		{
			m_DebugDraw = new DebugDraw(m_Link);
			m_LoadStep = LoadSoundFiles;
		}
		break;

		case LoadSoundFiles:
		{
			//Load audio
			LoadAudio("BombDrop");
			LoadAudio("BombExplode");
			LoadAudio("Candle");
			LoadAudio("DungeonDoorUnlock");
			LoadAudio("DungeonKeyAppear");
			LoadAudio("DungeonTheme-Loop");
			LoadAudio("EnemyDeath");
			LoadAudio("EnemyHit");
			LoadAudio("Fanfare");
			LoadAudio("HeartPickup");
			LoadAudio("ItemPickup");
			LoadAudio("LinkDeath");
			LoadAudio("LinkHurt");
			LoadAudio("LinkLowHealth");
			LoadAudio("MagicalRod");
			LoadAudio("OverworldTheme-Intro_01");
			LoadAudio("OverworldTheme-Loop_01");
			LoadAudio("Recorder");
			LoadAudio("RupeePickup");
			LoadAudio("Secret");
			LoadAudio("ShieldDeflect");
			LoadAudio("Sword");
			LoadAudio("SwordShoot");

			m_SoundManager = new LinkSoundManager();

			m_LoadStep = LoadRegion0_0;
		}
		break;

		case LoadRegion0_0:
		{
			m_Regions[0] = new Region(LEVEL_0_0, 0, 0,this);
			m_LoadStep = LoadRegion0_1;
		}
		break;

		case LoadRegion0_1:
		{
			m_Regions[1] = new Region(LEVEL_0_1, 0, 1, this);
			m_ActiveRegion = m_Regions[1];
			m_LoadStep = LoadRegion0_2;
		}
		break;

		case LoadRegion0_2:
		{
			m_Regions[2] = new Region(LEVEL_0_2, 0, 2, this);
			m_LoadStep = LoadRegion1_0;
		}
		break;

		case LoadRegion1_0:
		{
			m_Regions[3] = new Region(LEVEL_1_0, 1, 0, this);
			m_LoadStep = LoadRegion1_1;
		}
		break;

		case LoadRegion1_1:
		{
			m_Regions[4] = new Region(LEVEL_1_1, 1, 1, this);
			m_LoadStep = LoadRegion1_2;
		}
		break;

		case LoadRegion1_2:
		{
			m_Regions[5] = new Region(LEVEL_1_2, 1, 2, this);
			m_LoadStep = LoadRegion1_3;
		}
		break;

		case LoadRegion1_3:
		{
			m_Regions[6] = new Region(LEVEL_1_3, 1, 3, this);
			m_LoadStep = LoadRegion1_4;
		}
		break;
		case LoadRegion1_4:
		{
			m_Regions[7] = new Region(LEVEL_1_4, 1, 4, this);
			m_LoadStep = LoadRegion1_5;
		}
		break;
		case LoadRegion1_5:
		{
			m_Regions[8] = new Region(LEVEL_1_5, 1, 5, this);
			m_LoadStep = LoadRegion2_0;
		}
		break;

		case LoadRegion2_0:
		{
			m_Regions[9] = new Region(LEVEL_2_0, 2, 0, this);
			m_LoadStep = LoadRegion2_1;
		}
		break;

		case LoadRegion2_1:
		{
			m_Regions[10] = new Region(LEVEL_2_1, 2, 1, this);
			m_LoadStep = LoadRegion2_2;
		}
		break;

		case LoadRegion2_2:
		{
			m_Regions[11] = new Region(LEVEL_2_2, 2, 2, this);
			m_LoadStep = LoadHUD;
		}
		break;

		case LoadHUD:
		{
			//Create the Heads up display
			m_HeadsUpDisplay = new HeadsUpDisplay(m_Link);
			m_LoadStep = LoadCave;
		}
		break;

		case LoadCave:
		{
			//Create the Cave Region
			m_Cave = new Cave(m_Link, this);
			m_LoadStep = LoadFinalize;
		}
		break;

		case LoadFinalize:
		{
			//Set the camera
			Vector2 halfScreenSize = Vector2(GetScreenWidth(), GetScreenHeight()) * 0.5f;
			Services::GetGraphics()->GetActiveCamera()->SetPosition(halfScreenSize + m_ActiveRegion->GetPosition());
			//Screen Fade out Not sure of were should I put it so it is here
			m_EndFade = new Polygon();
			m_EndFade->MakeRectangle(GetScreenWidth(), GetScreenHeight(), true);
			m_EndFade->SetColor(Color::BlackColor(0.0f));
			m_EndFade->SetAnchor(Vector2(0.5f,0.5f));
			m_EndFade->AttachTo(Services::GetGraphics()->GetActiveCamera());
			//This is the last load step, this time we are changing the game state
			m_GameState = StateGame;
		}
		break;
		}
	}

	bool Game::IsLoading()
	{
		return m_GameState == StateLoading;
	}

	void Game::CheckRegionTrees()
	{
		bool allTreesBurned = false;
		for (int i = 0; i < NUM_REGIONS; i++)
		{
			allTreesBurned = m_Regions[i]->CheckTrees();
			if (allTreesBurned == false)
			{
				break;
			}
		}
		if (allTreesBurned == true)
		{
			for (int i = 0; i < NUM_REGIONS; i++)
			{
				m_Regions[i]->ChangeToDesert();
			}
			m_Link->SetHasBracelet(true);
			m_Link->SetIsVilain(true);
			m_SoundManager->PlayAudio(Secret_Sound);
		}
	}

	bool Game::IsWon()
	{
		return m_IsWon;
	}

	void Game::SetIsWon(bool isWon)
	{
		GetSoundManager()->PlayAudio(Item_Sound);
		m_IsWon = isWon;
	}

	LinkSoundManager * Game::GetSoundManager()
	{
		return m_SoundManager;
	}

	Region* Game::GetRegion(const Vector2& aPosition)
	{
		if (m_GameState == StateGame)
		{
			int regionWidth = NUM_COLUMNS * TILE_SIZE;
			int regionHeight = NUM_ROWS * TILE_SIZE;
			int row = aPosition.y / regionHeight;
			int column = aPosition.x / regionWidth;
			int index = -1;
			if (row==1 && (column == 3||column==4|| column == 5))//Fixing the fact that I changed the region array
			{
				index = column + (row * NUM_REGION_COLUMNS);
			}
			else if (row==2)
			{
				index = column + (row * NUM_REGION_COLUMNS)+3;
			}
			else
			{
				index = column + (row * NUM_REGION_COLUMNS);
			}//End of fix
			if (index >= 0 && index < NUM_REGIONS)
			{
				return m_Regions[index];
			}
		}
		else if (m_GameState == StateCave)
		{
			return m_Cave;
		}
		return nullptr;
	}

	void Game::ShiftCamera(Region* region)
	{
		//Setup for transition
		m_TransitionRegion = m_ActiveRegion;
		m_ActiveRegion = region;

		//Reset and Start the Camera
		m_CameraTimer.Reset();
		m_CameraTimer.Start();
	}
	void Game::SetState(GameState state)
	{
		m_GameState = state;

		Vector2 halfScreenSize = Vector2(GetScreenWidth(), GetScreenHeight()) * 0.5f;

		if (m_GameState == StateCave)
		{
			Services::GetGraphics()->GetActiveCamera()->SetPosition(halfScreenSize);
			m_Link->SetPosition(Vector2(halfScreenSize.x, TILE_SIZE)); //(512,64)
		}
		else if (m_GameState == StateGame)
		{
			Vector2 position = m_ActiveRegion->GetPosition();
			Services::GetGraphics()->GetActiveCamera()->SetPosition(position + halfScreenSize);
			if (m_ActiveRegion->GetRow() == 0 && m_ActiveRegion->GetColumn() == 0)
			{
				const int index = 151;
				int row = index / NUM_COLUMNS;
				int column = index % NUM_COLUMNS;
				Vector2 tilePosition = Vector2(column, row) * TILE_SIZE;
				Vector2 offset = Vector2(TILE_SIZE * 0.5f, -1.0f);
				m_Link->SetPosition(position + tilePosition + offset);

				//If Link leaves the cave with the old letter, then the cave is cleared
				if (m_Cave->GetTile(71)->HasPickup() == false)
				{
					m_Cave->SetCaveCleared();
				}
			}
			else if (m_ActiveRegion->GetRow() == 0 && m_ActiveRegion->GetColumn() == 1)
			{
				const int index = 148;
				int row = index / NUM_COLUMNS;
				int column = index % NUM_COLUMNS;
				Vector2 tilePosition = Vector2(column, row) * TILE_SIZE;
				Vector2 offset = Vector2(TILE_SIZE * 0.5f, -1.0f);
				m_Link->SetPosition(position + tilePosition + offset);

				//If Link leaves the cave with the sword, then the cave is cleared
				if (m_Cave->GetTile(71)->HasPickup() == false)
				{
					m_Cave->SetCaveCleared();
				}
			}
			else if (m_ActiveRegion->GetRow() == 1 && m_ActiveRegion->GetColumn() == 1)
			{
				const int index = 151;
				int row = index / NUM_COLUMNS;
				int column = index % NUM_COLUMNS;
				Vector2 tilePosition = Vector2(column, row) * TILE_SIZE;
				Vector2 offset = Vector2(TILE_SIZE * 0.5f, -1.0f);
				m_Link->SetPosition(position + tilePosition + offset);

				//If Link leaves the cave with the bombs, then the cave is cleared
				if (m_Cave->GetTile(71)->HasPickup() == false)
				{
					m_Cave->SetCaveCleared();
				}
			}
			else if (m_ActiveRegion->GetRow() == 1 && m_ActiveRegion->GetColumn() == 0)
			{
				const int index = 153;
				int row = index / NUM_COLUMNS;
				int column = index % NUM_COLUMNS;
				Vector2 tilePosition = Vector2(column, row) * TILE_SIZE;
				Vector2 offset = Vector2(TILE_SIZE * 0.5f, -1.0f);
				m_Link->SetPosition(position + tilePosition + offset);

				//If Link leaves the cave with the bombs, then the cave is cleared
				if (m_Cave->GetTile(71)->HasPickup() == false)
				{
					m_Cave->SetCaveCleared();
				}
			}
			else if (m_ActiveRegion->GetRow() == 1 && m_ActiveRegion->GetColumn() == 5)
			{
				const int index = 103;
				int row = index / NUM_COLUMNS;
				int column = index % NUM_COLUMNS;
				Vector2 tilePosition = Vector2(column, row) * TILE_SIZE;
				Vector2 offset = Vector2(TILE_SIZE * 0.5f, -1.0f);
				m_Link->SetPosition(position + tilePosition + offset);

				//If Link leaves the cave with the bombs, then the cave is cleared
				if (m_Cave->GetTile(71)->HasPickup() == false)
				{
					m_Cave->SetCaveCleared();
				}
			}
			else if (m_ActiveRegion->GetRow() == 2 && m_ActiveRegion->GetColumn() == 2)
			{
				const int index = 104;
				int row = index / NUM_COLUMNS;
				int column = index % NUM_COLUMNS;
				Vector2 tilePosition = Vector2(column, row) * TILE_SIZE;
				Vector2 offset = Vector2(TILE_SIZE * 0.5f, -1.0f);
				m_Link->SetPosition(position + tilePosition + offset);

				//If Link leaves the cave with the bombs, then the cave is cleared
				if (m_Cave->GetTile(71)->HasPickup() == false)
				{
					m_Cave->SetCaveCleared();
				}
			}
		}
	}
}