#ifndef MiniMap_h_
#define MiniMap_h_
#include"../h/Player.h"
#include"DxLib.h"
#include"../h/Player.h"

class MiniMap
{
public: 
	MiniMap() :
		m_MiniHandle{ 0 },
		m_CircleHandle{ 0 },
		m_MapPos{ 0.f },
		m_Wide{ 0. },
		m_Height{ 0. },
		m_CirPos{ 50.f,0.f,50.f },
		m_PlayerPos{ 0.f }
	{}
	~MiniMap() {}
 
	void Init();
	void Update(Player* player);
	void Draw();


private:
#define CIRCLE_RAD 10    //�~�̔��a
#define INIT_TEX_POS 0   //�e�N�X�`���̍�����W
#define TEX_WIDE   1700.  //�e�N�X�`���̉���
#define TEX_HEIGHT 2480.  //�e�N�X�`���̏c��
#define TEXUV_SIZE 300   //�e�N�X�`��UV�̃T�C�Y
#define MAP_WIDE   997.357951 //�}�b�v�̉���
#define MAP_HEIGHT 1001.126301 //�}�b�v�̏c��

	int m_MiniHandle;
	int m_CircleHandle;
	double m_Wide;
	double m_Height;
	VECTOR m_MapPos;
	VECTOR m_CirPos;
	VECTOR m_PlayerPos;
};

#endif