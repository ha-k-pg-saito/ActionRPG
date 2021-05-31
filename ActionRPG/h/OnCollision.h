#ifndef OnCollision_h_
#define OnCollision_h_

#include"../h/Enemy.h"

class Player;

class OnColl
{
public:
	OnColl() :
		SpherePos{0}
	{}
	~OnColl() {}
	void Init(Player* player);
	void Update(Player* player);

	MV1_COLL_RESULT_POLY_DIM HitPolyDim;
	VECTOR SpherePos;
};

#endif