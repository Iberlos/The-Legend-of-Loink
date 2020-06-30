#pragma once


#include <GameDev2D.h>
#include "Timer.h"
#include "Constants.h"

namespace GameDev2D
{
	//Forward declaration
	class Game;

    class Link : public Drawable
    {
    public:
        Link(Game* game);
        ~Link();

        void Update(double delta);
        void Draw();
        float GetWidth();
        float GetHeight();

        void Move(LinkDirection direction, double delta);

        void Pause();
        void Resume();

        bool IsAttacking();

		bool HasSword();
		void SetHasSword(bool hasSword);

		bool HasOldLetter();
		void SetHasOldLetter(bool hasOldLetter);

		bool HasCandle();
		void SetHasCandle(bool hasCandle);

		bool HasBracelet();
		void SetHasBracelet(bool hasBracelet);

		bool IsDead();
		void SetIsDead(bool isDead);

		bool IsVilain();
		void SetIsVilain(bool isVilain);

		unsigned int GetBombCount();
		void AddBombs(unsigned int numBombs);

		void ApplyDamage(int damage, bool pushBack);

		int GetCurentHealth();
    private:

        void Save();
        void Load();

        //Member variables
        AnimatedSprite* m_Animations[NUMBER_OF_LINK_DIRECTIONS];
        SpriteAtlas* m_Attacks[NUMBER_OF_LINK_DIRECTIONS];
        LinkDirection m_Direction;
        Timer m_AttackTimer;
		Timer m_BombDelay;
		Timer m_CandleDelay;
		Timer m_DehidrationTimer;

		bool m_HasSword;
		bool m_HasOldLetter;
		bool m_HasBraceletOfPower;
		bool m_HasCandle;
		bool m_IsDead;
		bool m_IsVilain;

		unsigned int m_NumBombs;
		Game* m_Game;

		int m_Health;
	};
}