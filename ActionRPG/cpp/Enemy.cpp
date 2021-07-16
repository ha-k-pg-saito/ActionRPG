#include<Math.h>
#include"../h/Enemy.h"
#include"../h/OnCollision.h"

void Enemy::Init()
{

	m_ModelHandle = MV1LoadModel("Tex/Enemy/goblin-sapper.mv1");
	m_GrHandle = LoadGraph("Tex/Enemy/goblin.jpg");
	if (m_GrHandle != -1)
	{
		int texindex = MV1GetMaterialDifMapTexture(m_ModelHandle, 0);
		int hand = MV1SetTextureGraphHandle(m_ModelHandle, texindex, m_GrHandle, FALSE);
	}
	VECTOR Scale = { 3.f,3.f,3.f };
	MV1SetScale(m_ModelHandle, Scale);
	Anim.InitAnimation(m_ModelHandle, "idle_1");
	m_Enemy_MoveFlag = FALSE;

	// �R�c���f���̍��W��������
	m_Rand_Pos.x = rand() % 1000 - 100;
	m_Rand_Pos.z = rand() % 1000 - 100;
	m_Rand_Pos.y = 0.0f;
	m_Enemy_Position = VGet(m_Rand_Pos.x, m_Rand_Pos.y, m_Rand_Pos.z);
	m_Enemy_InitialPosition = VGet(m_Rand_Pos.x, m_Rand_Pos.y, m_Rand_Pos.z);

	//�J�v�Z���̏�����
	m_Capsule.OldPos = m_Enemy_Position;
	m_Capsule.Bottom = m_Enemy_Position;
	m_Capsule.Top = VAdd(m_Enemy_Position, m_EnemyHeight);
	m_Capsule.Radius = ENEMY_HIT_SIZE_R;
	m_Hp = 3;
	IsActive = true;
	MV1SetupCollInfo(m_ModelHandle, -1, 1, 1, 1);
}

void Enemy::Update(VECTOR player_pos)
{
	m_AABB.Update(m_Enemy_Position);
	m_Capsule.Update(m_Enemy_Position);
	// �R�c���f��Enemy����R�c���f��Player�Ɍ������x�N�g�����Z�o
	m_Vector = VSub(player_pos, m_Enemy_Position);
	// �R�c���f��Enemy���珉���n�_�ւ̃x�N�g�����Z�o
	m_Initial_EnemyVector = VSub(m_Enemy_InitialPosition, m_Enemy_Position);

	// atan2 ���g�p���Ċp�x���擾
	m_Enemy_Angle = atan2f(m_Vector.x, m_Vector.z);
	m_Initial_EnemyAngle = atan2f(m_Initial_EnemyVector.x, m_Initial_EnemyVector.z);

	// Player��Enemy�̋���
	m_Distance_Pos.x = player_pos.x - m_Enemy_Position.x;
	m_Distance_Pos.z = player_pos.z - m_Enemy_Position.z;
	// Enemy�̏����ʒu��Enemy�̋���
	m_SetEnemy_Pos.x = m_Enemy_InitialPosition.x - m_Enemy_Position.x;
	m_SetEnemy_Pos.z = m_Enemy_InitialPosition.z - m_Enemy_Position.z;

	if (m_Distance_Pos.x < 0)
	{
		// Player�Ƃ̕�����+-���C��
		m_Enemy_direction_x = -1;
		// Player�Ƃ̋�����-��+�ɕύX
		m_Distance_Pos.x *= -1;
	}
	else
	{
		m_Enemy_direction_x = 1;
	}
	if (m_Distance_Pos.z < 0)
	{
		m_Enemy_direction_z = -1;
		m_Distance_Pos.z *= -1;
	}
	else
	{
		m_Enemy_direction_z = 1;
	}

	if (m_SetEnemy_Pos.x < 0)
	{
		// �����ʒu�Ƃ̕�����+-���C��
		m_Setenemy_direction_x = -1;
		// �����ʒu�Ƃ̋����A-��+�ɕύX
		m_SetEnemy_Pos.x *= -1;
	}
	else
	{
		m_Setenemy_direction_x = 1;
	}
	if (m_SetEnemy_Pos.z < 0)
	{
		m_Setenemy_direction_z = -1;
		m_SetEnemy_Pos.z *= -1;
	}
	else
	{
		m_Setenemy_direction_z = 1;
	}

	m_Enemy_MoveFlag = FALSE;

	// ��苗���ɂȂ��Player�̕��Ɍ���
	if (m_Distance_Pos.x <= 50.0f && m_Distance_Pos.z <= 50.0f)
	{
		// atan2 �Ŏ擾�����p�x�ɂR�c���f���𐳖ʂɌ������邽�߂̕␳�l( DX_PI_F )��
		// �������l���R�c���f���� Y����]�l�Ƃ��Đݒ�
		MV1SetRotationXYZ(m_ModelHandle, VGet(0.0f, m_Enemy_Angle + DX_PI_F, 0.0f));

		// ��苗���ɂȂ��Player�̕��Ɉړ�
		if (m_Distance_Pos.x <= 50.0f && m_Distance_Pos.z <= 50.0f)
		{
			if (m_Distance_Pos.x >= 4.2f) {
				m_Enemy_Position.x += m_Enemy_direction_x * (m_Speed * 1.f / 60.f);
				m_Enemy_MoveFlag = TRUE;
			}
			if (m_Distance_Pos.z >= 4.2f) {
				m_Enemy_Position.z += m_Enemy_direction_z * (m_Speed * 1.f / 60.f);
				m_Enemy_MoveFlag = TRUE;
			}
		}
	}
	else // �T�m�͈͊O�ɂȂ�Ə����ʒu�ɖ߂�
	{
		MV1SetRotationXYZ(m_ModelHandle, VGet(0.0f, m_Initial_EnemyAngle + DX_PI_F, 0.0f));

		if (m_SetEnemy_Pos.x >= 0.1f) {
			m_Enemy_Position.x += m_Setenemy_direction_x * (m_Speed * 1.f / 60.f);
			m_Enemy_MoveFlag = TRUE;
		}
		if (m_SetEnemy_Pos.z >= 0.1f) {
			m_Enemy_Position.z += m_Setenemy_direction_z * (m_Speed * 1.f / 60.f);
			m_Enemy_MoveFlag = TRUE;
		}
	}

	if (m_Enemy_MoveFlag)
	{
		VECTOR CenterPos = m_Enemy_Position;
		CenterPos.y += 6;
		//���������Ƃ�����I�_�ɂ���
		VECTOR HitPos = { 0 };
		if (m_MapRef.CollisionToModel(CenterPos, VAdd(CenterPos, m_Enemy_Position), &HitPos))
		{
			return;
		}

		//�����n�_�l����ǂꂭ�炢���炷�̂�
		VECTOR vertical{ 0,6,0 };
		//�n�_�͌��݂̃|�W�V�����ƈړ��ʂ�ۑ����Ă���ϐ��𑫂��Ă���
		m_StartLine = VAdd(m_Pos, m_Enemy_Position);
		m_StartLine.y += vertical.y;
		//�����n�_�l����ǂꂭ�炢���Ƀ��C���o���̂�
		VECTOR DownLine{ 0,-20,0 };
		m_EndLine = VAdd(m_StartLine, DownLine);
		//�o�������C�̃}�b�v�Ƃ̂����蔻��
		if (m_MapRef.CollisionToModel(m_StartLine, m_EndLine, &HitPos))
		{
			m_Pos = HitPos;
		}
		DrawLine3D(m_Pos, m_StartLine, GetColor(0, 0, 255));
		DrawLine3D(m_StartLine, m_EndLine, GetColor(0, 0, 255));
	}


	MV1SetPosition(m_ModelHandle, m_Enemy_Position);
	MV1RefreshCollInfo(m_ModelHandle, -1);
}

void Enemy::Draw()
{
	//��ʓ��ɍ��W�������Ă��邩�ǂ���
	//�����Ă���[���`��@�����Ă��Ȃ��[���`�悵�Ȃ�
	if (CheckCameraViewClip(m_Enemy_Position) == FALSE)
	{
		// �V�����A�j���[�V�������A�^�b�`
		if (m_Enemy_MoveFlag)
		{
			// �ړ�
			//Anim.SetAnimation(m_ModelHandle, ANIM_LIST::ANIM_RUN);
		}
		else
		{
			//Anim.SetAnimation(m_ModelHandle, ANIM_LIST::ANIM_IDLE);
		}

		MV1DrawModel(m_ModelHandle);
	}
}


void Enemy::DrawHp()
{
}

void Enemy::Damage()
{
	m_Hp--;
	//Anim.SetAnimation(m_ModelHandle, ANIM_LIST::ANIM_DAMAGE);
}
