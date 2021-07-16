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
		m_EnemyHeight{ 0.f,2.f,0 },
		m_Enemy_Angle{ 0.f },
		m_Initial_EnemyAngle{ 0.f },
		m_Enemy_MoveFlag{ true },
		m_Enemy_MoveAnimFrameIndex{ 0 },
		m_Enemy_Position{ 0.f },
		m_Rand_Pos{ 0.f },
		m_Enemy_InitialPosition{ 0.f },
		m_Vector{ 0.f },
		m_Initial_EnemyVector{ 0.f },
		m_Distance_Pos{ 0.f },
		m_SetEnemy_Pos{ 0.f },
		m_Enemy_direction_x{ 0 },
		m_Enemy_direction_z{ 0 },
		m_Setenemy_direction_x{ 0 },
		m_Setenemy_direction_z{ 0 },
		m_StartLine{ 0.f },
		m_EndLine{ 0.f }
	{
	}

	~Enemy() {}

public:
	void Init();
	void Update(VECTOR player_pos);
	void Draw();
	void DrawHp();
	void Damage();

	bool IsActive;

	int GetHp() { return m_Hp; }
	int GetModel() { return m_ModelHandle; }
	VECTOR GetPos() { return m_Enemy_Position; }
	VECTOR GetHeight() { return m_EnemyHeight; }

private:
	int    m_ModelHandle;		//���f������ۑ�����ϐ�
	int m_GrHandle;
	float m_PlayTime;				//�A�j���[�V��������

	//�v�Z�Ŏg���ϐ�
	float  m_Enemy_Angle;
	float  m_Initial_EnemyAngle;
	int    m_Enemy_MoveFlag;
	int    m_Enemy_MoveAnimFrameIndex;
	VECTOR m_Enemy_Position;
	VECTOR m_Rand_Pos;	// �����ۑ��p
	VECTOR m_Enemy_InitialPosition;
	VECTOR m_Vector;
	VECTOR m_Initial_EnemyVector;

	VECTOR m_Distance_Pos;
	VECTOR m_SetEnemy_Pos;
	// ���W��+-�̏C���p�ϐ�
	int m_Enemy_direction_x, m_Enemy_direction_z;
	int m_Setenemy_direction_x, m_Setenemy_direction_z;

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