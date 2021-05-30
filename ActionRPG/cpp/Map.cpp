#include"../h/Map.h"

void Map::Init(int maphandle,int grhandle)
{
#pragma region マップモデル読み込み
	//初期マップモデル
	m_MapHandle = maphandle;
	//初期マップテクスチャ
	m_GrHandle[0] = grhandle;
	m_GrHandle[1] =  LoadGraph("Tex/Stage/ground.jpg");
	m_GrHandle[2] =  LoadGraph("Tex/Stage/bark.jpg");
	m_GrHandle[3] =  LoadGraph("Tex/Stage/wood.jpg");
	m_GrHandle[4] =  LoadGraph("Tex/Stage/wood kawa.jpg");
	m_GrHandle[5] =  LoadGraph("Tex/Stage/wood yuka.jpg");
	m_GrHandle[6] =  LoadGraph("Tex/Stage/wood kabe.jpg");
	m_GrHandle[7] =  LoadGraph("Tex/Stage/grass.jpg");
	m_GrHandle[8] =  LoadGraph("Tex/Stage/bridge.jpg");
	m_GrHandle[9] =  LoadGraph("Tex/Stage/water.jpg");

#pragma endregion
	//モデルに貼るテクスチャの数分だけfor文を回す
	for (int i = 0; i <10 ; i++)
	{
		MV1SetTextureGraphHandle(m_MapHandle, i, m_GrHandle[i], FALSE);
	}
	//もともとのマップデータを100倍している
	MV1SetScale(m_MapHandle, VECTOR{ 100,100,100 });
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
