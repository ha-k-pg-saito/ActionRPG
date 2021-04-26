#ifndef Enemy_h_
#define Enemy_h_
#include"DxLib.h"
#include"Base.h"

class Enemy :public Base
{
public:
	//アニメーションリスト
	enum ANIM_LIST
	{

		ANIM_RUN,

		ANIM_NUM
	};

public:
	Enemy() :
		Base(0.f, 0.9f, 10.f),
		m_Radian(0.f),
		m_Digree_Y(0.f),
		m_Direction{0}
	{
		m_Speed = (10.f);
		m_Hp = (3.f);
	}

	Enemy(VECTOR pos) :
		Base(pos)
	{}

		~Enemy() {}

public:
	void Init();
	void Update();
	void Draw();
	void DrawHp();

private:
	//モデル情報保存する変数
	int m_MHandle;

	//計算で使う変数
	float  m_Radian;
	float  m_Digree_Y;
	VECTOR m_Direction;

};

#endif