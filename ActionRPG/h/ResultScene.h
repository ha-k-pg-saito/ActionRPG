#ifndef ResultScene_h_
#define ResultScene_h_

#include"DxLib.h"

class ResultScene
{
public:
	ResultScene() :
		IsPush{ true },
		GrHandle{ 0 }
	{}
	~ResultScene() {}

	void InitResultScene();
	void RunResultScene();
	void FinishResultScene();

public:
	void ResultSceneUpdate();

private:
	bool IsPush;
	int GrHandle;
};
#endif