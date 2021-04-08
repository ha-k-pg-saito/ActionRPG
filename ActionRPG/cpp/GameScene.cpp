#include "../h/GameScene.h"
#include"../h/Scene.h"
#include"../h/Player.h"
#include"../h/Camera.h"

extern SceneKind g_SceneKind;
extern SceneStep g_SceneStep;

GameScene::GameScene()
{

}

void GameScene::InitGameScene()
{
	Player::Instance()->Update();
	
	g_SceneStep = SceneStep::Run;

	Push = true;
}

void GameScene::RunGameScene()
{
	
	Camera::Instance()->Update();
	
	Player::Instance()->Move();

	//‚Ç‚ÌƒV[ƒ“‚©‚í‚©‚é‚æ‚¤‚É
	DrawFormatString(0.f, 100.f, GetColor(255, 255, 255), "GameScene");

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

	Player::Instance()->Draw();
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
