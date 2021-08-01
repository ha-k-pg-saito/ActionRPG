#ifndef Shape_h_
#define Shape_h_
#include"DxLib.h"

//バウンディングボックスを利用したあたり判定を作製するための構造体
struct AABB
{
	VECTOR Max;				 //最小値
	VECTOR Min;				 //最大値
	VECTOR OldPos;			 //前の座標保存

//defaultで初期化することで明示的に定義できる
	~AABB() = default;
	AABB()
	{
		ZeroMemory(this, sizeof(AABB));
	}
	AABB(VECTOR minvalue, VECTOR maxvalue, VECTOR postpos) :
		Min{ minvalue },
		Max{ maxvalue },
		OldPos{ postpos }
	{
	}

	void Update(const VECTOR& objpos)
	{
		VECTOR Diff = VSub(objpos, OldPos);
		//上記の計算で求めた値をxyzに加算する
		Min = VAdd(Min, Diff);
		Max = VAdd(Max, Diff);
		OldPos = objpos;
	}
};

struct Capsule
{
	float Radius;
	VECTOR Bottom;
	VECTOR Top;
	VECTOR OldPos;

	~Capsule() = default;

	Capsule() 
	{
		//カプセルのメンバを０で初期化
		ZeroMemory(this, sizeof(Capsule));
	}

	Capsule(float radius, VECTOR bottom, VECTOR top, VECTOR oldpos) :
		Radius{ radius },
		Bottom{ bottom },
		Top{ top },
		OldPos{ oldpos }
	{
	}

	void Update(const VECTOR& objpos)
	{
		VECTOR Diff = VSub(objpos, OldPos);
		//上記の計算で求めた値をxyzに加算する
		Bottom = VAdd(Bottom, Diff);
		Top = VAdd(Top, Diff);
		OldPos = objpos;
	}
};
#endif