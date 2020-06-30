#include "Link.h"
#include "Constants.h"
#include "Game.h"
#include "BombsPickup.h"
#include <fstream>
#include "Enemy.h"


namespace GameDev2D
{
	Link::Link(Game* game) : Drawable(),
		m_Direction(LinkDown),
		m_AttackTimer(LINK_ATTACK_DURATION), m_BombDelay(0.5), m_CandleDelay(1.0), m_DehidrationTimer(2.0)
    {
        //Keyframes array
        std::string animationKeys[] = { "LinkLeft-", "LinkRight-", "LinkUp-", "LinkDown-" };
        std::string frameKeys[] = { "LinkAttack-Left", "LinkAttack-Right", "LinkAttack-Up", "LinkAttack-Down" };
        Vector2 anchorPoints[] = { Vector2(0.7f, 0.5f), Vector2(0.3f, 0.5f), Vector2(0.5f, 0.3f), Vector2(0.5f, 0.675f) };

        //Create and initialize the AnimatedSprite objects
        for (int i = 0; i < NUMBER_OF_LINK_DIRECTIONS; i++)
        {
            m_Animations[i] = new AnimatedSprite("Tileset");
            m_Animations[i]->AddFrame(std::string(animationKeys[i] + "1"));
            m_Animations[i]->AddFrame(std::string(animationKeys[i] + "2"));
            m_Animations[i]->SetFrameSpeed(4.0f);
            m_Animations[i]->SetDoesLoop(true);
            m_Animations[i]->SetAnchor(Vector2(0.5f, 0.5f));

            m_Attacks[i] = new SpriteAtlas("Tileset");
            m_Attacks[i]->UseFrame(frameKeys[i]);
            m_Attacks[i]->SetAnchor(anchorPoints[i]);
        }

		m_HasSword = false;
		m_HasOldLetter = false;
		m_HasBraceletOfPower = false;
		m_HasCandle = false;
		m_IsDead = false;
		m_IsVilain = false;
		m_NumBombs = 0;
		m_Game = game;
		m_Health = LINK_INITIAL_HEALTH;

        //Load Link's position and direction from the last time
        //Load();
    }

    Link::~Link()
    {
        //Save Link's current position and direction to the HDD
        //Save();

        //Delete the AnimatedSprite objects AND the SpriteAtlas objects
        for (int i = 0; i < NUMBER_OF_LINK_DIRECTIONS; i++)
        {
            SafeDelete(m_Animations[i]);
            SafeDelete(m_Attacks[i]);
        }
    }

    void Link::Update(double delta)
    {
		if (m_IsDead == false)
		{
			//Check health and play audio if low health
			if (m_Health <= 3 && m_Game->GetSoundManager()->IsAudioPlaying(LowHealth_Sound) == false)
			{
				m_Game->GetSoundManager()->PlayAudio(LowHealth_Sound);
			}
			else if (m_Health >= 3)
			{
				m_Game->GetSoundManager()->PauseAudio(LowHealth_Sound);
			}

			//Pause the animations, they'll be resumed below if any key is pressed
			Pause();

			//Update the attack timer
			m_AttackTimer.Update(delta);

			//Update bomb delay timer
			m_BombDelay.Update(delta);
			m_CandleDelay.Update(delta);
			m_DehidrationTimer.Update(delta);

			//Is Link attacking
			if (IsKeyDown(Keyboard::Spacebar) == true && IsAttacking() == false && HasSword() == true)
			{
				//play sword sound
				m_Game->GetSoundManager()->PlayAudio(Sword_Sound);
				m_AttackTimer.Reset();
				m_AttackTimer.Start();
			}
			else if (IsKeyDown(Keyboard::B) == true && m_BombDelay.IsRunning() == false && m_NumBombs > 0)
			{
				//link can place bomb
				Region* region = m_Game->GetRegion(GetPosition());
				Tile* tile = region->GetTile(GetPosition());
				int row = tile->GetRow();
				int column = tile->GetColumn();
				Vector2 linkDirection = LINK_DIRECTIONS[m_Direction];
				int bombRow = row + linkDirection.y;
				int bombColumn = column + linkDirection.x;

				Tile* bombTile = region->GetTile(bombRow, bombColumn);
				if (bombTile != nullptr)
				{
					if (bombTile->HasPickup() == true)
					{
						bombTile->RemovePickup();
					}

					bombTile->SetPickup(PickupType_Bombs);
					// bomb drop sound
					m_Game->GetSoundManager()->PlayAudio(BombDrop_Sound);

					BombsPickup* bomb = (BombsPickup*)bombTile->GetPickup();
					bomb->Arm();

					m_BombDelay.Reset();
					m_BombDelay.Start();

					m_NumBombs--;
				}
			}
			else if (IsKeyDown(Keyboard::R) == true)
			{
				m_Health = 6;
			}
			else if (IsKeyDown(Keyboard::C) == true && m_CandleDelay.IsRunning() == false && m_HasCandle == true)
			{
				//link can place bomb
				Region* region = m_Game->GetRegion(GetPosition());
				Tile* tile = region->GetTile(GetPosition());
				int row = tile->GetRow();
				int column = tile->GetColumn();
				Vector2 linkDirection = LINK_DIRECTIONS[m_Direction];
				int candleRow = row + linkDirection.y;
				int candleColumn = column + linkDirection.x;

				Tile* candleTile = region->GetTile(candleRow, candleColumn);
				if (region->GetTile(candleRow, candleColumn) != nullptr)
				{
					region->SpawnEnemyAtIndex(region->GetTile(candleRow, candleColumn)->GetIndex(), Enemy_Fire);
				}


				if (candleTile != nullptr)
				{
					if (candleTile->HasPickup() == true)
					{
						candleTile->RemovePickup();
					}
					m_CandleDelay.Reset();
					m_CandleDelay.Start();
				}
			}
			else
			{
				//Get Link's position before movement and the tile he's on
				Vector2 previousPosition = GetPosition();
				Tile* previousTile = m_Game->GetRegion(previousPosition)->GetTile(previousPosition);
				//Is the left key down
				if (IsKeyDown(Keyboard::Left) == true)
				{
					Move(LinkLeft, delta);
				}

				//Is the right key down
				else if (IsKeyDown(Keyboard::Right) == true)
				{
					Move(LinkRight, delta);
				}

				//Is the up key down
				else if (IsKeyDown(Keyboard::Up) == true)
				{
					Move(LinkUp, delta);
				}

				//Is the down key down
				else if (IsKeyDown(Keyboard::Down) == true)
				{
					Move(LinkDown, delta);
				}

				//get tile link is on afte the movemnt
				std::vector<Vector2> offsets = { LINK_COLISION_OFFSETS[m_Direction].first, LINK_COLISION_OFFSETS[m_Direction].second };
				for (int i = 0; i < offsets.size(); i++)
				{
					Vector2 currentPosition = GetPosition();
					Vector2 colisionPoint = currentPosition + offsets[i];
					Tile* currentTile = m_Game->GetRegion(colisionPoint)->GetTile(colisionPoint);

					//is link on a different tile?
					if (currentTile != previousTile)
					{
						Region* region = currentTile->GetRegion();
						if (currentTile->GetTileType() == TileType_Sand && m_HasBraceletOfPower == false)
						{
							if (m_DehidrationTimer.IsRunning() == false)
							{
								ApplyDamage(1, false);
								m_DehidrationTimer.Reset();
								m_DehidrationTimer.Start();
							}
						}
						if (currentTile->IsWalkable() == false && IsKeyDown(Keyboard::LeftControl) == false)
						{
							//link moved to a unwalkable tile.
							SetPosition(previousPosition);
							Pause();
						}
						else
						{
							Region* region = currentTile->GetRegion();
							int temp = region->GetNumberOfEnemies();
							for (int i = 0; i < temp; i++)
							{
								if (region->GetEnemy(i) != nullptr)
								{
									Enemy* enemy = region->GetEnemy(i);
									float radii = enemy->GetCollisionRadius() + LINK_ATTACK_RADIUS;
									float distance = enemy->GetPosition().Distance(GetPosition());
									if (distance <= radii)
									{
										ApplyDamage(enemy->GetAttackDamage(), true);
									}
								}
							}
							if (currentTile->GetIndex() == 88 && (region->GetRow() == 2 && region->GetColumn() == 1) && region->IsTrapSprung() == false)
							{
								//region->SpawnEnemyAtIndex(83, Enemy_Fire);
								region->SpawnEnemyAtIndex(95, Enemy_Fire);
								region->SetTrapSprung(true);
							}
						}
					}
				}
			}

			for (int i = 0; i < NUMBER_OF_LINK_DIRECTIONS; i++)
			{
				m_Animations[i]->SetPosition(GetPosition());
				m_Attacks[i]->SetPosition(GetPosition());
			}
		}
		else
		{
			if (m_Game->GetSoundManager()->IsAudioPlaying(LowHealth_Sound))
			{
				m_Game->GetSoundManager()->PauseAudio(LowHealth_Sound);
			}
			int temp = m_Direction;
			temp++;//Funny as hell so i'll leave as is
			if (temp >= 4) 
			{
				temp = 0;
			}
			m_Direction = (LinkDirection)temp;
		}
    }

    void Link::Draw()
    {
        if (IsAttacking() == true)
        {
            m_Attacks[m_Direction]->Draw();
        }
        else
        {
            m_Animations[m_Direction]->Draw();
        }
    }

    float Link::GetWidth()
    {
        return m_Animations[m_Direction]->GetWidth();
    }

    float Link::GetHeight()
    {
        return m_Animations[m_Direction]->GetHeight();
    }

    void Link::Move(LinkDirection direction, double delta)
    {
        //Don't move if Link is attacking
        if (IsAttacking() == true)
        {
            return;
        }

        //Get the position
        Vector2 position = GetPosition();

        //Resume the animation
        Resume();

        //If link facing the desired direction? If not turn link 
        if (m_Direction != direction)
        {
            m_Direction = direction;
        }

        //Increment the position
        Vector2 velocity = LINK_DIRECTIONS[direction] * LINK_SPEED;
        position += velocity * delta;

        //Set the position
        SetPosition(position);

		//Get the region link is on
		Region* region = m_Game->GetRegion(position);

		//Then get the tile link is on
		Tile* tile = region->GetTile(position);

		//Does that tile have a pickup on it?
		if (tile->HasPickup() == true)
		{
			if (tile->GetPickup()->GetPickupType() == PickupType_WoodSword)
			{
				SetHasSword(true);
				tile->RemovePickup();
			}
			else if (tile->GetPickup()->GetPickupType() == PickupType_OldLetter)
			{
				SetHasOldLetter(true);
				tile->RemovePickup();
			}
			else if (tile->GetPickup()->GetPickupType() == PickupType_Candle)
			{
				SetHasCandle(true);
				tile->RemovePickup();
			}
			else if (tile->GetPickup()->GetPickupType() == PickupType_Triforce)
			{
				m_Game->SetIsWon(true);
				tile->RemovePickup();
			}
			else if (tile->GetPickup()->GetPickupType() == PickupType_Bracelet)
			{
				SetHasBracelet(true);
				tile->RemovePickup();

				std::string animationKeys[] = { "LinkLeft-Red-", "LinkRight-Red-", "LinkUp-Red-", "LinkDown-Red-" };
				std::string frameKeys[] = { "LinkAttack-Red-Left", "LinkAttack-Red-Right", "LinkAttack-Red-Up", "LinkAttack-Red-Down" };
				Vector2 anchorPoints[] = { Vector2(0.7f, 0.5f), Vector2(0.3f, 0.5f), Vector2(0.5f, 0.3f), Vector2(0.5f, 0.675f) };

				for (int i = 0; i < NUMBER_OF_LINK_DIRECTIONS; i++)
				{
					m_Animations[i]->RemoveAllFrames();
					m_Animations[i]->AddFrame(std::string(animationKeys[i] + "1"));
					m_Animations[i]->AddFrame(std::string(animationKeys[i] + "2"));

					m_Attacks[i]->UseFrame(frameKeys[i]);
				}
			}
			else if (tile->GetPickup()->GetPickupType() == PickupType_Bombs)
			{
				if (((BombsPickup*)(tile->GetPickup()))->IsArmed() == true)
				{
					AddBombs(1);
					tile->RemovePickup();
				}
				else
				{
					AddBombs(3);
					tile->RemovePickup();
				}
			}
		}
    }

    void Link::Pause()
    {
        for (int i = 0; i < NUMBER_OF_LINK_DIRECTIONS; i++)
        {
            m_Animations[i]->Pause();
        }
    }

    void Link::Resume()
    {
        for (int i = 0; i < NUMBER_OF_LINK_DIRECTIONS; i++)
        {
            m_Animations[i]->Resume();
        }
    }

    bool Link::IsAttacking()
    {
        return m_AttackTimer.IsRunning();
    }

	bool Link::HasSword()
	{
		return m_HasSword;
	}

	void Link::SetHasSword(bool hasSword)
	{
		m_Game->GetSoundManager()->PlayAudio(Item_Sound);
		m_HasSword = hasSword;
	}

	bool Link::HasOldLetter()
	{
		return m_HasOldLetter;
	}

	void Link::SetHasOldLetter(bool hasOldLetter)
	{
		m_Game->GetSoundManager()->PlayAudio(Item_Sound);
		m_HasOldLetter = hasOldLetter;
	}

	bool Link::HasCandle()
	{
		return m_HasCandle;
	}

	void Link::SetHasCandle(bool hasCandle)
	{
		m_Game->GetSoundManager()->PlayAudio(Item_Sound);
		m_HasCandle = hasCandle;
	}

	bool Link::HasBracelet()
	{
		return m_HasBraceletOfPower;
	}

	void Link::SetHasBracelet(bool hasBracelet)
	{
		m_Game->GetSoundManager()->PlayAudio(Item_Sound);
		m_HasBraceletOfPower = hasBracelet;
	}

	bool Link::IsDead()
	{
		return m_IsDead;
	}

	void Link::SetIsDead(bool isDead)
	{
		m_IsDead = isDead;
	}

	bool Link::IsVilain()
	{
		return m_IsVilain;
	}

	void Link::SetIsVilain(bool isVilain)
	{
		m_IsVilain = isVilain;
	}

	unsigned int Link::GetBombCount()
	{
		return m_NumBombs;
	}

	void Link::AddBombs(unsigned int numBombs)
	{
		m_Game->GetSoundManager()->PlayAudio(Item_Sound);
		m_NumBombs += numBombs;
	}

	void Link::ApplyDamage(int damage, bool pushBack)
	{
		if (!m_HasBraceletOfPower)
		{
			m_Health -= damage;
			if (m_Health <= 0)
			{
				SetIsDead(true);
				m_Game->GetSoundManager()->PlayAudio(LinkDeath_Sound);
				m_Health = 0;
			}

			if (pushBack == true)
			{
				//Push back;
				Vector2 direction = LINK_DIRECTIONS[m_Direction] * -1.0f;
				Vector2 size = Vector2(TILE_SIZE, TILE_SIZE);
				Vector2 position = GetPosition();
				position += direction*size;
				SetPosition(position);
				//Hurt Sound
				m_Game->GetSoundManager()->PlayAudio(Hurt_Sound);
			}
		}
	}

	int Link::GetCurentHealth()
	{
		return m_Health;
	}

    void Link::Save()
    {
        //Save Link's position and direction on shutdown
        std::string path = Services::GetApplication()->GetPathForResourceInDirectory("SaveData", "bin", "Data");
        std::ofstream output;
        output.open(path, std::ofstream::out | std::ofstream::trunc | std::ofstream::binary);
        if (output.is_open() == true)
        {
            int buffer[3] = { (int)GetPosition().x, (int)GetPosition().y, m_Direction };
            output.write((char*)buffer, 12);
            output.close();
        }
    }

    void Link::Load()
    {
        //Load Link's position and direction on shutdown
        std::string path = Services::GetApplication()->GetPathForResourceInDirectory("SaveData", "bin", "Data");
        std::ifstream input;
        input.open(path, std::ifstream::in | std::ifstream::binary);
        if (input.is_open() == true)
        {
            input.seekg(0, std::ifstream::end);
            int bytes = input.tellg();

            //Are there any bytes to read?
            if (bytes > 0)
            {
                //Seek back to the start of the stream
                int elements = bytes / sizeof(int);
                input.seekg(0, std::ifstream::beg);
                int* buffer = new int[elements];

                //Read in the buffer
                input.read((char*)buffer, bytes);

                //Set the position and direction
                float x = (float)buffer[0];
                float y = (float)buffer[1];
                SetPosition(Vector2(x, y));
                m_Direction = (LinkDirection)buffer[2];

                //Delete the buffer array
                SafeDeleteArray(buffer);
            }

            //Close the input stream
            input.close();
        }
    }
}