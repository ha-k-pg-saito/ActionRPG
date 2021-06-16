#include "../h/GameScene.h"
#include"../h/Scene.h"
#include"../h/SoundManager.h"

extern SceneKind g_SceneKind;
extern SceneStep g_SceneStep;

void GameScene::InitGameScene()
{
	Map.Init();
	Player.Init();
	EnemyMng.Init();
	//BGM‚Ì“Ç‚Ýž‚ÝAƒL[‚ÌÝ’è
	m_SoundHandle=SoundMng::Instance()->Load("Sound/Stage.mp3", "Game");
	SoundMng::Instance()->Play("Game", DX_PLAYTYPE_LOOP);
	g_SceneStep = SceneStep::Run;
}

void GameScene::RunGameScene()
{
	EnemyMng.Update(Player.GetPos());
	Player.Update();
	Camera.Update(&Player);
	for (int i=0;i<EnemyMng.GetEnemyNum();++i)
	{
		OnColl::Inatance()->Update(&Player, EnemyMng.GetEnemy(i));
	}
	IsAlive = Player.GetAliveFlag();
	if (IsAlive == false)
	{
		g_SceneStep = SceneStep::Finish;
	}

	EnemyMng.CreateEnemy();

	Map.Draw();
	Player.Draw();
	EnemyMng.Draw();
	for (int i = 0; i < EnemyMng.GetEnemyNum(); ++i)
	{
		OnColl::Inatance()->Draw(&Player, EnemyMng.GetEnemy(i));
	}
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
