#ifndef Scene_h_
#define Scene_h_

//ƒV[ƒ“‚Ìí—Ş
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

#endif