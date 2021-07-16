#ifndef Animation_h_ 
#define Animation_h_

#include"DxLib.h"

//�A�j���[�V�����̏��
enum ANIM_LIST
{
	ANIM_IDLE,	   //�ҋ@
	ANIM_RUN,	   //����
	ANIM_ATTACK,   //�U��
	ANIM_DAMAGE,   //�_���[�W
	ANIM_DIED,	   //���S
	ANIM_NUM,	   //�ő吔
};

//�A�j���[�V�����̎��
struct MotionParam
{
	float StartFrame;	  //�A�j���[�V�����n��
	float FinishFrame;	  //�A�j���[�V�����I���
};

class Animation
{
public:
//�A�j���[�V�����penum
	Animation() :
		m_AnimHandle{ 0 },
		m_AnimAttachIndex{ 0 },
		m_AnimTotalTime{ 0.f }
	{}
	~Animation() {}

	//�A�j���[�V�����p�ϐ�
	int m_AnimHandle[ANIM_NUM];
	int m_AnimAttachIndex[ANIM_NUM];
	float m_AnimTotalTime[ANIM_NUM];
	/*
		�A�j���[�V�����̓ǂݍ��݁E�A�^�b�`�E���Đ����Ԏ擾
		�����[�����f���n���h���A�A�j���[�V�����ԍ�
	*/
	void InitAnimation(int mhandle, const char* animname);
};
#endif 