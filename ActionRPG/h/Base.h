#ifndef Base_h_ 
#define Base_h_

#include"DxLib.h"
#include"../h/Shape.h"

class CharBase
{
public:
	CharBase();		

	CharBase(float x, float y, float z, int hp, float speed);

	CharBase(VECTOR pos, int hp, float speed);

	virtual ~CharBase() {}		

	Capsule* GetCapsule() { return &m_Capsule; }
	AABB*    GetAABB() { return &m_AABB; }
//継承関連はprotectedを使用
protected:				
	VECTOR  m_Pos;		//ポジション
	int     m_Hp;		//Hp
	float   m_Speed;	//スピード
	Capsule m_Capsule;  //カプセルによるあたり判定用の構造体
	AABB    m_AABB;		//AABBによるあたり判定用の構造体
};
#endif