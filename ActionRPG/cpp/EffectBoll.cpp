#include"../h/EffectBoll.h"
#include<Math.h>

void EffBoll::Init()
{
}

void EffBoll::Update()
{
	m_Timer++;
	//���W�A���ϊ�
	m_Angle = 45.f * DX_PI_F / 180.f;
	m_Gravity = m_Gravity * m_Timer;
	m_Pos.x += m_Speed * cosf(m_Angle);
	m_Pos.y += m_Speed * sinf(m_Angle);
}

void EffBoll::Draw()
{
	for (int i = 0; i < 50; i++)
	{
			SetDrawBright(0, 0, 200);			//�`��P�x���Z�b�g
			DrawCircle(m_Pos.x, m_Pos.y, m_Rad, GetColor(0, 0, 255), TRUE);
	}
}