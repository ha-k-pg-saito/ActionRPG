#ifndef TitleScene_h_
#define TitleScene_h_

#include"DxLib.h"

class TitleScene
{
public:
	void InitTitleScene();
	void RunTitleScene();
	void FinishTitleScene();

public:
	void TitleSceneUpdate();

private:
	bool m_Push;
	int  m_FrameCounter;			
	int  m_GrHandle;
	int  m_SoundHandle;
};

#endif