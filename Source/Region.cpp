#include "Region.h"
#include "GroundTile.h"
#include "WaterTile.h"
#include "RockTile.h"
#include "BoulderTile.h"
#include "TreeTile.h"
#include "SandTile.h"
#include "CaveTile.h"
#include "BridgeTile.h"
#include "EvilTreeTile.h"
#include "WaterfallTile.h"
#include "LadderTile.h"
#include "Fire.h"
#include "Game.h"


namespace GameDev2D
{
	Region::Region(const unsigned short aLevel[NUM_TILES], int row, int column, Game* game)
	{
		m_Game = game;
		m_TrapIsSprung = false;
		//Reverse the ROWS of the LEVEL
		unsigned short level[NUM_TILES] = {};
		for (int i = 0; i < NUM_TILES; i++)
		{
			level[i] = aLevel[i];
		}

		for (int row = 0; row < NUM_ROWS / 2; row++)
		{
			int offset = NUM_ROWS - 1 - row;
			for (int column = 0; column < NUM_COLUMNS; column++)
			{
				unsigned short* a = &level[column + (row * NUM_COLUMNS)];
				unsigned short* b = &level[column + (offset * NUM_COLUMNS)];
				unsigned short temp = *a;
				*a = *b;
				*b = temp;
			}
		}

		//Tile variants MUST be in reverse order
		TileVariant variants[] = { TileVariant_12, TileVariant_11, TileVariant_10, TileVariant_9, TileVariant_8,
			TileVariant_7, TileVariant_6, TileVariant_5, TileVariant_4, TileVariant_3,
			TileVariant_2, TileVariant_1, TileVariant_0 };

		unsigned short tileMask = 15;     //(0000 0000 0000 1111)
		unsigned short variantMask = 240; //(0000 0000 1111 0000)
		unsigned short colorMask = 768;   //(0000 0011 0000 0000)

		for (int i = 0; i < NUM_TILES; i++)
		{
			//initialyze to null first
			m_Tiles[i] = nullptr;

			//Load the Tiles
			unsigned short tileData = level[i] & tileMask;
			unsigned short variantData = level[i] & variantMask;
			unsigned short colorData = level[i] & colorMask;

			//Make the tile
			SetTileAtIndex(i, (TileType)tileData, (TileVariant)variantData, (TileColor)colorData,false);
		}


		//Create the Texture
		PixelFormat pixelFormat = PixelFormat(PixelFormat::RGBA, PixelFormat::UnsignedByte);
		ImageData imageData = ImageData(pixelFormat, GetWidth(), GetHeight());
		m_TilesCanvas = new Texture(imageData);

		//Render Tiles
		RenderTiles();

		//Initialize the row and column
		m_Row = row;
		m_Column = column;

		//Using the row and column set the position
		SetPosition(Vector2(GetColumn() * GetWidth(), GetRow() * GetHeight()));

		if (row==1 && (column==4|| column == 5))
		{
			for (int i =0; i<NUM_TILES;i++)
			{
				if (level[i]== 261)
				{
					SpawnEnemyAtIndex(i, Enemy_Fire);
				}
			}
		}
	}

	Region::~Region()
	{
		for (int i = 0; i < NUM_TILES; i++)
		{
			SafeDelete(m_Tiles[i]);
		}

		SafeDelete(m_TilesCanvas);

		for (int i =0; i<m_Enemies.size();i++)
		{
			SafeDelete(m_Enemies.at(i));
		}
		m_Enemies.clear();
	}

	void Region::Update(double delta)
	{
		for (int i = 0; i < NUM_TILES; i++)
		{
			m_Tiles[i]->Update(delta);
		}
		for (int i = 0; i < m_Enemies.size(); i++)
		{
			if (m_Enemies.at(i)!=nullptr)
			{
				m_Enemies.at(i)->Update(delta);
				if (m_Enemies.at(i)->DeleteMe())
				{
					SafeDelete(m_Enemies.at(i));
					m_Enemies.at(i) = nullptr;
					m_Game->CheckRegionTrees();
				}
			}
		}
	}

	void Region::Draw()
	{
		Services::GetGraphics()->DrawTexture(m_TilesCanvas, GetPosition(), Rotation::Degrees(0.0f));
	
		for (int i = 0; i < NUM_TILES; i++)
		{
			if (m_Tiles[i]->HasPickup() == true)
			{
				m_Tiles[i]->GetPickup()->Draw();
			}
			if (m_Tiles[i]->GetTileType()== TileType_Waterfall)
			{
				m_Tiles[i]->Draw();
			}
		}

		//Draw all enemies
		for (int i=0; i<m_Enemies.size();i++)
		{
			if (m_Enemies.at(i)!=nullptr)
			{
				m_Enemies.at(i)->Draw();
			}
		}
	}

	float Region::GetWidth()
	{
		return NUM_COLUMNS * TILE_SIZE;
	}

	float Region::GetHeight()
	{
		return NUM_ROWS * TILE_SIZE;
	}
	int Region::GetRow()
	{
		return m_Row;
	}
	int Region::GetColumn()
	{
		return m_Column;
	}
	bool Region::CheckTrees()
	{
		bool allTreesBurned = true;
		for (int i = 0; i < NUM_TILES; i++)
		{
			if (m_Tiles[i]->GetTileType()==TileType_Tree)
			{
				if (m_Tiles[i]->GetColor() == TileColor_Primary)
				{
					allTreesBurned = false;
				}
			}
		}
		return allTreesBurned;
	}
	void Region::ChangeToDesert()
	{
		for (int i = 0; i < NUM_TILES; i++)
		{
			if (m_Tiles[i]->GetTileType()==TileType_Ground)
			{
				SetTileAtIndex(i, TileType_Sand,TileVariant_0,TileColor_Primary,false);
			}
		}
		RenderTiles();
	}
	Game * Region::GetGame()
	{
		return m_Game;
	}
	Tile * Region::GetTile(const Vector2 & position)
	{
		int row = (position.y - GetPosition().y) / TILE_SIZE;
		int column = (position.x - GetPosition().x) / TILE_SIZE;
		return GetTile(row, column);
	}
	Tile * Region::GetTile(int row, int column)
	{
		int index = column + (row * NUM_COLUMNS);
		return GetTile(index);
	}
	Tile * Region::GetTile(int index)
	{
		if (index >= 0 && index < NUM_TILES)
		{
			return m_Tiles[index];
		}
		return nullptr;
	}
	void Region::SetTileAtIndex(int index, TileType type, TileVariant variant, TileColor color, bool render)
	{
		//Delete existing tile at the index
		SafeDelete(m_Tiles[index]);

		if (type == TileType_Ground)
		{
			m_Tiles[index] = new GroundTile(index);
		}
		else if (type == TileType_Water)
		{
			m_Tiles[index] = new WaterTile(index);
		}
		else if (type == TileType_Sand)
		{
			m_Tiles[index] = new SandTile(index);
		}
		else if (type == TileType_Rock)
		{
			m_Tiles[index] = new RockTile(index);
		}
		else if (type == TileType_Tree)
		{
			m_Tiles[index] = new TreeTile(index);
		}
		else if (type == TileType_Boulder)
		{
			m_Tiles[index] = new BoulderTile(index);
		}
		else if (type == TileType_Cave)
		{
			m_Tiles[index] = new CaveTile(index);
		}
		else if (type == TileType_Bridge)
		{
			m_Tiles[index] = new BridgeTile(index);
		}
		else if (type == TileType_Ladder)
		{
			m_Tiles[index] = new LadderTile(index);
		}
		else if (type == TileType_EvilTree)
		{
			m_Tiles[index] = new EvilTreeTile(index);
		}
		else if (type == TileType_Waterfall)
		{
			m_Tiles[index] = new WaterfallTile(index);
		}

		//Set variant and color
		m_Tiles[index]->SetVariant(variant);
		m_Tiles[index]->SetColor(color);
		m_Tiles[index]->SetRegion(this);

		//Should the canvas be rerendered?
		if (render == true)
		{
			RenderTiles();
		}
	}
	void Region::SpawnEnemyAtIndex(int index, EnemyType enemyType)
	{
		if (index >= 0 && index < NUM_TILES)
		{
			Tile* tile = GetTile(index);

			if (enemyType == Enemy_Fire)
			{
				Fire* fire = new Fire(this);
				fire->SetPosition(tile->GetCenter());
				m_Enemies.push_back(fire);
			}
		}
	}
	Enemy * Region::GetEnemy(int index)
	{
		for (int i = 0; i<m_Enemies.size(); i++)
		{
			if (i == index)
			{
				return m_Enemies.at(i);
			}
		}
		return nullptr;
	}
	unsigned int Region::GetNumberOfEnemies()
	{
		return m_Enemies.size();
	}
	bool Region::IsTrapSprung()
	{
		return m_TrapIsSprung;
	}
	void Region::SetTrapSprung(bool state)
	{
		m_TrapIsSprung = state;
	}
	void Region::RenderTiles()
	{
		//First make sure the tiles are not a child of the region when rendering to the canvas
		for (int i = 0; i < NUM_TILES; i++)
		{
			m_Tiles[i]->AttachTo(nullptr);
		}
		RenderTarget* renderTarget = new RenderTarget(m_TilesCanvas);
		renderTarget->Begin();

		for (int i = 0; i < NUM_TILES; i++)
		{
			m_Tiles[i]->Draw();
		}

		renderTarget->End();
		SafeDelete(renderTarget);

		//Lastly attach the tiles to the region, this must be done AFTER they are 
		//rendered to a texture
		for (int i = 0; i < NUM_TILES; i++)
		{
			m_Tiles[i]->AttachTo(this);
		}
	}
}