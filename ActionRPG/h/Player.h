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
		//Base()内で初期化しているのはポジション変数
		Base(0.f, 0.9f, 0.f),
		m_Radian{ 0.f },
		m_PlayTime{ 0.f },
		m_AnimHandle{ 0 },
		m_Direction{0}
	{
		m_Speed = (20.f);
		m_Hp = (3.f);
	}
	Player(VECTOR pos) :
		Base(pos)
	{}

	~Player() { Release(); }

public:
	//Initの引数はモデル読み込む時に使う
	void Init(int modelhandle, int grhandle);
	void Update();
	void Draw();
	void DrawHP(); 
	void Release();
	

public:
	//プレイヤーの座標取取得
	VECTOR GetPos() { return m_Pos; }

	int GetModel() { return m_ModelHandle; }

private:
	void Rotate();
	void Move();
	void Collision();

private:
	// 3Dモデルを保存する変数
	int m_ModelHandle;
	//3Dモデルに貼るテクスチャ保存変数
	int m_GrHandle[8];

	//アニメーションに使用する変数
	int   m_AnimHandle[ANIM_NUM];
	int   m_AnimAttachIndex[ANIM_NUM];
	int   m_AnimTotalTime[ANIM_NUM];
	float m_PlayTime;						//アニメーション時間

	//計算で使う変数
	float  m_Radian;		
	float  m_Digree_Y;	
	VECTOR m_Direction;		

	//レイの描画に使う変数
	VECTOR m_Line;
	//DxLibにあるあたり判定用の戻り値+変数
	MV1_COLL_RESULT_POLY HitPoly;
};


#endif // !Player_h_



