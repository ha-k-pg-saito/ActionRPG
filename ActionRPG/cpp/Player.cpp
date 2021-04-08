#include "../h/Player.h"
#include"DxLib.h"

Player::Player()
{
	m_Pos = VGet(0.f, 0.9f, 0.f);
	m_Angle = (0.f);
}

void Player::Update()
{
	// モデルの読み込み
	m_Player = MV1LoadModel("Tex/sister.mv1");

	// 画面に移るモデルの移動
	MV1SetPosition(m_Player, m_Pos);

}

void Player::Draw()
{
	// 3Dモデルの描画
	MV1DrawModel(m_Player);
}
