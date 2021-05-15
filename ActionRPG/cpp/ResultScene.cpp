#include "../h/ResultScene.h"
#include"../h/Scene.h"
#include"../h/Sound.h"

extern SceneKind g_SceneKind;
extern SceneStep g_SceneStep;

ResultScene::ResultScene()
{

}

void ResultScene::InitResultScene()
{
	int SoundHandle       = LoadSoundMem("Sound/•|‚¢‰\‚Ì‚ ‚é”pšÐ.mp3");
	Sound::Instance()->Init(SoundHandle);
	g_SceneStep = SceneStep::Run;

	Push = true;
}

void ResultScene::RunResultScene()
{
	DrawFormatString(0, 100, GetColor(255, 255, 255), "ResultScene");

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
	Sound::Instance()->play();
}

void ResultScene::FinishResultScene()
{
	Sound::Instance()->stop();
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
