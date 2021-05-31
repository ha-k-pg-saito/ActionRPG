#ifndef OnCollision_h_
#define OnCollision_h_
#include"../h/Player.h"
#include"../h/Enemy.h"

class OnColl
{
public:
	OnColl() :
		m_SpherePos{0}
	{}
	~OnColl() {}

	void Update(Player* player, Enemy* enemy);
	void Draw(Player* player);

	MV1_COLL_RESULT_POLY_DIM HitPolyDim;
	VECTOR m_SpherePos;
};

#endif