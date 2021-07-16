#ifndef EffectBoll_h_
#define EffectBoll_h_
#include"../h/Particle.h"
#include"DxLib.h"

class EffBoll :public Particle
{
public:
	EffBoll() :
		//ポジション・角度・半径・スピード
		Particle{ {500,500,0},0.f,10.f,1.5f },
		m_Gravity{ -9.8f },
		m_Timer{ 0.f }
	{}
	~EffBoll() {}

	void Init();
	void Update();
	void Draw();

private:
	 float m_Gravity;			//重力は9.8固定
	 float m_Timer;
};
#endif