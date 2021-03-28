#include "../h/ResultScene.h"
#include"../h/Scene.h"

extern SceneKind g_SceneKind;
extern SceneStep g_SceneStep;

ResultScene::ResultScene()
{

}

void ResultScene::InitResultScene()
{
	g_SceneStep = SceneStep::Run;
}

void ResultScene::RunResultScene()
{

	DrawFormatString(0.f, 100.f, GetColor(255, 255, 255), "ResultScene");

	if (CheckHitKey(KEY_INPUT_RETURN) != 0)
	{
		g_SceneStep = SceneStep::Finish;
	}
}

void ResultScene::FinishResultScene()
{
	g_SceneKind = SceneKind::SceneKind_Title;
	g_SceneStep = SceneStep::Init;
}

void ResultScene::ResultSceneUpdate()
{

	switch (g_SceneStep)
	{
	case SceneStep::Init:   InitResultScene();   break;
	case SceneStep::Run:    RunResultScene();    break;
	case SceneStep::Finish: FinishResultScene(); break;
	}

}
