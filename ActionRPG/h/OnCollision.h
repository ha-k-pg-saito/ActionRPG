#ifndef OnCollision_h_
#define OnCollision_h_
#include"../h/Player.h"
#include"../h/Enemy.h"

class OnColl
{
public:
	OnColl() :
		m_OldPlayerPos{ 0.f },
		m_OldEnemyPos{ 0.f },
		m_PlayerPos{ 0.f },
		m_EnemyPos{ 0.f }
	{}
	~OnColl() {}

	void Update(Player* player, Enemy* enemy);
	void Draw(Player* player,Enemy* enemy);

	VECTOR m_OldPlayerPos;
	VECTOR m_OldEnemyPos;
	VECTOR m_PlayerPos;
	VECTOR m_EnemyPos;

//Žg‚¤ƒ‚ƒfƒ‹‚Ì”¼Œa
#define PLATER_HIT_SIZE_R 2.f
#define ENEMY_HIT_SIZE_R  4.3f
};
#endif