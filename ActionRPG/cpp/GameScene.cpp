#include "../h/GameScene.h"
#include"../h/Scene.h"

extern SceneKind g_SceneKind;
extern SceneStep g_SceneStep;

GameScene::GameScene()
{
}

void GameScene::InitGameScene()
{
	// モデルのテクスチャ読み込み
	int PlayerGrHandle    = LoadGraph("Tex/Player/sister_body.png");
	// モデルの読み込み
	int PlayerModelHandle = MV1LoadModel("Tex/Player/sister.mv1");
	//デバッグ用敵モデル読み込み
	//int PlayerModelHandle = MV1LoadModel("Tex/cat.mv1");
	//マップのテクスチャ読み込み
	int MapGrHandle       = LoadGraph("Tex/Stage/rock.jpg");
	int LastMGrHandle     = LoadGraph("Tex/Stage/rock.jpg");
	//マップモデルの読み込み
	int MapHandle         = MV1LoadModel("Tex/Stag/map.mv1");
	int LastMHandle       = MV1LoadModel("Tex/Stage/lastmap.mv1");
	int SoundHandle = LoadSoundMem("Sound/");
	map.Init(MapHandle, MapGrHandle,LastMHandle,LastMGrHandle);
	player.Init(PlayerModelHandle, PlayerGrHandle);
	Sound::Instance()->Init(SoundHandle);
	Push = true;
	g_SceneStep = SceneStep::Run;
}

void GameScene::RunGameScene()
{
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

	map.Draw();
	player.Draw();
}

void GameScene::FinishGameScene()
{
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
