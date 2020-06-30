#pragma once
#include "Enemy.h"
#include "Constants.h"
#include "Timer.h"

namespace GameDev2D
{
	class Region;
	class Fire : public Enemy
	{
	public:
		Fire(Region* region);
		~Fire();

		// Inherited via Enemy
		virtual void Draw() override;

		virtual float GetWidth() override;

		virtual float GetHeight() override;

		virtual EnemyType GetEnemyType() override;

		virtual float GetCollisionRadius() override;

		virtual int GetAttackDamage() override;

		virtual void Update(double delta) override;

		virtual bool DeleteMe() override;

	private:
		AnimatedSprite* m_Fire;
		Region* m_Region;
		Timer m_SpreadTimer;
		bool m_CanSpread;
		bool m_DeleteMe;
	};
}