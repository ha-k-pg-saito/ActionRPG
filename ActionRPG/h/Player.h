#ifndef Player_h_
#define Player_h_
#include"Base.h"
#include"DxLib.h"

class Player :public Base
{
	//アニメーションリスト
	enum ANIM_LIST
	{
		//走るアニメーション
		ANIM_RUN,

		ANIM_NUM,
	};

public:
	Player():
		Base(0.f, 0.9f, 0.f),
		m_Radian{ 0.f },
		m_PlayTime{ 0 },
		m_AnimHandle{ 0 }
	{
		m_Speed = (20.f);
	}

	Player(VECTOR pos) :
		Base(pos)
	{}

	~Player() {}		

public:
	void Init();
	void Update();
	void Draw();
	void Move();
	void DrawHP(); 

public:
	VECTOR GetPos() { return m_Pos; }

private:
	// モデルを保存する変数
	int   m_ModelHandle;

	//アニメーションに使用する変数
	int   m_AnimHandle[ANIM_NUM];
	int   m_AnimAttachIndex[ANIM_NUM];
	int   m_AnimTotalTime[ANIM_NUM];
	int   m_PlayTime;						//アニメーション時間

	//計算で使う変数
	float m_Radian;						
	float m_Digree_X, m_Digree_Z;		//向きベクトルの保存

};


#endif // !Player_h_



