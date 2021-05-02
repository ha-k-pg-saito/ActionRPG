#include"../h/Map.h"

void Map::Init(int maphandle,int grhandle)
{
	m_MapHandle = maphandle;
#pragma region テクスチャ読み込み
	m_GrHandle[0] = grhandle;
	m_GrHandle[1] =  LoadGraph("Tex/grass.jpg");
	m_GrHandle[2] =  LoadGraph("Tex/ground.jpg");
	m_GrHandle[3] =  LoadGraph("Tex/bridge.jpg");
	m_GrHandle[4] =  LoadGraph("Tex/water.jpg");
	m_GrHandle[5] =  LoadGraph("Tex/wood.jpg");
	m_GrHandle[6] =  LoadGraph("Tex/bark.jpg");
#pragma endregion

	for (int i = 0; i <7 ; i++)
	{
		MV1SetTextureGraphHandle(m_MapHandle, i, m_GrHandle[i], FALSE);
	}
}

void Map::Draw()
{
	MV1SetPosition(m_MapHandle, m_Pos);
	MV1DrawModel(m_MapHandle);
}
