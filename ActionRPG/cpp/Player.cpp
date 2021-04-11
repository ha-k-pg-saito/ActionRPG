#include "../h/Player.h"
#include"DxLib.h"
#include<Math.h>

Player::Player()
{
	m_Pos = VGet(0.f, 0.9f, 0.f );
	m_Angle = (90.f);
	m_Speed = (0.3f);
}

Player::~Player()
{
}

void Player::Update()
{
	// モデルの読み込み
	m_ModelHandle = MV1LoadModel("Tex/sister.mv1");
	
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

	//モデルの回転
	//MV1SetRotationXYZ(m_ModelHandle, VGet(0.f,m_Angle * DX_PI_F / 180.f, 0.f));

	m_Digree_X = cosf(m_Radian);
	m_Digree_Y = sinf(m_Radian);

	//特定のキーを押したときにプレイヤーを移動させる
	if (CheckHitKey(KEY_INPUT_W)) { m_Pos.z -= m_Speed; }
	if (CheckHitKey(KEY_INPUT_S)) { m_Pos.z += m_Speed; }
	if (CheckHitKey(KEY_INPUT_A)) { m_Pos.x += m_Digree_X; }
	if (CheckHitKey(KEY_INPUT_D)) { m_Pos.x -= m_Digree_X; }

}
