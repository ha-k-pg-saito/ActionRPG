#ifndef Animation_h_ 
#define Animation_h_

#include"DxLib.h"

//アニメーションの状態
enum ANIM_LIST
{
	ANIM_IDLE,	   //待機
	ANIM_RUN,	   //走り
	ANIM_ATTACK,   //攻撃
	ANIM_DAMAGE,   //ダメージ
	ANIM_DIED,	   //死亡
	ANIM_NUM,	   //最大数
};

//アニメーションの種類
struct MotionParam
{
	float StartFrame;	  //アニメーション始め
	float FinishFrame;	  //アニメーション終わり
};

class Animation
{
public:
//アニメーション用enum
	Animation() :
		m_AnimHandle{ 0 },
		m_AnimAttachIndex{ 0 },
		m_AnimTotalTime{ 0.f }
	{}
	~Animation() {}

	//アニメーション用変数
	int m_AnimHandle[ANIM_NUM];
	int m_AnimAttachIndex[ANIM_NUM];
	float m_AnimTotalTime[ANIM_NUM];
	/*
		アニメーションの読み込み・アタッチ・総再生時間取得
		引数ー＞モデルハンドル、アニメーション番号
	*/
	void InitAnimation(int mhandle, const char* animname);
};
#endif 