#include "..\h\MiniMap.h"

void MiniMap::Init()
{
	//CreateMaskScreen();
	m_MiniHandle = LoadGraph("Tex/MiniMap.png");
	m_CircleHandle = LoadMask("Tex/Circle.png");
}

void MiniMap::Update(Player* player)
{
	m_PlayerPos = player->GetPos();
}

void MiniMap::Draw()
{
	DrawExtendGraph(m_MapPos.x, m_MapPos.z, 300, 300, m_MiniHandle, FALSE);
	//DrawGraph(m_MapPos.x, m_MapPos.z, m_MiniHandle,TRUE);
	//DrawMask(m_CirPos.x, m_CirPos.z, m_CircleHandle, DX_MASKTRANS_BLACK);
	//プレイヤのポジションを表示
	DrawCircle(m_PlayerPos.x, m_PlayerPos.z, CIRCLE_RAD, GetColor(255, 255, 255), TRUE);
}