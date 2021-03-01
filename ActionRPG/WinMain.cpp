#include"DxLib.h"
#include"h/Camera.h"

// プログラムは WinMain から始まります
int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_  HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nCmdShow)
{
	int ModelHandle;

	//ウインドウモードに変更
	SetOutApplicationLogValidFlag(FALSE);
	ChangeWindowMode(TRUE);					//ウィンドウモード
	SetGraphMode(640, 480, 32);				//画面モード変更
	SetBackgroundColor(0, 0, 0);			//背景色
	SetFontSize(75);						//フォントサイズ

	if (DxLib_Init() == -1)					//ＤＸライブラリ初期化処理
	{
		return -1;							//エラーが起きたら直ちに終了
	}

	SetDrawScreen(DX_SCREEN_BACK);			//裏面に描画

	//ゲームループ
	while (true)
	{
		if (ProcessMessage() != 0)
		{
			break;
		}

		ClearDrawScreen();					//描画されたもの削除
		clsDx();							//文字描画

		
		ScreenFlip();						//画面更新

	}

	DxLib_End();							 // ＤＸライブラリ使用の終了処理

	return 0;								 // ソフトの終了 
}