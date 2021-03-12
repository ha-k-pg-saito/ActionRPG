#include "../h/GameScene.h"
#include"../h/Scene.h"

extern SceneKind g_SceneKind;
extern SceneStep g_SceneStep;

GameScene::GameScene()
{

}

void GameScene::InitGameScene()
{
	g_SceneStep = SceneStep::Run;
}

void GameScene::RunGameScene()
{
	DrawFormatString(0.f, 100.f, GetColor(255, 255, 255), "GameScene");

	if (CheckHitKey(KEY_INPUT_ESCAPE) != 0)
	{
		g_SceneStep = SceneStep::Finish;
	}
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
