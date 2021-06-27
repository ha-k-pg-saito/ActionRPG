#include"../h/Map.h"

void Map::Init()
{
#pragma region マップ関連読み込み
	const char* file_name[]
	{
		"Tex/Stage/rock.jpg",
		"Tex/Stage/ground.jpg",
		"Tex/Stage/bark.jpg",
		"Tex/Stage/wood.jpg",
		"Tex/Stage/wood kawa.jpg",
		"Tex/Stage/wood yuka.jpg",
		"Tex/Stage/wood kabe.jpg",
		"Tex/Stage/grass.jpg",
		"Tex/Stage/bridge.jpg",
		"Tex/Stage/water.jpg"
	};

	for (int i = 0; i < MAP_TEX_NUM; i++)
	{
		m_GrHandle[i] = LoadGraph(file_name[i]);
	}

	//初期マップモデル
	m_MapHandle = MV1LoadModel("Tex/Stage/map2.mv1");

#pragma endregion
	//モデルに貼るテクスチャの数分だけfor文を回す
	for (int i = 0; i <MAP_TEX_NUM ; i++)
	{
		MV1SetTextureGraphHandle(m_MapHandle, i, m_GrHandle[i], FALSE);
	}
	//もともとのマップデータを100倍している
	VECTOR Scale{ 100.f,100.f,100.f };
	MV1SetScale(m_MapHandle, Scale);
	MV1SetPosition(m_MapHandle, m_StagePos);
	//モデル全体のコリジョン情報構築
	MV1SetupCollInfo(m_MapHandle, -1, 8, 8, 8);
}

void Map::Draw()
{
	MV1DrawModel(m_MapHandle);
}

//マップとレイのあたり判定
//PlayerだけでなくEnemyでも使用する
bool Map::CollisionToModel(VECTOR startpos, VECTOR endpos, VECTOR* intersectpos)
{
	//-1番フレームとレイとのあたり判定
	//m_Posは始点・m_Lineは終点
	HitPoly = MV1CollCheck_Line(m_MapHandle, -1, startpos, endpos);

	if (HitPoly.HitFlag == 0)
	{	
		return false;
	}

	if (intersectpos != nullptr)
	{
		*intersectpos= HitPoly.HitPosition;
	}

	return true;

}
