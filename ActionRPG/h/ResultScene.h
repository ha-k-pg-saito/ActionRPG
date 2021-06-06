#ifndef ResultScene_h_
#define ResultScene_h_

#include"DxLib.h"

class ResultScene
{
public:
	ResultScene() :
		IsPush{ true }
	{}
	~ResultScene() {}

	void InitResultScene();
	void RunResultScene();
	void FinishResultScene();

public:
	void ResultSceneUpdate();

private:
	bool IsPush;
};
#endif