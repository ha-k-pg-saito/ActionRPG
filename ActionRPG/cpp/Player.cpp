#include<Math.h>
#include "../h/Player.h"
#include"DxLib.h"

void Player::Init()
{
	// モデルの読み込み
	m_ModelHandle = MV1LoadModel("Tex/sister.mv1");
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

//プレイヤー描画
void Player::Draw()
{
	// 3Dモデルの描画
	MV1DrawModel(m_ModelHandle);
	DrawHP();
}

//プレイヤーの回転
void Player::Rotate()
{
	float Digree = 0.f;

	//特定のキーを押したときにプレイヤー向いている方向にを移動させる
	if (CheckHitKey(KEY_INPUT_LEFT)) { Digree -= 10; }
	if (CheckHitKey(KEY_INPUT_RIGHT)) { Digree += 10; }

	if (Digree != 0.f)
	{
		m_Digree_Y += Digree;

		float Rad = m_Digree_Y * DX_PI_F / 180.0f;

		//３Dの向きベクトル算出(単位ベクトル＝１)
		m_Direction.x = sinf(Rad);
		m_Direction.z = cosf(Rad);
		//モデルの回転
		MV1SetRotationXYZ(m_ModelHandle, VGet(0.0f, Rad, 0.0f));
	}
}

void Player::Move()
{
	Rotate();
	// 画面に移るモデルの移動
	MV1SetPosition(m_ModelHandle, m_Pos);

	//一時的に移動量を保存する
	VECTOR Move_Vec{ 0.f,0.f,0.f };

	if (CheckHitKey(KEY_INPUT_W))
	{ 
		Move_Vec.x -= m_Direction.x * (m_Speed * 1 / 60);
		Move_Vec.z -= m_Direction.z * (m_Speed * 1 / 60);
	}
	if (CheckHitKey(KEY_INPUT_S)) 
	{
		Move_Vec.x += m_Direction.x * (m_Speed * 1 / 60);
		Move_Vec.z += m_Direction.z * (m_Speed * 1 / 60);
	}
	if (CheckHitKey(KEY_INPUT_A)) 
	{	
		Move_Vec.x += m_Direction.x * (m_Speed * 1 / 60);
		Move_Vec.z -= m_Direction.z * (m_Speed * 1 / 60);
	}
	if (CheckHitKey(KEY_INPUT_D))
	{
		Move_Vec.x -= m_Direction.x * (m_Speed * 1 / 60); 
		Move_Vec.z += m_Direction.z * (m_Speed * 1 / 60); 
	}
	
	//移動したのかを調べて移動していたならアニメーションする
	if (Move_Vec.x != 0.f || Move_Vec.z != 0.f)
	{
		//アニメーション
		m_AnimHandle[ANIM_LIST::ANIM_RUN] = MV1LoadModel("Tex/unitychan_RUN00_F.mv1");
		m_AnimAttachIndex[ANIM_LIST::ANIM_RUN] = MV1AttachAnim(m_ModelHandle, 0, m_AnimHandle[ANIM_LIST::ANIM_RUN], TRUE);
		m_AnimTotalTime[ANIM_LIST::ANIM_RUN] = MV1GetAttachAnimTotalTime(m_ModelHandle, m_AnimAttachIndex[ANIM_LIST::ANIM_RUN]);
		m_Pos.x += Move_Vec.x;
		m_Pos.z += Move_Vec.z;
	}
}

void Player::DrawHP()
{
	//HPバー描画（四角形）
	DrawBox(100, 65, 900, 140, GetColor(0,255,0), TRUE);
	//HPゲージ読み込み描画
	LoadGraphScreen(0, 0, "Tex/HPGauge.png", TRUE);
}

