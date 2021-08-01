#ifndef Enemy_h_
#define Enemy_h_
#include"DxLib.h"
#include"Base.h"
#include"../h/Map.h"
#include"../h/Animation.h"
#include"../h/Shape.h"

class Enemy :public CharBase
{
public:
	Enemy() :
		CharBase({ 0.f, 0.9f, 0.f }, 3, 35.f),
		m_ModelHandle{ 0 },
		m_GrHandle{ 0 },
		m_EnemyHeight{ 0.f,4.f,0 },
		m_Angle{ 0.f },
		m_InitAngle{ 0.f },
		IsMoveFlag{ true },
		m_MoveAnimFrameIndex{ 0 },
		m_Rand_Pos{ 0.f },
		m_InitPos{ 0.f },
		m_Vector{ 0.f },
		m_InitVec{ 0.f },
		m_Distance_Pos{ 0.f },
		m_SetEnemy_Pos{ 0.f },
		m_Direction_x{ 0 },
		m_Direction_z{ 0 },
		m_SetenemyDirection_x{ 0 },
		m_SetenemyDirection_z{ 0 },
		m_StartLine{ 0.f },
		m_EndLine{ 0.f },
		m_RadSize{ 2.8f },
		m_EnemyNum{ 10 }
	{
	}

	~Enemy() {}

public:
	void Init();
	void Update(VECTOR player_pos);
	void Draw();
	void DrawHp();
	void Damage();
	void Release();

	bool IsActive;

	int GetHp() { return m_Hp; }
	int GetModel() { return m_ModelHandle; }
	VECTOR GetPos() { return m_Pos; }
	VECTOR GetHeight() { return m_EnemyHeight; }

private:
	int    m_ModelHandle;		//���f������ۑ�����ϐ�
	int m_GrHandle;
	float m_PlayTime;				//�A�j���[�V��������

	//�v�Z�Ŏg���ϐ�
	float  m_Angle;
	float  m_InitAngle;
	float  m_RadSize;
	int    IsMoveFlag;
	int    m_MoveAnimFrameIndex;
	int m_EnemyNum;
	VECTOR m_Rand_Pos;	// �����ۑ��p
	VECTOR m_InitPos;
	VECTOR m_Vector;
	VECTOR m_InitVec;

	VECTOR m_Distance_Pos;
	VECTOR m_SetEnemy_Pos;
	// ���W��+-�̏C���p�ϐ�
	int m_Direction_x, m_Direction_z;
	int m_SetenemyDirection_x, m_SetenemyDirection_z;

	//���C�̎n�_�Ɏg���ϐ�
	VECTOR m_StartLine;
	VECTOR m_EndLine;

	//�����蔻��̃J�v�Z���̍���
	VECTOR m_EnemyHeight;

	Map m_MapRef;
	Animation Anim;
	AABB m_AABB;
};
#endif