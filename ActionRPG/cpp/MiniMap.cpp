#include "..\h\MiniMap.h"

void MiniMap::Init()
{
	m_MiniHandle = LoadGraph("Tex/MiniMap.png");
//�e�N�X�`���̏c�E��/�}�b�v�̏c�E��
	m_Wide = TEX_WIDE / MAP_WIDE;
	m_Height = TEX_HEIGHT / MAP_HEIGHT;
}

void MiniMap::Update(Player* player)
{
	
	m_PlayerPos = player->GetAfterPos();
}

void MiniMap::Draw()
{
//�e�N�X�`����؂蔲���ĕ`��
	DrawRectGraph(INIT_TEX_POS, INIT_TEX_POS, m_PlayerPos.x, m_PlayerPos.z, TEXUV_SIZE, TEXUV_SIZE, m_MiniHandle, TRUE, FALSE);
//�v���C���̃|�W�V������\��
	DrawCircle(m_PlayerPos.x / m_Wide ,m_PlayerPos.z / m_Height, CIRCLE_RAD, GetColor(0, 0, 255), TRUE);
}