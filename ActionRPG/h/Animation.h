#ifndef Animation_h_ 
#define Animation_h_

#include"DxLib.h"

class Animation
{
public:
	//アニメーション用enum
	enum ANIM_LIST
	{
		ANIM_WAIT,
		ANIM_RUN,
		ANIM_ATTACK,
		ANIM_DAMAGE,
		ANIM_DIED,
		ANIM_NUM,
	};

	//アニメーション用変数
	int m_AnimHandle[ANIM_NUM];
	int m_AnimAttachIndex[ANIM_NUM];
	int m_AnimTotalTime[ANIM_NUM];

	//アニメーションの読み込み・アタッチ・総再生時間取得
	//引数ー＞モデルハンドル、文字列
	void InitAnimation(int mhandle, const char* filename[]);

	//アニメーションを切り替えるための関数
	//引数ー＞モデルハンドル、アニメーション番号、総再生時間
	void SetAnimation(int mhandle, ANIM_LIST type, float playtime);
};
#endif 