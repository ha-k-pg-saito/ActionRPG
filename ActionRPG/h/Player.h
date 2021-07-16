#ifndef Player_h_
#define Player_h_

#include<unordered_map>
#include"DxLib.h"
#include"../h/Base.h"
#include"../h/Map.h"
#include"../h/Animation.h"
#include"../h/Shape.h"

class Player :public CharBase
{
//���������ǂ����ŏ�Ԃ�ω�������
	enum PlayerState
	{
		None,
		OnMove
	};
public:
	//�v���C�����Ń}�b�v�����X�V���Ă���
	Player(Map* map) :
		//CharBase({pos},hp,speed)�����������Ă���
		CharBase({ 0.f, -3.f, 0.f }, 4, 40.f),
		m_ModelHandle{ 0 },
		m_Radian{ 0.f },
		m_PlayTime{ 1380.f },
		m_Direction{ 0.f,0.f,1.f },
		m_Digree_Y{ 0.f },
		m_HitCounter{ 0 },
		m_OldMoveVec{ 0.f },
		m_OldPos{ 0.f },
		m_HeightCapsule{ 0.f,9.f,0.f },
		m_RotateSpeed{ 5.f },
		m_InitRad{ 0.f },
		IsAlive{ true },
		m_AfterPos{ 0.f },
		m_OffSet{ 200.f,0.f,200.f }
	{
		MapRef = map;
	}

	~Player() { Release(); }

public:
// �v���C���[�̃��f���擾
	int    GetModel() { return m_ModelHandle; }
//�v���C����Hp�J�E���^�\�擾
	int GetAliveFlag() { return IsAlive; }
//pos�ϐ��ɔ��f������
	void SetPos(VECTOR setpos) { m_Pos = setpos; }
//�v���C���[�̍��W��擾
	VECTOR GetPos() { return m_Pos; }
	VECTOR GetAfterPos() { return m_AfterPos; }
public:
	void Init();			   //������
	void Update();			   //�X�V�i�����j
	void UpdateAnimation();	   //�A�j���[�V�����X�V
	void Draw();			   //�`��֐�
	void DrawHP(); 			   //HP�`��
	void Release();			   //�폜����
	void Attack();			   //�U������
	void Damage();			   //�_���[�W�J�E���^�\���₷->HP�ϓ�
	void NoticeHit();          //�����������Ƃ�ʒm����

private:
	void Rotate();			   //��]����
	void Move();			   //�s������
	void InitAnim();           //���Ԃɉ����Ăق����A�j���[�V������I������֐�
	void ChangeAnim(ANIM_LIST type);

//Player�̃A�j���[�V������
#define PLAYER_ANIM_NUM 6
//60�t���[���Ŋ���Ƃ��Ɏg��
#define FPS 60.f

#define RAY_ORIGIN 4.f
#define RAY_DOWN   -16.f
// 3D���f����ۑ�����ϐ�
	int m_ModelHandle;
//3D���f���ɓ\��e�N�X�`���ۑ��ϐ�
	int m_GrHandle;
	int m_SwordGrHandle;
//Ekard�ɂ��錕�̃��f���ۑ��ϐ�
	int m_SwordHandle;
//�A�j���[�V��������
	float m_PlayTime;						
//�v�Z�Ŏg���ϐ�(�����x�N�g���p)
	float  m_Radian;		
	float  m_Digree_Y;	
	VECTOR m_Direction;	
//���������񐔂�ۑ�����ϐ�
	int m_HitCounter;
//�����t���O
	bool IsAlive;
//�L�����̈ړ��ʕۑ��ϐ�
	VECTOR m_OldMoveVec;      

	VECTOR m_OldPos;
//���C�̎n�_�Ɏg���ϐ�
	VECTOR m_StartLine;
	VECTOR m_EndLine;
//�J�v�Z���̓����蔻��Ŏg�p����ϐ�
	VECTOR m_HeightCapsule;

	VECTOR m_InitRad;
//��]�X�s�[�h
	float m_RotateSpeed;
//�ړ���̍��W����I�t�Z�b�g�l�������l��ۑ�����ϐ�
	VECTOR m_AfterPos;
//�I�t�Z�b�g�l
	VECTOR m_OffSet;
//�}�b�v���f��������
	Map* MapRef;
	Animation m_Anim;
	AABB m_AABB;

	//enum��ANIM_LIST�ƍ\����MotionParam��R�Â��Ă���
	std::unordered_map<ANIM_LIST, MotionParam>m_MotionList;

	ANIM_LIST m_AnimKind;
};
#endif // !Player_h_