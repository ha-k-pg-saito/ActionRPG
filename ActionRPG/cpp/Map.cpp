#include"../h/Map.h"

void Map::Init(int maphandle,int grhandle,int lastmaphandle,int lastgrhandle)
{
	
#pragma region マップモデル読み込み
	//初期マップモデル
	m_MapHandle = maphandle;
	//初期マップテクスチャ
	m_GrHandle[0] = grhandle;
	m_GrHandle[1] =  LoadGraph("Tex/Stage/grass.jpg");
	m_GrHandle[2] =  LoadGraph("Tex/Stage/ground.jpg");
	m_GrHandle[3] =  LoadGraph("Tex/Stage/bridge.jpg");
	m_GrHandle[4] =  LoadGraph("Tex/Stage/water.jpg");
	m_GrHandle[5] =  LoadGraph("Tex/Stage/wood.jpg");
	m_GrHandle[6] =  LoadGraph("Tex/Stage/bark.jpg");
	//ボス戦のマップモデル
	m_LastMHandle = lastmaphandle;
	//ボス戦のマップテクスチャ
	m_LastMGrHandle[0] = lastgrhandle;
	m_LastMGrHandle[1] = LoadGraph("Tex/Stage/wood kawa.jpg");
	m_LastMGrHandle[2] = LoadGraph("Tex/Stage/wood yuka.jpg");
	m_LastMGrHandle[3] = LoadGraph("Tex/Stage/wood kabe.jpg");
#pragma endregion
	//モデルに貼るテクスチャの数分だけfor文を回す
	for (int i = 0; i <7 ; i++)
	{
		MV1SetTextureGraphHandle(m_MapHandle, i, m_GrHandle[i], FALSE);
	}
	for (int i = 0; i < 4; i++)
	{
		MV1SetTextureGraphHandle(m_LastMHandle, i, m_LastMGrHandle[i], FALSE);
	}
}

void Map::Draw()
{
	MV1SetPosition(m_MapHandle, m_Pos);
	MV1DrawModel(m_MapHandle);
	//MV1SetPosition(m_LastMHandle, m_Pos);
	//MV1DrawModel(m_LastMHandle);
}
