#ifndef Map_h_
#define Map_h_

#include"DxLib.h"

class Map
{
public:
	Map() :
		m_MapHandle(0),
		m_StagePos{ 71,-10,462 },
		HitPoly{ 0 }
	{}
	~Map() {}

public:	
	//モデル情報を渡すゲッター
	int GetModel(){ return m_MapHandle; }

public:
	void Init();
	void Draw();
	bool CollisionToModel(VECTOR startpos, VECTOR endpos,VECTOR* intersectpos);

private:
	//マップモデル保存用変数
	int    m_MapHandle;
	//マップに貼るテクスチャ保存変数
	int    m_GrHandle[10];
	VECTOR m_StagePos;
	//DxLibにあるあたり判定用の戻り値+変数
	MV1_COLL_RESULT_POLY HitPoly;

#define MAP_TEX_NUM      10
};
#endif