#ifndef TitleScene_h_
#define TitleScene_h_

#include"DxLib.h"

class TitleScene
{
public:
	TitleScene();
	~TitleScene() {}

public:
	void InitTitleScene();
	void RunTitleScene();
	void FinishTitleScene();

public:
	void TitleSceneUpdate();

private:
	bool Push;
};

#endif