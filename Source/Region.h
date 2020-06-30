#pragma once

#include <GameDev2D.h>
#include "Tile.h"
#include "Constants.h"


namespace GameDev2D
{
	class Game;
	class Enemy;

	class Region : public Drawable
	{
	public:
		Region(const unsigned short level[NUM_TILES], int row, int column, Game* game);
		~Region();

		void Update(double delta);
		void Draw() override;

		float GetWidth() override;
		float GetHeight() override;

		int GetRow();
		int GetColumn();
		bool CheckTrees();
		void ChangeToDesert();

		Game* GetGame();

		Tile* GetTile(const Vector2& position);
		Tile* GetTile(int row, int column);
		Tile* GetTile(int index);

		void SetTileAtIndex(int index, TileType type, TileVariant variant, TileColor color, bool render = false);

		void SpawnEnemyAtIndex(int index, EnemyType enemyType);

		Enemy* GetEnemy(int index);
		unsigned int GetNumberOfEnemies();

		bool IsTrapSprung();
		void SetTrapSprung(bool state);

	private:
		void RenderTiles();

		//Member variables
		Game* m_Game;
		Tile * m_Tiles[NUM_TILES];
		Texture* m_TilesCanvas;
		int m_Row;
		int m_Column;
		bool m_TrapIsSprung;

		std::vector<Enemy*> m_Enemies;
	};
}