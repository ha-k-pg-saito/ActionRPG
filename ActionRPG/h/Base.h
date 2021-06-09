#ifndef Base_h_ 
#define Base_h_

#include"DxLib.h"

class CharBase
{
public:
	CharBase();		

	CharBase(float x, float y, float z, int hp, float speed);

	CharBase(VECTOR pos, int hp, float speed);

	virtual ~CharBase() {}		

//継承関連はprotectedを使用
protected:				
	VECTOR m_Pos;		//ポジション
	int    m_Hp;		//Hp
	float  m_Speed;		//スピード
};
#endif