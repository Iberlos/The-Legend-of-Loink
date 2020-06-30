#pragma once

#include "Region.h"
#include "Constants.h"


namespace GameDev2D
{
	class Game;
	class Link;
	class Cave : public Region
	{
	public:
		Cave(Link* link, Game* game);
		~Cave();

		void SetCaveType(CaveType caveType);
		void SetCaveCleared();

		void Draw() override;

	private:
		CaveType m_CaveType;
		bool m_IsCaveCleared[CaveType_Count];
		bool m_HasRequiredItem;

		SpriteAtlas* m_OldMan;
		SpriteFont* m_Text;
		Link* m_Link;
	};
}