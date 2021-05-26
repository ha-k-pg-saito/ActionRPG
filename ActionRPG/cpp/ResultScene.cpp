#include "../h/ResultScene.h"
#include"../h/Scene.h"
#include"../h/SoundManager.h"

extern SceneKind g_SceneKind;
extern SceneStep g_SceneStep;

void ResultScene::InitResultScene()
{
	g_SceneStep = SceneStep::Run;

	m_Push = true;
}

void ResultScene::RunResultScene()
{
	DrawFormatString(0, 100, GetColor(255, 255, 255), "ResultScene");

	
	if (CheckHitKey(KEY_INPUT_RETURN) != 0)
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
}

void ResultScene::FinishResultScene()
{
	SoundMng::Instance()->Stop("Dead");
	SoundMng::Instance()->Stop("Clear");
	SoundMng::Instance()->Release("Dead");
	SoundMng::Instance()->Release("Clear");
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
