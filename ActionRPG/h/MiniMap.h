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
		m_CirPos{ 50.f,0.f,50.f },
		m_PlayerPos{ 0.f }
	{}
	~MiniMap() {}
 
	void Init();
	void Update(Player* player);
	void Draw();


private:
#define CIRCLE_RAD 10

	int m_MiniHandle;
	int m_CircleHandle;
	VECTOR m_MapPos;
	VECTOR m_CirPos;
	VECTOR m_PlayerPos;
};

#endif