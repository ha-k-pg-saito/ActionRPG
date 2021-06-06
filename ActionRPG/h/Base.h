#ifndef Base_h_ 
#define Base_h_

#include"DxLib.h"

class CharBase
{
public:
	CharBase();		

	CharBase(float x, float y, float z,float hp,float speed);

	CharBase(VECTOR pos, float hp, float speed);

	virtual ~CharBase() {}		

//継承関連はprotectedを使用
protected:				
	VECTOR m_Pos;		//ポジション
	float   m_Hp;		//Hp
	float  m_Speed;		//スピード
};
#endif