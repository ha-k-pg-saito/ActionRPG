#ifndef EffectBoll_h_
#define EffectBoll_h_
#include"../h/Particle.h"
#include"DxLib.h"

class EffBoll :public Particle
{
public:
	EffBoll() :
		//�|�W�V�����E�p�x�E���a�E�X�s�[�h
		Particle{ {500,500,0},0.f,10.f,1.5f },
		m_Gravity{ -9.8f },
		m_Timer{ 0.f }
	{}
	~EffBoll() {}

	void Init();
	void Update();
	void Draw();

private:
	 float m_Gravity;			//�d�͂�9.8�Œ�
	 float m_Timer;
};
#endif