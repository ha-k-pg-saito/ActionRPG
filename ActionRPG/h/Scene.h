#ifndef Scene_h_
#define Scene_h_

#include"DxLib.h"
//シーンの種類
enum SceneKind
{
	SceneKind_Title,
	SceneKind_Game,
	SceneKind_Result
};

enum SceneStep
{
	Init,
	Run,
	Finish
};

void SceneUpdate();

//値が変わらないのでconst使用
static const int color = GetColor(255, 255, 255);

#endif