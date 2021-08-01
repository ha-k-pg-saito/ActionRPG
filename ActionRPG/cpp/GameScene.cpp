#include "../h/GameScene.h"
#include"../h/Scene.h"
#include"../h/SoundManager.h"

extern SceneKind g_SceneKind;
extern SceneStep g_SceneStep;

void GameScene::InitGameScene()
{
	m_Map.Init();
	m_Player.Init();
	m_EnemyMng.Init();
	m_MiniMap.Init();
	//BGMの読み込み、キーの設定
	//m_SoundHandle=SoundMng::Instance()->Load("Sound/Stage.mp3", "Game");
	SoundMng::Instance()->Play("Game", DX_PLAYTYPE_LOOP);
	g_SceneStep = SceneStep::Run;
}

void GameScene::RunGameScene()
{
	m_EnemyMng.Update(m_Player.GetPos());
	m_Player.Update();
	m_Camera.Update(&m_Player);
	m_MiniMap.Update(&m_Player);
	for (int i=0;i< m_EnemyMng.GetEnemyNum();++i)
	{
		if (OnColl::Inatance()->Update(m_Player.GetCapsule(), m_EnemyMng.GetEnemy(i)->GetCapsule()))
		{
			m_Player.NoticeHit();
		}
	}
	IsAlive = m_Player.GetAliveFlag();
	if (IsAlive == false)
	{
		g_SceneStep = SceneStep::Finish;
	}
	//デバッグ用
	if (CheckHitKey(KEY_INPUT_Q) != 0) g_SceneStep = SceneStep::Finish;

	m_EnemyMng.CreateEnemy();

	for (int i = 0; i < m_EnemyMng.GetEnemyNum(); i++)
	{
		if (/*当たり判定  仮=> */CheckHitKey(KEY_INPUT_C) == 1)
		{
			m_IsCollision = true;
		}
		else
		{
			m_IsCollision = false;
		}

		// 攻撃判定 & 当たり判定 & Enemyがいるか
		if (/*攻撃判定 &&*/m_IsCollision == true && m_EnemyMng.GetEnemy(i)->IsActive == true)
		{
			m_EnemyMng.GetEnemy(i)->Damage();
		}

		if (m_EnemyMng.GetEnemy(i)->GetHp() <= 0)
		{
			m_EnemyMng.GetEnemy(i)->IsActive = false;
		}
	}
	OnColl::Inatance()->Draw(m_Player.GetCapsule());
	for (int i = 0; i < m_EnemyMng.GetEnemyNum(); ++i)
	{
		OnColl::Inatance()->Draw(m_EnemyMng.GetEnemy(i)->GetCapsule());
	}
	m_Map.Draw();
    m_MiniMap.Draw();
	m_Player.Draw();
	m_EnemyMng.Draw();
	
}

void GameScene::FinishGameScene()
{
	SoundMng::Instance()->Stop("Game");
	SoundMng::Instance()->Release("Game");
	g_SceneKind = SceneKind::SceneKind_Result;
	g_SceneStep = SceneStep::Init;
}

void GameScene::GameSceneUpdate()
{
	switch (g_SceneStep)
	{
	case SceneStep::Init:   InitGameScene();   break;
	case SceneStep::Run:    RunGameScene();    break;
	case SceneStep::Finish: FinishGameScene(); break;
	}
}
