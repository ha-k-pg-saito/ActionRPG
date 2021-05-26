#include "../h/TitleScene.h"
#include"../h/Scene.h"
#include"../h/SoundManager.h"

extern SceneKind g_SceneKind;
extern SceneStep g_SceneStep;

void TitleScene::InitTitleScene()
{
	//m_SoundHandle = SoundMng::Instance()->Load("Sound/Title.mp3", "Title");
	m_GrHandle = LoadGraph("Tex/Title.png");

	m_Push = true;
	m_FrameCounter = 0;

	g_SceneStep = SceneStep::Run;
}

void TitleScene::RunTitleScene()
{
	m_FrameCounter++;

	if ((GetMouseInput() & MOUSE_INPUT_LEFT) != 0)
	{
		if (m_Push == false)
		{
			m_Push = true;
			g_SceneStep = SceneStep::Finish;
		}
	}
	else
	{
		m_Push = false;
	}

	DrawGraph(0, 0, m_GrHandle, FALSE);

	if (m_FrameCounter < 60)
	{
		DrawString(470, 890, "左クリックでゲームスタート", GetColor(0, 0, 0));
	}

	if (m_FrameCounter >= 120)
	{
		m_FrameCounter = 0;
	}
	
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
