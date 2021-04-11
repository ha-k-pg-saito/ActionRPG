#ifndef Player_h_
#define Player_h_
#include"Base.h"

class Player :public Base
{
public:
	Player();
	~Player();

public:
	void Update();
	void Draw();
	void Move();

private:
	// モデルを保存する変数
	int   m_ModelHandle;
	float m_Angle;
	float m_Radian;
	float m_Digree_X, m_Digree_Y,m_Digree_Z;

};


#endif // !Player_h_



