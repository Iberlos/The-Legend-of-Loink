#pragma once

#include <GameDev2D.h>

namespace GameDev2D
{
	class Link;

	class HeadsUpDisplay
	{
	public:
		HeadsUpDisplay(Link* link);
		~HeadsUpDisplay();

		void Draw();

	private:
		Polygon * m_Background;
		SpriteAtlas* m_WoodSword;
		SpriteAtlas* m_Shield;
		SpriteAtlas* m_Bombs;
		SpriteAtlas* m_OldLetter;
		SpriteAtlas* m_Bracelet;
		SpriteAtlas* m_Candle;
		SpriteAtlas* m_EmptyHeart;
		SpriteAtlas* m_FullHeart;
		SpriteAtlas* m_HalfHeart;
		SpriteFont* m_BombsLabel;
		Vector2 m_StartPosheart;
		Link* m_Link;
	};
}