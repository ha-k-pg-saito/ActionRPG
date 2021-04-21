#include "../h/GameScene.h"
#include"../h/Scene.h"

extern SceneKind g_SceneKind;
extern SceneStep g_SceneStep;

GameScene::GameScene()
{
}

void GameScene::InitGameScene()
{
	player.Init();
	Push = true;
	g_SceneStep = SceneStep::Run;
}

void GameScene::RunGameScene()
{
	player.Update();
	camera.Update();
	
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

	player.Draw();
	//’†S“_->(íœ‚Ì‰Â”\«‚à‚ ‚è)
	DrawCircle(960, 510,5, GetColor(255,255,255),TRUE);		
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
