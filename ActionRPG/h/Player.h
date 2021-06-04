#ifndef Player_h_
#define Player_h_
#include"Base.h"
#include"DxLib.h"
#include"../h/Map.h"
#include"../h/Enemy.h"

class Player :public CharBase
{
	//アニメーションを管理するenum
	enum ANIM_LIST
	{
		ANIM_WAIT,
		ANIM_RUN,
		ANIM_ATTACK,
		ANIM_DAMAGE,
		ANIM_DIED,
		ANIM_NUM,
	};

public:
	Player(Map* map) :
		//CharBase({pos},hp,speed)を初期化している
		CharBase({ 0.f, 0.f, 0.f }, 0, 40.f), 
		m_Radian{ 0.f },
		m_PlayTime{ 0.f },
		m_AnimHandle{ 0 },
		m_Direction{ 0 },
		m_HitCounter{0},
		m_HeightCapsule { 0.f,6.f,0 }
	{
		m_MapRef = map;
	}
	Player(VECTOR pos, float hp, float speed) :
		CharBase(pos, hp, speed)
	{}

	~Player() { Release(); }

public:
// プレイヤーのモデル取得
	int    GetModel() { return m_ModelHandle; }
	VECTOR SetPos(VECTOR movevec) { return m_MoveVec; }
//プレイヤーの座標取取得
	VECTOR GetPos() { return m_Pos; }
// プレイヤーの移動ベクトル取得
	VECTOR GetMoveVec() { return m_MoveVec; }
//プレイヤの高さを取得
	VECTOR GetHeight() { return m_HeightCapsule; }

public:
	void Init();
	void Update();
	void Draw();
	void DrawHP(); 
	void Release();
	void Attack();

private:
//playerの関数内で呼び出す関数
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
	VECTOR m_Direction;	

//当たった回数を保存する変数
	int m_HitCounter;
//キャラの移動量保存変数
	VECTOR m_MoveVec;       
//レイの始点に使う変数
	VECTOR m_StartLine;
	VECTOR m_EndLine;
//カプセルの当たり判定で使用する変数
	VECTOR m_HeightCapsule;

	Map* m_MapRef;
	
//Playerのテクスチャ数
#define PLAYER_TEX_NUM  8
};
#endif // !Player_h_



