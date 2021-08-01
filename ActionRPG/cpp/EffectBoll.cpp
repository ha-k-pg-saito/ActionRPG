#include"../h/EffectBoll.h"
#include<Math.h>
#include"../h/Calculation.h"

void EffBoll::Init()
{
	int AliveTime = rand() % 181 + 120;
    //ランダムで放出角度算出
	m_Angle = rand() % 181 ;
	m_Pos.x = rand() % 960 + 500;
	m_Pos.y = rand() % 540 + 300;
	Particle::Init(m_Pos, m_Angle, m_Rad, m_Speed, AliveTime);
}

void EffBoll::Update()
{
	m_Timer++;
	if (m_Timer >= m_AliveTime)
	{
		m_IsAlive = false;
	}
	//ラジアン変換
	float Angle = m_Angle * DX_PI_F / 180.f;
	if (m_Timer <= m_Gravity)
	{
		m_Pos.x -= m_Gravity;
		m_Pos.y -= m_Gravity;
	}
	else 
	{
		m_Pos.x += m_Speed * cosf(Angle);
		m_Pos.y += m_Speed * sinf(Angle);
	}

	VECTOR Red = { 255.f,0.f,0.f }, Blue = { 0.f,0.f,255.f };
	float Time = m_Timer / m_AliveTime;
	VECTOR Color = Lerp(Blue, Red, Time);
	m_Color = GetColor(Color.x, Color.y, Color.z);
}

void EffBoll::Draw()
{
	SetDrawBright(255, 255, 255);		//描画輝度をセット
	
	m_GrHandle = DrawCircle(m_Pos.x, m_Pos.y, m_Rad, m_Color, TRUE);
}

void EffBoll::Delete()
{
}