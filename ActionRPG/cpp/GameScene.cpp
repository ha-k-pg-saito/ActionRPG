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
	//int PlayerModelHandle = MV1LoadModel("Tex/Cat/catoriginal (2).mv1");
	//マップのテクスチャ読み込み
	int MapGrHandle = LoadGraph("Tex/Stage/rock.jpg");
	//マップモデルの読み込み
	int MapHandle = MV1LoadModel("Tex/Stage/map.mv1");
	int SoundHandle = LoadSoundMem("Sound/怖い噂のある廃墟.mp3");
	map.Init(MapHandle, MapGrHandle);
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
	//Sound::Instance()->play();
}

void GameScene::FinishGameScene()
{
	Sound::Instance()->stop();
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
