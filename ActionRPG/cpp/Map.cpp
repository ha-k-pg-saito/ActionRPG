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
}

void Map::Draw()
{
	MV1SetPosition(m_MapHandle, m_Pos);
	MV1DrawModel(m_MapHandle);
}

//マップとレイのあたり判定
//PlayerだけでなくEnemyでも使用する
bool Map::CollisionToModel(VECTOR startpos,VECTOR endpos)
{
	//モデル全体のコリジョン情報構築
	MV1SetupCollInfo(m_MapHandle, -1, 8, 8, 8);
	//0番目のフレームのコリジョン情報を更新する
	MV1RefreshCollInfo(m_MapHandle, 0);
	//-1番フレームとレイとのあたり判定
	//m_Posは始点・m_Lineは終点
	HitPoly = MV1CollCheck_Line(m_MapHandle, -1, startpos, endpos);

	//当たったならその位置をレイの終点とする
	if (HitPoly.HitFlag == 1)
	{
		endpos = HitPoly.HitPosition;
		// 当たったかどうかを表示する
	/*	DrawFormatString(1200, 200, GetColor(255, 255, 255), "Hit Pos %f,%f",
			HitPoly.HitPosition.x, HitPoly.HitPosition.z);*/
	}
	else
	{
		DrawString(1200, 200, "NO HIT", GetColor(255, 255, 255));
	}
		return true;
}
