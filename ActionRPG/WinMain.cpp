#include "DxLib.h"
#include"h/Scene.h"

// �v���O������ WinMain ����n�܂�܂�
int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_  HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nCmdShow)
{ 
	//�E�C���h�E���[�h�ɕύX
	SetOutApplicationLogValidFlag(FALSE);
	ChangeWindowMode(TRUE);					//�E�B���h�E���[�h
	SetGraphMode(1920, 1080, 32);			//��ʃ��[�h�ύX
	SetBackgroundColor(120, 120, 120);		//�w�i�F
	SetFontSize(40);						//�t�H���g�T�C�Y
	SetUseLighting(TRUE);	                //���C�g
	SetUsePremulAlphaConvertLoad(FALSE);	//��Z�ς݃��摜�ɕϊ����邩�ǂ���
	SetUseTransColor(FALSE);				//�����F���g�p���邩�ǂ���

	if (DxLib_Init() == -1)					//�c�w���C�u��������������
	{
		return -1;							//�G���[���N�����璼���ɏI��
	}

	SetDrawScreen(DX_SCREEN_BACK);

	//�Q�[�����[�v
	while (true)
	{
		if (ProcessMessage() != 0)
		{
			break;
		}

		//Escape�L�[�ŃQ�[�������I��
		if (CheckHitKey(KEY_INPUT_ESCAPE))
		{
			break;
		}

		ClearDrawScreen();					//�`�悳�ꂽ���̍폜
		clsDx();							//�����폜
		
		SceneUpdate();

		ScreenFlip();						//��ʍX�V
	}

	DxLib_End();							 // �c�w���C�u�����g�p�̏I������

	return 0;								 // �\�t�g�̏I�� 
}