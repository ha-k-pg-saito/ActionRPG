#ifndef EffectBollMng_h_
#define EffectBollMng_h_

#include"../h/EffectBoll.h"

class Emitter
{
public:
	Emitter() :
		m_BollNum{ 50 },
		m_EmittionRate{ 20 },
		m_Timer{ 0 }
	{}
	~Emitter() {}
	void Init();
	void Update();
	void Draw();
	EffBoll* CreateBoll();
	EffBoll* GetBoll(int index) { return &EffBolls[index]; }
	int GetBollNum() { return m_BollNum; }

private:
	void Delete();
	void Emit();

private:
	EffBoll EffBolls[50];
	int     m_BollNum;
	int     m_EmittionRate;		//ï˙èoó¶
	int     m_Timer;
};


#endif