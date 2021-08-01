#ifndef Calculation_h_
#define Calculation_h_

#include"DxLib.h"
#include<math.h>

//value���ŏ��l�E�ő�l�𒴂��Ȃ��悤�ɂ���
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

//���`���
//�����[���ړ��O�̍��W�A�ړ���̍��W
static VECTOR Lerp(VECTOR vec1, VECTOR vec2, float time)
{
	Clamp(time, 0.1f, 1.f);
	VECTOR c;
	c.x = vec1.x * (1 - time) + vec2.x * time;
	c.y = vec1.y * (1 - time) + vec2.y * time;
	c.z = vec1.z * (1 - time) + vec2.z * time;

	return c;
}

//���ʐ��`���
//�����[���ړ��O�̍��W�A�ړ���̍��W�A��]�X�s�[�h
static VECTOR Slerp(VECTOR vec1, VECTOR vec2, float time)
{
	Clamp(time, -1.f, 1.f);
	VECTOR NormalVec1, NormalVec2;
	if (vec1.x != 0.f || vec1.y != 0.f || vec1.z != 0.f)
	{
		//�x�N�g���̐��K��
		 NormalVec1 = VNorm(vec1);
	}
	if (vec2.x != 0.f || vec2.y != 0.f || vec2.z != 0.f)
	{
		//�x�N�g���̐��K��
		 NormalVec2 = VNorm(vec2);
	}
	//��̃x�N�g���̊p�x
	//���ρE�O�ς����߂�Ƃ��̓h�b�g��
	float d = VDot(NormalVec1, NormalVec2);
	Clamp(d, -1.f, 1.f);
	float angle = acosf(d);
	//sin��
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