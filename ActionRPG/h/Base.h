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
//�p���֘A��protected���g�p
protected:				
	VECTOR m_Pos;		//�|�W�V����
	int    m_Hp;		//Hp
	float  m_Speed;		//�X�s�[�h
	Capsule m_Capsule;  //�J�v�Z���쐻
};
#endif