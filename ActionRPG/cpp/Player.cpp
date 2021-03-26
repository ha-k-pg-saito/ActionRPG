#include "../h/Player.h"
#include"DxLib.h"

//Player::Player()
//{
//	
//}
//
//Player::~Player()
//{
//	// モデルハンドルの削除
//	MV1DeleteModel(m_Player);
//}

void Player::Update()
{
	// モデルの読み込み
	m_Player = MV1LoadModel("Tex/sister.mv1");

	// 画面に移るモデルの移動
	MV1SetPosition(m_Player, VGet(0.f, 0.f, 0.f));
	
}

void Player::Draw()
{
	// 3Dモデルの描画
	MV1DrawModel(m_Player);
}
