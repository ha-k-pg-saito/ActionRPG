#include "../h/TitleScene.h"
#include"../h/Scene.h"

extern SceneKind g_SceneKind;
extern SceneStep g_SceneStep;

TitleScene::TitleScene()
{

}

void TitleScene::InitTitleScene()
{
	g_SceneStep = SceneStep::Run;

	Push = true;
}

void TitleScene::RunTitleScene()
{

	DrawFormatString(0.f, 100.f, color, "TitleScene");

	if (CheckHitKey(KEY_INPUT_RETURN)!=0)
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
}

void TitleScene::FinishTitleScene()
{
	g_SceneKind = SceneKind::SceneKind_Game;
	g_SceneStep = SceneStep::Init;
}

void TitleScene::TitleSceneUpdate()
{

	switch (g_SceneStep)
	{
	case SceneStep::Init:   InitTitleScene();   break;
	case SceneStep::Run:    RunTitleScene();    break;
	case SceneStep::Finish: FinishTitleScene();	break;
	}

}
