#ifndef EnemyManager_h_
#define EnemyManager_h_

#include "../h/Enemy.h"

class EnemyManager
{
public:
	void Init();
	void Update(VECTOR player_pos);
	void Draw();
	Enemy* CreateEnemy();
	Enemy* GetEnemy(int index) { return &Enemies[index]; }
	int  GetEnemyNum() { return Enemy_Num; }

private:
	int Enemy_Num = 10;
	Enemy Enemies[10];	// []の中とEnemy_Numを同じにする
};
#endif // !Enemy_Manager_h_
