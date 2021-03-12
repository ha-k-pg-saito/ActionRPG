#include"../h/Scene.h"
#include"../h/TitleScene.h"
#include"../h/GameScene.h"
#include"../h/ResultScene.h"

SceneKind g_SceneKind = SceneKind::SceneKind_Title;
SceneStep g_SceneStep = SceneStep::Init;

static TitleScene g_TitleScene;
static GameScene  g_GameScene;
static ResultScene  g_ResultScene;

void SceneUpdate()
{
	switch (g_SceneKind)
	{
	case SceneKind::SceneKind_Title:  g_TitleScene.TitleSceneUpdate();   break;
	case SceneKind::SceneKind_Game:   g_GameScene.GameSceneUpdate();	 break;
	case SceneKind::SceneKind_Result: g_ResultScene.ResultSceneUpdate(); break;
	}
}