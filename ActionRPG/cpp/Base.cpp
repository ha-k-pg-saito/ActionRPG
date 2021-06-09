#include"../h/Base.h"

//メンバイニシャライザにてメンバ変数初期化
CharBase::CharBase() :
	m_Pos{ 0.f },
	m_Hp{ 0 },
	m_Speed{ 0.f }
{}

CharBase::CharBase(float x, float y, float z,int hp,float speed) :
	m_Pos(VGet(x, y, z)),
	m_Hp{ hp },
	m_Speed{ speed }
{}

CharBase::CharBase(VECTOR pos, int hp, float speed) :
	m_Pos(pos),
	m_Hp{ hp },
	m_Speed{ speed }
{}

