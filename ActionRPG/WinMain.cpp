#include "DxLib.h"
#include "h/Player.h"

// プログラムは WinMain から始まります
int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_  HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nCmdShow)
{
	Player player;  // PlayerClassのローカル変数

	//ウインドウモードに変更
	SetOutApplicationLogValidFlag(FALSE);
	ChangeWindowMode(TRUE);				//ウィンドウモード
	SetGraphMode(640, 480, 32);		//画面モード変更
	SetBackgroundColor(0, 0, 0);	//背景色
	SetFontSize(75);					//フォントサイズ
	SetCameraNearFar(1.f,150.f);

	if (DxLib_Init() == -1)  // ＤＸライブラリ初期化処理
	{
		return -1;   // エラーが起きたら直ちに終了
	}

	player.Update();           // Playerの実行関数

	//ゲームループ
	while (true)
	{
		if (ProcessMessage() != 0)
		{
			break;
		}

		//画面クリア
		ClearDrawScreen();

		player.Draw();          // Playerの描画関数

		//clsDx();

		//画面更新
		ScreenFlip();

	}

	SetDrawScreen(DX_SCREEN_BACK);

	DxLib_End();    // ＤＸライブラリ使用の終了処理

	return 0;    // ソフトの終了 
}