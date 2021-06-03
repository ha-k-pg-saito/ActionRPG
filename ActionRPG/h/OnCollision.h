#ifndef OnCollision_h_
#define OnCollision_h_
#include"../h/Player.h"
#include"../h/Enemy.h"

class OnColl
{
public:
	OnColl() {}
	~OnColl() {}

	void Update(Player* player, Enemy* enemy);
	void Draw(Player* player,Enemy* enemy);

	VECTOR m_CharVec;
	VECTOR m_PushVec;
	VECTOR m_CharPos;
	float  m_Length;
	VECTOR m_MoveVec;
};

#endif