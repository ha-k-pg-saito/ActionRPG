#ifndef ResultScene_h_
#define ResultScene_h_

#include"DxLib.h"

class ResultScene
{
public:
	ResultScene();
	~ResultScene() {}

public:
	void InitResultScene();
	void RunResultScene();
	void FinishResultScene();

public:
	void ResultSceneUpdate();

};

#endif