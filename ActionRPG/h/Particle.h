#ifndef Particle_h_
#define Particle_h_
#include"DxLib.h"
#include<Math.h>

class Particle
{
public:
	Particle() :
		m_Pos{0.f},
		m_Angle{ 0.f },
		m_Rad{ 0.f },
		m_Speed{ 1.f }
	{}

	Particle(VECTOR pos,float angle, float rad, float speed) :
		m_Pos{pos},
		m_Angle{ angle },
		m_Rad{ rad },
		m_Speed{ speed }
	{}
	virtual ~Particle() {}

protected:
	VECTOR m_Pos;
	float m_Angle;
	float m_Rad;
	float m_Speed;
};
#endif