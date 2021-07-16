#ifndef TitleScene_h_
#define TitleScene_h_

#include"DxLib.h"

class TitleScene
{
public:

	TitleScene() :
		IsPush{ true },
		m_FrameCounter{ 0 },
		m_GrHandle{ 0 },
		m_SoundHandle{ 0 }
	{}
	~TitleScene() {}
	void InitTitleScene();
	void RunTitleScene();
	void FinishTitleScene();

public:
	void TitleSceneUpdate();

private:
	bool IsPush;
	int  m_FrameCounter;			
	int  m_GrHandle;
	int  m_SoundHandle;
	int m_FontHandle;
};
#endif