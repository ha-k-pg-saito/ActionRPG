#include"../h/Base.h"

//メンバイニシャライザにてメンバ変数初期化
CharBase::CharBase() :
	m_Pos{0.f},
	m_Hp{0.f},
	m_Speed{0.f}
{
}

CharBase::CharBase(float x, float y, float z) :
	m_Pos(VGet(x, y, z)),
	m_Hp{ 0.f },
	m_Speed{ 0.f }
{
}

CharBase::CharBase(VECTOR pos) :
	m_Pos(pos),
	m_Hp{ 0 },
	m_Speed{ 0 }
{
}

