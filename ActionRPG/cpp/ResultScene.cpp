#include "../h/ResultScene.h"
#include"../h/Scene.h"
#include"../h/SoundManager.h"

extern SceneKind g_SceneKind;
extern SceneStep g_SceneStep;

void ResultScene::InitResultScene()
{
	g_SceneStep = SceneStep::Run;
	//GrHandle = LoadGraph("Tx/GameOver.png");
	m_Emitter.Init();
	IsPush = true;
}

void ResultScene::RunResultScene()
{
	m_Emitter.Update();
	//m_Emitter.CreateBoll();
	IsPush = false;
	
	if (CheckHitKey(KEY_INPUT_RETURN) != 0)
	{
		if (IsPush == false)
		{
			IsPush = true;
			g_SceneStep = SceneStep::Finish;
		}
	}

	DrawGraph(0, 0, GrHandle, FALSE);
	m_Emitter.Draw();
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
