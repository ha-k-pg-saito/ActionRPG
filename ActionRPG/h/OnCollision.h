#ifndef OnCollision_h_
#define OnCollision_h_

#include"../h/Shape.h"

class OnColl
{
public:
	static OnColl* Inatance()
	{
		static OnColl instance;
		return &instance;
	}

	//PlayerとEnemyの情報を渡している
	bool Update(const Capsule* player, const Capsule* enemy);
	bool OnCollisionAABB(const AABB* player, const AABB* enemy);
	void Draw(Capsule* capsule);

	const float m_PolyFine;

//モデルの過去のポジション保存用変数
	VECTOR m_OldPlayerPos;
	VECTOR m_PlayerPos;
	VECTOR m_EnemyTop;

private:
	OnColl() :
		m_OldPlayerPos{ 0.f },
		m_PlayerPos{ 0.f },
		m_EnemyTop{ 0.f },
		m_PolyFine{ 4.f }
	{}
	~OnColl() {}
};
#endif