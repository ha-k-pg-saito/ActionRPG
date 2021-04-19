#ifndef Player_h_
#define Player_h_
#include"Base.h"

class Player :public Base
{
	//アニメーションリスト
	enum ANIM_LIST
	{
		//走るアニメーション
		ANIM_RUN,

		ANIM_NUM,
	};

public:
	Player();		
	~Player() {}		

public:
	void Init();
	void Update();
	void Draw();
	void Move();
	void HP();

private:
	// モデルを保存する変数
	int   m_ModelHandle;

	//アニメーションに使用する変数
	int   m_AnimHandle[ANIM_NUM];
	int   m_AnimAttachIndex[ANIM_NUM];
	int   m_AnimTotalTime[ANIM_NUM];
	int   m_PlayTime;						//アニメーション時間

	//計算で使う変数
	float m_Radian;						//角度	
	float m_Digree_X, m_Digree_Z;		//向きベクトルの保存

};


#endif // !Player_h_



