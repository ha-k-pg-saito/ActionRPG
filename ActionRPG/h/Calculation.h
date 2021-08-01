#ifndef Calculation_h_
#define Calculation_h_

#include"DxLib.h"
#include<math.h>

//valueが最小値・最大値を超えないようにする
static void Clamp(float& value,float min,float max) 
{
	if (value < min)
	{
		value = min;
	}
	if (value > max)
	{
		value = max;
	}
}

//線形補間
//引数ー＞移動前の座標、移動後の座標
static VECTOR Lerp(VECTOR vec1, VECTOR vec2, float time)
{
	Clamp(time, 0.1f, 1.f);
	VECTOR c;
	c.x = vec1.x * (1 - time) + vec2.x * time;
	c.y = vec1.y * (1 - time) + vec2.y * time;
	c.z = vec1.z * (1 - time) + vec2.z * time;

	return c;
}

//球面線形補間
//引数ー＞移動前の座標、移動後の座標、回転スピード
static VECTOR Slerp(VECTOR vec1, VECTOR vec2, float time)
{
	Clamp(time, -1.f, 1.f);
	VECTOR NormalVec1, NormalVec2;
	if (vec1.x != 0.f || vec1.y != 0.f || vec1.z != 0.f)
	{
		//ベクトルの正規化
		 NormalVec1 = VNorm(vec1);
	}
	if (vec2.x != 0.f || vec2.y != 0.f || vec2.z != 0.f)
	{
		//ベクトルの正規化
		 NormalVec2 = VNorm(vec2);
	}
	//二つのベクトルの角度
	//内積・外積を求めるときはドット積
	float d = VDot(NormalVec1, NormalVec2);
	Clamp(d, -1.f, 1.f);
	float angle = acosf(d);
	//sinθ
	float SinTh = sinf(angle);
	
	float Ps = sinf(angle * (1 - time));
	float Pe = sinf(angle * time);

	NormalVec1.x *= Ps;
	NormalVec1.z *= Ps;
	NormalVec2.x *= Pe;
	NormalVec2.z *= Pe;

	VECTOR v = VAdd(NormalVec1, NormalVec2);
	if (SinTh != 0.f)
	{
		v.x /= SinTh;
		v.z /= SinTh;
	}

	return v;
}
#endif