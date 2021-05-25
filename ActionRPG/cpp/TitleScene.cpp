#include "../h/TitleScene.h"
#include"../h/Scene.h"
#include"../h/SoundManager.h"

extern SceneKind g_SceneKind;
extern SceneStep g_SceneStep;

TitleScene::TitleScene()
{

}

void TitleScene::InitTitleScene()
{
	m_SoundHandle = SoundMng::Instance()->Load("Sound/Title.mp3", "Title");
	m_GrHandle = LoadGraph("Tex/Title.png");
	Push = true;
	g_SceneStep = SceneStep::Run;
}

void TitleScene::RunTitleScene()
{
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
	DrawGraph(0, 0, m_GrHandle, FALSE);
	SoundMng::Instance()->Play("Title", DX_PLAYTYPE_LOOP);
}

void TitleScene::FinishTitleScene()
{
	SoundMng::Instance()->Stop("Title");
	SoundMng::Instance()->Release("Title");
	DeleteGraph(m_GrHandle);
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
