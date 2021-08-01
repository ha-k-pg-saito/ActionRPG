#include"../h/Emitter.h"

void Emitter::Init()
{
	/*for (int i = 0; i < m_BollNum; i++)
	{
		EffBolls[i].Init();
	}*/
}

void Emitter::Update()
{
	++m_Timer;
	if (m_Timer % m_EmittionRate == 0)
	{
		Emit();
	}
	for (int i = 0; i < m_BollNum; i++)
	{
		if (EffBolls[i].IsAlive() == false)
		{
			continue;
		}

		EffBolls[i].Update();
	}
}

void Emitter::Draw()
{
	for (int i = 0; i < m_BollNum; i++)
	{
		if (EffBolls[i].IsAlive() == false)
		{
			continue;
		}

		EffBolls[i].Draw();
	}
}

void Emitter::Delete()
{
	for (int i = 0; i < m_BollNum; i++)
	{
		if (EffBolls[i].IsActive == false)
		{
			continue;
		}
		EffBolls[i].Delete();
	}
}

void Emitter::Emit()
{
	for (int i = 0; i < m_BollNum; i++)
	{
		if (EffBolls[i].IsAlive())
		{
			continue;
		}
	
		EffBolls[i].Init();
		break;
	}
}

EffBoll* Emitter::CreateBoll()
{
	for (int i = 0; i < m_BollNum; i++)
	{
		// 非アクティブの敵をアクティブに変更する => 敵を生成する
		if (EffBolls[i].IsActive == false)
		{
			EffBolls[i].Init();
			EffBolls[i].IsActive = true;

			return &EffBolls[i];
		}
	}
	return nullptr;
}