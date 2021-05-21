#ifndef Player_h_
#define Player_h_
#include"Base.h"
#include"DxLib.h"
#include"../h/Map.h"

class Player :public Base
{
	//アニメーションリスト
	enum ANIM_LIST
	{
		//走るアニメーション
		ANIM_RUN,
		ANIM_ATTACK,
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
		m_Speed = (100.f);
		m_Hp = (0.f);
		m_HitCounter = (0);
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
	void Attack();


private:
	void Rotate();
	// 引数　移動処理をとる引数
	void Move();
	
public:
	//プレイヤーの座標取取得
	VECTOR GetPos() { return m_Pos; }
	// プレイヤーのモデル取得
	int GetModel() { return m_ModelHandle; }
	// プレイヤーの移動ベクトル取得
	VECTOR MoveVecter() { return Move_Vec; }

private:
	void Rotate();
	void Move();
	void Damage();

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
<<<<<<< HEAD
	VECTOR m_Direction;		

	//レイの描画に使う変数
	VECTOR m_Line;

	//当たった回数を保存する変数
	int m_HitCounter;

	//マップクラスのインスタンス化
	Map map;
=======
	VECTOR m_Direction;		//向いている方向
	VECTOR Move_Vec;        //キャラの移動ベクトル
>>>>>>> Collision
};


#endif // !Player_h_



