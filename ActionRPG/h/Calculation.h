#ifndef Calculation_h_
#define Calculation_h_

#include"DxLib.h"
#include<math.h>

void Clamp(float& value,float min,float max) 
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

VECTOR Lerp(VECTOR vec1, VECTOR vec2, float time)
{
	Clamp(time, 0.f, 1.f);
	VECTOR c;
	c.x = vec1.x * (1 - time) + vec2.x * time;
	c.y = vec1.y * (1 - time) + vec2.y * time;
	c.z = vec1.z * (1 - time) + vec2.z * time;

	return c;
}

VECTOR Slerp(VECTOR vec1, VECTOR vec2, float time)
{
	Clamp(time, -1.f, 1.f);
	VECTOR NormalVec1, NormalVec2;
	if (vec1.x != 0.f || vec1.y != 0.f || vec1.z != 0)
	{
		//ベクトルの正規化
		 NormalVec1 = VNorm(vec1);
	}
	if (vec2.x != 0.f || vec2.y != 0.f || vec2.z != 0)
	{
		//ベクトルの正規化
		 NormalVec2 = VNorm(vec2);
	}
	//二ベクトルの角度
	float d = VDot(NormalVec1, NormalVec2);
	Clamp(d, -1.f, 1.f);
	float angle = acos(d);
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
#endif // !1