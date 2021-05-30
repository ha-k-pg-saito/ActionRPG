#include "../h/GameScene.h"
#include"../h/Scene.h"
#include"../h/SoundManager.h"

extern SceneKind g_SceneKind;
extern SceneStep g_SceneStep;

void GameScene::InitGameScene()
{
	// モデルのテクスチャ読み込み
	int PlayerGrHandle    = LoadGraph("Tex/Player/sister_body.png");
	// モデルの読み込み
	//int PlayerModelHandle = MV1LoadModel("Tex/Player/sister.mv1");
	//デバッグ用敵モデル読み込み
	int PlayerModelHandle = MV1LoadModel("Tex/Cat/catoriginal.mv1");
	//マップのテクスチャ読み込み
	int MapGrHandle = LoadGraph("Tex/Stage/rock.jpg");
	//マップモデルの読み込み
	int MapHandle = MV1LoadModel("Tex/Stage/map2.mv1");
	map.Init(MapHandle, MapGrHandle);
	player.Init(PlayerModelHandle, PlayerGrHandle);
	EnemyMng.Init();
	SoundHandle=SoundMng::Instance()->Load("Sound/Stage.mp3", "ゲーム");
	Push = true;
	g_SceneStep = SceneStep::Run;
}

void GameScene::RunGameScene()
{
	EnemyMng.Update(player.GetPos());
	player.Update();
	camera.Update(&player);

	if (CheckHitKey(KEY_INPUT_RETURN) != 0)
	{
		if (Push == false)
		{
			Push = true;
			g_SceneStep = SceneStep::Finish;
		}
	}
	else
	{
		Push = false;
	}
	EnemyMng.CreateEnemy();


	map.Draw();
	player.Draw();
	EnemyMng.Draw();
	SoundMng::Instance()->Play("ゲーム", DX_PLAYTYPE_LOOP);
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
