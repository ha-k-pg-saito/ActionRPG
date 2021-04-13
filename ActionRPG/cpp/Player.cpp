#include "../h/Player.h"
#include"DxLib.h"
#include<Math.h>

Player::Player():
	Base(0.f, 0.9f,0.f),
	m_Angle{90.f},
	m_PlayTime{0}
{
	m_Speed = (0.3f);	
}

void Player::Init()
{
	// モデルの読み込み
	m_ModelHandle = MV1LoadModel("Tex/sister.mv1");

	//アニメーション
	m_AnimHandle[ANIM_LIST::ANIM_RUN]= MV1LoadModel("Tex/unitychan_RUN00_F.mv1");
	m_AnimAttachIndex[ANIM_LIST::ANIM_RUN] = MV1AttachAnim(m_ModelHandle, 0, m_AnimHandle[ANIM_LIST::ANIM_RUN], TRUE);
	m_AnimTotalTime[ANIM_LIST::ANIM_RUN] = MV1GetAttachAnimTotalTime(m_ModelHandle, m_AnimAttachIndex[ANIM_LIST::ANIM_RUN]);
}

void Player::Update()
{
	Move();
	m_PlayTime++;
	if (m_PlayTime>=m_AnimTotalTime[ANIM_LIST::ANIM_RUN])
	{
		m_PlayTime = 0;
	}
	MV1SetAttachAnimTime(m_ModelHandle, m_AnimAttachIndex[ANIM_LIST::ANIM_RUN], m_PlayTime);
}

void Player::Draw()
{
	// 3Dモデルの描画
	MV1DrawModel(m_ModelHandle);
}

void Player::Move()
{
	// 画面に移るモデルの移動
	MV1SetPosition(m_ModelHandle, m_Pos);

	//X軸の向きベクトル算出
	m_Digree_X = cosf(m_Radian);

	//特定のキーを押したときにプレイヤーを移動させる
	if (CheckHitKey(KEY_INPUT_W)) { m_Pos.z -= m_Speed; }
	if (CheckHitKey(KEY_INPUT_S)) { m_Pos.z += m_Speed; }
	if (CheckHitKey(KEY_INPUT_A)) { m_Pos.x += m_Digree_X; }
	if (CheckHitKey(KEY_INPUT_D)) { m_Pos.x -= m_Digree_X; }
}

