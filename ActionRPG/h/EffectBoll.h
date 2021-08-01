#ifndef EffectBoll_h_
#define EffectBoll_h_
#include"../h/Particle.h"
#include"DxLib.h"

class EffBoll :public Particle
{
public:
	EffBoll() :
		//ポジション・角度・半径・スピード
		Particle{ {500,500,0},0.f,10.f,1.5f,0.f,0 },
		m_Gravity{ 9.8f },
		IsActive{ false },
		m_GrHandle{ 0 },
		m_Color{ 0 },
		m_Red{ 0 },
		m_Green{ 0 },
		m_Blue{ 255 }
	{}
	~EffBoll() {}

	void Init();
	void Update();
	void Draw();
	void Delete();

public:
	bool IsActive;

private:
	 float m_Gravity;			//重力は9.8固定
	 int   m_GrHandle;
	 int   m_Color;
	 int   m_Red, m_Green, m_Blue;
};
#endif