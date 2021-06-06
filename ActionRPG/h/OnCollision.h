#ifndef OnCollision_h_
#define OnCollision_h_
#include"../h/Player.h"
#include"../h/Enemy.h"

class OnColl
{
public:
	OnColl() :
		m_OldCharPos{ 0.f }
	{}
	~OnColl() {}

	void Update(Player* player, Enemy* enemy);
	void Draw(Player* player,Enemy* enemy);

	VECTOR m_OldCharPos;
	VECTOR m_CharPos;
};
#endif