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

	//Player��Enemy�̏���n���Ă���
	bool Update(const Capsule* player, const Capsule* enemy);
	bool OnCollisionAABB(const AABB& player, const AABB& enemy);
	void Draw(Capsule* capsule);

//�e���f���̔��a
#define PLATER_HIT_SIZE_R 2.
#define ENEMY_HIT_SIZE_R  4.2
//�J�v�Z���|���S���ׂ̍���
#define POLYGON_FINENESS  4
	
//���f���̉ߋ��̃|�W�V�����ۑ��p�ϐ�
	VECTOR m_OldPlayerPos;
	VECTOR m_PlayerPos;
	VECTOR m_EnemyTop;

private:
	OnColl() :
		m_OldPlayerPos{ 0.f },
		m_PlayerPos{ 0.f },
		m_EnemyTop{ 0.f }
	{}
	~OnColl() {}
};
#endif