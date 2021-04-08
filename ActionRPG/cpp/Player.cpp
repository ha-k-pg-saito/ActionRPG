#include "../h/Player.h"
#include"DxLib.h"
#include<Math.h>

Player::Player()
{
	m_Pos = VGet(0.f, 0.9f, 0.f);
	m_Angle = (0.f);
}

void Player::Update()
{
	// ƒ‚ƒfƒ‹‚Ì“Ç‚İ‚İ
	m_Player = MV1LoadModel("Tex/sister.mv1");
	
}

void Player::Draw()
{
	// 3Dƒ‚ƒfƒ‹‚Ì•`‰æ
	MV1DrawModel(m_Player);
}

void Player::Move()
{

	// ‰æ–Ê‚ÉˆÚ‚éƒ‚ƒfƒ‹‚ÌˆÚ“®
	MV1SetPosition(m_Player, m_Pos);

	if (CheckHitKey(KEY_INPUT_W)) { m_Pos.z -= 0.5f; }
	if (CheckHitKey(KEY_INPUT_S)) { m_Pos.z += 0.5f; }
	if (CheckHitKey(KEY_INPUT_A)) { m_Pos.x -= 0.5f; }
	if (CheckHitKey(KEY_INPUT_D)) { m_Pos.x += 0.5f; }

}
