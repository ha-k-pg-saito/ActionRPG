#ifndef Collison_h_
#define Collison_h_

#include "DxLib.h"
#include "../h/Player.h"
#include "../h/Map.h"

class Collision
{
public:
	Collision();
	~Collision();

	void Update(Player *player, Map *map);
	void Draw();

private:
	MV1_COLL_RESULT_POLY_DIM HitPolyDim;
	int Add, y, i;
	VECTOR SpherePos;

};

#endif // !1



