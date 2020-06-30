#pragma once
#include <GameDev2D.h>
#include "Constants.h"

namespace GameDev2D
{
	class Enemy : public Drawable
	{
	public:
		Enemy();
		virtual ~Enemy();

		virtual void Draw() = 0;
		virtual float GetWidth() = 0;
		virtual float GetHeight() = 0;

		virtual EnemyType GetEnemyType() = 0;

		virtual float GetCollisionRadius() = 0;
		virtual int GetAttackDamage() = 0;
		virtual void Update(double delta) = 0;
		virtual bool DeleteMe() = 0;
	};
}