#ifndef Shape_h_
#define Shape_h_
#include"DxLib.h"

//�o�E���f�B���O�{�b�N�X�𗘗p���������蔻����쐻���邽�߂̍\����
struct AABB
{
	VECTOR Max;				 //�ŏ��l
	VECTOR Min;				 //�ő�l
	VECTOR OldPos;			 //�O�̍��W�ۑ�

//default�ŏ��������邱�ƂŖ����I�ɒ�`�ł���
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
		//��L�̌v�Z�ŋ��߂��l��xyz�ɉ��Z����
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
		//�J�v�Z���̃����o���O�ŏ�����
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
		//��L�̌v�Z�ŋ��߂��l��xyz�ɉ��Z����
		Bottom = VAdd(Bottom, Diff);
		Top = VAdd(Top, Diff);
		OldPos = objpos;
	}
};
#endif