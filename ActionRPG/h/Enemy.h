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
		Base(0.f, 0.9f, 10.f)
	{
		m_Speed = (10.f);
		m_Hp = (3.f);
	}

	Enemy(VECTOR pos) :
		Base(pos)
	{}

	~Enemy() {}

public:
	void Init(VECTOR value);
	void Update(VECTOR player_pos);
	void Draw();
	void DrawHp();

	bool IsActive;

private:
	//モデル情報保存する変数
	int    Enemy_ModelHandle;

	//計算で使う変数
	float  Enemy_Angle;
	float  Initial_EnemyAngle;
	float  Enemy_AnimTotalTime;
	float  Enemy_AnimNowTime;
	int    Enemy_AnimAttachIndex;
	int    Enemy_RunFlag;
	int    Enemy_MoveFlag;
	int    Enemy_MoveAnimFrameIndex;
	VECTOR Enemy_Position;
	VECTOR Enemy_InitialPosition;
	VECTOR SubVector;
	VECTOR Initial_EnemyVector;

	VECTOR Distance_Pos;
	VECTOR SetEnemy_Pos;
	// 座標の+-の修正
	int Enemy_direction_x, Enemy_direction_z;
	int Setenemy_direction_x, Setenemy_direction_z;

};

#endif