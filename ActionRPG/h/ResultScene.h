#ifndef ResultScene_h_
#define ResultScene_h_
#include"../h/EffectBoll.h"

#include"DxLib.h"

class ResultScene
{
public:
	ResultScene() :
		IsPush{ true },
		GrHandle{ 0 }
	{
		//Boll = EffBoll;
	}
	~ResultScene() {}

	void InitResultScene();
	void RunResultScene();
	void FinishResultScene();

public:
	void ResultSceneUpdate();

private:
	bool IsPush;
	int GrHandle;
	EffBoll Boll;
};
#endif