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
	// ƒ‚ƒfƒ‹‚ğ•Û‘¶‚·‚é•Ï”
	int   m_ModelHandle;
	float m_Angle;
	float m_Radian;
	float m_Digree_X, m_Digree_Y;

};


#endif // !Player_h_



