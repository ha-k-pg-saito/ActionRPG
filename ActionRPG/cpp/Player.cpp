#include "../h/Player.h"
#include"DxLib.h"
#include<Math.h>

Player::Player():
	Base(0.f, 0.9f,0.f),
	m_Radian{0.f},
	m_PlayTime{0}
{
	m_Speed = (20.f);	
}

void Player::Init()
{
	// モデルの読み込み
	m_ModelHandle = MV1LoadModel("Tex/sister.mv1");
}

void Player::Update()
{
	Move();
	m_PlayTime++;
	
	if (CheckHitKey(KEY_INPUT_A)|| CheckHitKey(KEY_INPUT_D))
	{
		if (CheckHitKey(KEY_INPUT_W)|| CheckHitKey(KEY_INPUT_S))
		{
			//アニメーション
			m_AnimHandle[ANIM_LIST::ANIM_RUN] = MV1LoadModel("Tex/unitychan_RUN00_F.mv1");
			m_AnimAttachIndex[ANIM_LIST::ANIM_RUN] = MV1AttachAnim(m_ModelHandle, 0, m_AnimHandle[ANIM_LIST::ANIM_RUN], TRUE);
			m_AnimTotalTime[ANIM_LIST::ANIM_RUN] = MV1GetAttachAnimTotalTime(m_ModelHandle, m_AnimAttachIndex[ANIM_LIST::ANIM_RUN]);
		}
	}
	
	if (m_PlayTime>=m_AnimTotalTime[ANIM_LIST::ANIM_RUN])
	{
		m_PlayTime = 0;
	}
	MV1SetAttachAnimTime(m_ModelHandle, m_AnimAttachIndex[ANIM_LIST::ANIM_RUN], m_PlayTime);//特定のキーを押したときにアニメーションさせる
	
	
}

void Player::Draw()
{
	// 3Dモデルの描画
	MV1DrawModel(m_ModelHandle);
	HP();
}

void Player::Move()
{
	// 画面に移るモデルの移動
	MV1SetPosition(m_ModelHandle, m_Pos);

	//モデルの回転
	MV1SetRotationXYZ(m_ModelHandle, VGet(0.0f,m_Radian * DX_PI_F / 180.0f, 0.0f));

	//３Dの向きベクトル算出(単位ベクトル＝１)
	m_Digree_X = cosf(m_Radian) + sinf(m_Radian);
	m_Digree_Z = -sinf(m_Radian) + cosf(m_Radian);

	//特定のキーを押したときにプレイヤー向いている方向にを移動させる
	if (CheckHitKey(KEY_INPUT_W)) { m_Pos.z -= m_Digree_Z * (m_Speed * 1 / 60); }
	if (CheckHitKey(KEY_INPUT_S)) { m_Pos.z += m_Digree_Z * (m_Speed * 1 / 60); }
	if (CheckHitKey(KEY_INPUT_A)) { m_Pos.x += m_Digree_X * (m_Speed * 1 / 60); }
	if (CheckHitKey(KEY_INPUT_D)) { m_Pos.x -= m_Digree_X * (m_Speed * 1 / 60); }
}

void Player::HP()
{
	//HPバー描画（四角形）
	DrawBox(100.f, 65.f, 900.f, 140.f, GetColor(0,255,0), TRUE);
	//HPゲージ読み込み描画
	LoadGraphScreen(0.f, 0.f, "Tex/HPGauge.png", TRUE);
}

