#ifndef Enemy_Manager_h_
#define Enemy_Manaager_h_

#include "h/Enemy.h"

class EnemyManager
{
public:
	void Init(VECTOR pos);
	void Update(VECTOR player_pos);
	void Draw();
	Enemy* CreateEnemy(VECTOR init_pos);

	Enemy Enemies[10];
};

#endif // !Enemy_Manager_h_
