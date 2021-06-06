#include "../h/GameScene.h"
#include"../h/Scene.h"
#include"../h/SoundManager.h"

extern SceneKind g_SceneKind;
extern SceneStep g_SceneStep;

void GameScene::InitGameScene()
{
	//マップのテクスチャ読み込み
	int MapGrHandle = LoadGraph("Tex/Stage/rock.jpg");
	//マップモデルの読み込み
	int MapHandle = MV1LoadModel("Tex/Stage/map2.mv1");
	Map.Init();
	Player.Init();
	EnemyMng.Init();
	m_SoundHandle=SoundMng::Instance()->Load("Sound/Stage.mp3", "ゲーム");
	//SoundMng::Instance()->Play("ゲーム", DX_PLAYTYPE_LOOP);
	IsPush = true;
	g_SceneStep = SceneStep::Run;
}

void GameScene::RunGameScene()
{
	EnemyMng.Update(Player.GetPos());
	Player.Update();
	Camera.Update(&Player);
	for (int i=0;i<EnemyMng.GetEnemyNum();++i)
	{
		Oncoll.Update(&Player, EnemyMng.GetEnemy(i));
	}
	IsPush = false;
	if (CheckHitKey(KEY_INPUT_RETURN) != 0)
	{
		if (IsPush == false)
		{
			IsPush = true;
			g_SceneStep = SceneStep::Finish;
		}
	}

	EnemyMng.CreateEnemy();

	Map.Draw();
	Player.Draw();
	EnemyMng.Draw();
	for (int i = 0; i < EnemyMng.GetEnemyNum(); ++i)
	{
		Oncoll.Draw(&Player, EnemyMng.GetEnemy(i));
	}
	

}

void GameScene::FinishGameScene()
{
	SoundMng::Instance()->Stop("ゲーム");
	SoundMng::Instance()->Release("ゲーム");
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
