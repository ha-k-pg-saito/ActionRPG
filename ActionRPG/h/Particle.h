#ifndef Particle_h_
#define Particle_h_
#include"DxLib.h"
#include<Math.h>

class Particle
{
public:
	Particle() :
		m_Pos{ 0.f },
		m_Angle{ 0.f },
		m_Rad{ 0.f },
		m_Speed{ 1.f },
		m_Timer{ 0.f },
		m_IsAlive{ false },
		m_AliveTime{ 0 }
	{}

	Particle(VECTOR pos, float angle, float rad, float speed, float time, int alivetime, bool alive = false) :
		m_Pos{ pos },
		m_Angle{ angle },
		m_Rad{ rad },
		m_Speed{ speed },
		m_Timer{ time },
		m_IsAlive{ alive },
		m_AliveTime{ alivetime }
	{}
	virtual ~Particle() {}
	bool IsAlive() { return m_IsAlive; }
	void Init(VECTOR pos, float angle, float rad, float speed, int alivetime)
	{
		m_Pos = pos;
		m_Angle = angle;
		m_Rad = rad;
		m_Speed = speed;
		m_Timer = 0.f;
		m_IsAlive = true;
		m_AliveTime = alivetime;
	}

protected:
	VECTOR m_Pos;
	float m_Angle;
	float m_Rad;
	float m_Speed;
	float m_Timer;
	bool  m_IsAlive;
	int   m_AliveTime;
};
#endif