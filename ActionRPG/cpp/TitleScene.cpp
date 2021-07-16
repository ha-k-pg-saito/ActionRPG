#include "../h/TitleScene.h"
#include"../h/Scene.h"
#include"../h/SoundManager.h"

extern SceneKind g_SceneKind;
extern SceneStep g_SceneStep;

void TitleScene::InitTitleScene()
{
	m_SoundHandle = SoundMng::Instance()->Load("Sound/Title.mp3", "Title");
	m_GrHandle = LoadGraph("Tex/Title.png");

	IsPush = true;
	m_FrameCounter = 0;
	SoundMng::Instance()->Play("Title", DX_PLAYTYPE_LOOP);
	g_SceneStep = SceneStep::Run;
}

void TitleScene::RunTitleScene()
{
	m_FrameCounter += 1;
	IsPush = false;
	if ((GetMouseInput() & MOUSE_INPUT_LEFT) != 0)
	{
		if (IsPush == false)
		{
				IsPush = true;
				g_SceneStep = SceneStep::Finish;
		}
	}
	DrawGraph(0, 0, m_GrHandle, TRUE);
	if (m_FrameCounter <= 20)
	{
		DrawString(750, 890, "���N���b�N�ŃQ�[���X�^�[�g", GetColor(0, 0, 0));
	}

	if (m_FrameCounter >= 40)
	{
		m_FrameCounter = 0;
	}
	
	 m_FontHandle = CreateFontToHandle(NULL, 30, 0);
	DrawStringToHandle(1600, 30, "ESC�ŃQ�[���I��", GetColor(0,0,0), m_FontHandle);
	DeleteFontToHandle(m_FontHandle);
}

void TitleScene::FinishTitleScene()
{
	SoundMng::Instance()->Stop("Title");
	SoundMng::Instance()->Release("Title");
	DeleteGraph(m_GrHandle);
	// �쐬�����t�H���g�f�[�^���폜����
	DeleteFontToHandle(m_FontHandle);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
	g_SceneKind = SceneKind::SceneKind_Game;
	g_SceneStep = SceneStep::Init;
}

void TitleScene::TitleSceneUpdate()
{
	switch (g_SceneStep)
	{
	case SceneStep::Init:   InitTitleScene();   break;
	case SceneStep::Run:    RunTitleScene();    break;
	case SceneStep::Finish: FinishTitleScene();	break;
	}
}
