#include"../h/Map.h"

void Map::Init()
{
	m_MapHandle = MV1LoadModel("Tex/map.mv1");
}

void Map::Draw()
{
	MV1SetPosition(m_MapHandle, m_Pos);
	MV1DrawModel(m_MapHandle);
}
