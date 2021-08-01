#ifndef ResultScene_h_
#define ResultScene_h_
#include"../h/Emitter.h"

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
	Emitter m_Emitter;
};
#endif