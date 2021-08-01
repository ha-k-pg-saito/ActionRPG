#include<Math.h>
#include "../h/Player.h"
#include"../h/Calculation.h"
#include"../h/OnCollision.h"
#include"../h/Enemy.h"

void Player::Init()
{
	m_Pos={ 0.f,-3.f,0.f };
	m_HitCounter = 0;
	IsAlive = true;
	//�J�v�Z���̏�����
	m_Capsule.OldPos = m_Pos;
	m_Capsule.Bottom = m_Pos;
	m_Capsule.Top = VAdd(m_Pos,m_HeightCapsule);
	m_Capsule.Radius = m_RadSize;
	//AABB�̏�����
	m_AABB.OldPos = m_Pos;
	m_AABB.Max = m_Capsule.Top;
	m_AABB.Min = m_Pos;
	m_AnimKind = ANIM_LIST::ANIM_IDLE;		//������ԁi�ҋ@�j

#pragma region ���f���E�e�N�X�`���ǂݍ���

//�v���C���E�����f���̃e�N�X�`���ǂݍ���
	m_GrHandle = LoadGraph("Tex/Player/knight_01.jpg");
	m_SwordGrHandle = LoadGraph("Tex/Player/sword_01.jpg");
//�v���C���ǂݍ���
	m_ModelHandle = MV1LoadModel("Tex/Player/knight_low.mv1");
	//���f���̃X�P�[���ύX
	VECTOR Scale = { 3.f,3.f,3.f };
	MV1SetScale(m_ModelHandle, Scale);
	
	if (m_GrHandle <= -1)
	{
		//�w��}�e���A���̃e�N�X�`���ԍ����擾
		int TexIndex = MV1GetMaterialDifMapTexture(m_ModelHandle, 0);
		int SworIindex = MV1GetMaterialDifMapTexture(m_ModelHandle, 1);
		//���f���Ƀe�N�X�`����\��
		MV1SetTextureGraphHandle(m_ModelHandle, TexIndex, m_GrHandle, FALSE);
		MV1SetTextureGraphHandle(m_ModelHandle, SworIindex, m_SwordGrHandle, FALSE);
	}
//�v���C���̃}�e���A���̃A���r�G���g�J���[�ύX
	MV1SetMaterialAmbColor(m_ModelHandle, 0, GetColorF(1.f, 1.f, 1.f, 0.f));

#pragma endregion 

	m_Anim.InitAnimation(m_ModelHandle, "idle_1");
	
//player�̃��f���n���h��,�t���[���ԍ�,XYZ�̋�ԕ���
	MV1SetupCollInfo(m_ModelHandle, -1, 1, 1, 1);
}

void Player::Update()
{
	if (m_AnimKind != ANIM_ATTACK)
	{
		Move();
		Rotate();
	}
	Attack();
	UpdateAnimation();
	m_AABB.Update(m_Pos);
	m_Capsule.Update(m_Pos);

	//�����蔻����X�V
	MV1RefreshCollInfo(m_ModelHandle, -1);
}

//�A�j���[�V�����̐؂�ւ��𐧌䂷��֐�
void Player::UpdateAnimation()
{
	InitAnim();
	m_PlayTime++;
//���݂̏�Ԃ����ăA�j���[�V������؂�ւ���
	float CurrentFrame = m_MotionList[m_AnimKind].StartFrame;
		switch (m_AnimKind)
		{
		case ANIM_IDLE:						//�ҋ@���[�V����->���胂�[�V���� or�U�����[�V����
			//�ړ��ʂ�0�ł͖����Ƃ�
			if (m_OldMoveVec.x != PlayerState::None && m_OldMoveVec.z != PlayerState::None)
			{
				ChangeAnim(ANIM_RUN);
			}
			//���N���b�N���ꂽ�Ƃ�
			else if ((GetMouseInput() & MOUSE_INPUT_LEFT) != PlayerState::None)
			{
				ChangeAnim(ANIM_ATTACK);
				IsPushed = true;
			}
			if (m_PlayTime >= m_MotionList[m_AnimKind].FinishFrame)
			{
				CurrentFrame = m_MotionList[m_AnimKind].StartFrame;
				m_PlayTime = CurrentFrame;
			}
			break;
		case ANIM_RUN:						//���胂�[�V����->�ҋ@���[�V���� or �U�����[�V����
			//�ړ��ʂ�0�̎�
			if (VSize(m_OldMoveVec) <= 0.1f)
			{
				//�ҋ@���[�V������
				ChangeAnim(ANIM_IDLE);
			}
			//���N���b�N���ꂽ�Ƃ�
			else if ((GetMouseInput() & MOUSE_INPUT_LEFT) != PlayerState::None)
			{
				//�U�����[�V������
				ChangeAnim(ANIM_ATTACK);
				IsPushed = true;
			}
			if (m_PlayTime >= m_MotionList[m_AnimKind].FinishFrame)
			{
				CurrentFrame = m_MotionList[m_AnimKind].StartFrame;
				m_PlayTime = CurrentFrame;
			}
			break;
		case ANIM_ATTACK:					
			if (VSize(m_OldMoveVec) >= 0.1f && IsPushed == false)
			{
				ChangeAnim(ANIM_IDLE);
			}
			else if (VSize(m_OldMoveVec) <= 0.1f && IsPushed == false)
			{
				ChangeAnim(ANIM_RUN);
			}
			if (m_PlayTime >= m_MotionList[m_AnimKind].FinishFrame)
			{
				CurrentFrame = m_MotionList[m_AnimKind].StartFrame;
				m_PlayTime = CurrentFrame;
				IsPushed = false;
			}
			break;
		default:
			break;
		}

		//��Ԃɍ��킹���A�j���[�V������������
		MV1SetAttachAnimTime(m_ModelHandle, m_AnimKind, m_PlayTime);
}

//�v���C���[�`��
void Player::Draw()
{	
	if (IsAlive)
	{
#ifdef _DEBUG
		DrawLine3D(m_Pos, m_StartLine, GetColor(0, 0, 255));
		DrawLine3D(m_StartLine, m_EndLine, GetColor(0, 0, 255));
#endif

		DrawFormatString(200, 200, GetColor(255, 255, 255), "�ړ���X��: %d", m_OldMoveVec.x);
		DrawFormatString(200, 250, GetColor(255, 255, 255), "�ړ���Z��: %d", m_OldMoveVec.z);
		MV1DrawModel(m_ModelHandle);
		MV1DrawModel(m_SwordHandle);
		DrawHP();
	}
}

//�v���C���[�̉�]
void Player::Rotate()
{
	float Angle{ 0.f };

	//����̃L�[���������Ƃ��Ƀv���C���[����]������
	if      (CheckHitKey(KEY_INPUT_D))  Angle += m_RotateSpeed;
	else if (CheckHitKey(KEY_INPUT_A))  Angle -= m_RotateSpeed;

	//�p�x���O�ł͂Ȃ��ꍇ
	if (Angle != PlayerState::None)
	{
		m_Digree_Y += Angle;
		//�x���@���烉�W�A���ɕϊ�
		float Rad = m_Digree_Y * DX_PI_F / 180.f;

		//�RD�̌����x�N�g���Z�o(�P�ʃx�N�g�����P)
		m_Direction.x = sinf(Rad);
		m_Direction.z = cosf(Rad);
		m_OldMoveVec.x = m_Direction.x * (m_RotateSpeed * 1.f / FPS);
		m_OldMoveVec.z = m_Direction.z * (m_RotateSpeed * 1.f / FPS);

		//���f���̉�]
		MV1SetRotationXYZ(m_ModelHandle, VGet(0.f, Rad, 0.f));
	}
}

void Player::Move()
{
	//���t���[��0�ŏ���������
	VECTOR MoveVec{ 0.f };

#pragma region �ړ����� 
	//����̃L�[���������Ƃ��Ɉړ�
	if (CheckHitKey(KEY_INPUT_W))
	{
		//�P�t���[���œ�������������o���Ă���
		MoveVec.x += m_Direction.x * (m_Speed * 1.f / FPS);
		MoveVec.z += m_Direction.z * (m_Speed * 1.f / FPS);
	}
	else if (CheckHitKey(KEY_INPUT_S))
	{
		MoveVec.x -= m_Direction.x * (m_Speed * 1.f / FPS);
		MoveVec.z -= m_Direction.z * (m_Speed * 1.f / FPS);
	}

#pragma endregion
	if (MoveVec.x !=0.f || MoveVec.z != 0.f)
	{
		MoveVec = Slerp(m_OldMoveVec, MoveVec, 0.2f);
	}

	//�ߋ��̈ړ��x�N�g���ۑ�
	m_OldMoveVec = MoveVec;

	//�ړ��x�N�g����0.1�ȏ�
	if (VSize(MoveVec) >= 0.1f)
	{
		m_OldPos = m_Pos;
		//atan2���g�����ƂŌ��݂̌����Ă����������180�U�����
		float Rad = (float)atan2f(MoveVec.x, MoveVec.z);

		MV1SetRotationXYZ(m_ModelHandle, VGet(0.f, Rad, 0.f));
		m_Digree_Y = Rad * 180.f / DX_PI_F;

		VECTOR CenterPos = m_Pos;
		CenterPos.y += 6.f;
		//���������Ƃ�����I�_�ɂ���
		VECTOR HitPos{ 0.f };
		if (MapRef->CollisionToModel(CenterPos, VAdd(CenterPos, MoveVec), &HitPos))	return;

		// �ړ���̍��W��ۑ�
		m_StartLine = VAdd(m_Pos, MoveVec);

		// ���C�̌��_�����Ƃ߂� (�ړ���̍��W+����)
		VECTOR Vertical{ 0.f,RAY_ORIGIN,0.f };
		m_StartLine.y += Vertical.y;

		// ���C�̏I�_�����Ƃ߂� (���C�̌��_ + �������x�N�g��)
		VECTOR DownLine{ 0.f,RAY_DOWN,0.f };
		m_EndLine = VAdd(m_StartLine, DownLine);

		// �}�b�v�Ƃ̌�������
		if (MapRef->CollisionToModel(m_StartLine, m_EndLine, &HitPos))
		{
			//�������Ă���Ƃ�����v���C���̃|�W�V�����ɂ���
			m_Pos = HitPos;
		}
		//�v���C���̍��W����I�t�Z�b�g�l���������炷����
		m_AfterPos = VAdd(m_Pos, m_OffSet);
	}
	else
	{
		m_OldMoveVec.x = 0.f;
		m_OldMoveVec.y = 0.f;
		m_OldMoveVec.z = 0.f;
	}
	// ��ʂɈڂ郂�f���̈ړ�
	MV1SetPosition(m_ModelHandle, m_Pos);
}

void Player::DrawHP()
{
	const int HPX = 75;
	const int HPY = 960;
	int color = GetColor(0, 255, 0);
	DrawBox(HPX, HPY, 920, 1040, GetColor(255,0,0), TRUE);
	//HP�Q�[�W�`��
	if      (m_HitCounter == 0)  m_Hp = DrawBox(HPX, HPY, 920, 1040, color, TRUE);
	else if (m_HitCounter == 1)  m_Hp = DrawBox(HPX, HPY, 690, 1040,color, TRUE); 
	else if (m_HitCounter == 2)  m_Hp = DrawBox(HPX, HPY, 460, 1040,color, TRUE); 
	else if (m_HitCounter == 3)  m_Hp = DrawBox(HPX, HPY, 230, 1040,color, TRUE);
	else
	{
		m_Hp = DrawBox(HPX, HPY, 75, 1040, color, TRUE);
		Release();
		IsAlive = false;
	}
	//HP�Q�[�W�ǂݍ��ݕ`��
	LoadGraphScreen(0, 900, "Tex/HPGauge.png", TRUE);
}

void Player::Release()
{
	//3D���f���̍폜
	MV1DeleteModel(m_ModelHandle);
	//�e�N�X�`���̍폜
	DeleteGraph(m_GrHandle);
}

void Player::Attack()
{
	if ((GetMouseInput() & MOUSE_INPUT_LEFT) != PlayerState::None)
	{
		if (OnColl::Inatance()->OnCollisionAABB(this->GetAABB(),m_Enemy->GetAABB()));
		{
			DrawString(1700, 200, "Hit", GetColor(255, 255, 255));

			m_Enemy->Release();
		}
	}
}

//���̊֐��̓_���[�W��^���Ă����G�ɂ��̊֐����Ăяo��
void Player::Damage()
{
	m_HitCounter ++;
}

void Player::NoticeHit()
{
	m_Pos = m_OldPos;
}

//�A�j���[�V����������fbx�Ɋ܂܂�Ă��邩��t���[���w�肵�Đ؂���
void Player::InitAnim()
{
	//�ҋ@���[�V����
	m_MotionList[ANIM_LIST::ANIM_IDLE].StartFrame = 1380;
	m_MotionList[ANIM_LIST::ANIM_IDLE].FinishFrame = 1830;
	//���胂�[�V����
	m_MotionList[ANIM_LIST::ANIM_RUN].StartFrame = 170;
	m_MotionList[ANIM_LIST::ANIM_RUN].FinishFrame = 220;
	//�U�����[�V����
	m_MotionList[ANIM_LIST::ANIM_ATTACK].StartFrame = 440;
	m_MotionList[ANIM_LIST::ANIM_ATTACK].FinishFrame = 520;
	//�_���[�W���[�V����
	m_MotionList[ANIM_LIST::ANIM_DAMAGE].StartFrame = 1040;
	m_MotionList[ANIM_LIST::ANIM_DAMAGE].FinishFrame = 1080;
}

void Player::ChangeAnim(ANIM_LIST type)
{
	m_AnimKind = type;
	m_PlayTime = m_MotionList[m_AnimKind].StartFrame;
}
