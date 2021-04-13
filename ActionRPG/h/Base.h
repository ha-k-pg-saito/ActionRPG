#ifndef Base_h_ 
#define Base_h_

#include"DxLib.h"

class Base
{
public:
	Base();				//コンストラクタ

	Base(float x, float y, float z);

	Base(VECTOR pos);

	~Base() {}			//デストラクタ

protected:				//継承関連はprotectedを使用
	VECTOR m_Pos;		//ポジション
	float  m_Hp;		//Hp
	float  m_Speed;		//スピード
};


#endif