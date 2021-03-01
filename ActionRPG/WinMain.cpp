<<<<<<< HEAD
#include"DxLib.h"
#include"h/Camera.h"
=======
#include "DxLib.h"
#include "h/Player.h"
>>>>>>> cd424402c48c74a7e30de5e110a747f3ccfdff7d

// プログラムは WinMain から始まります
int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_  HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nCmdShow)
{
	
	Player player;

	//ウインドウモードに変更
	SetOutApplicationLogValidFlag(FALSE);
<<<<<<< HEAD
	ChangeWindowMode(TRUE);					//ウィンドウモード
	SetGraphMode(640, 480, 32);				//画面モード変更
	SetBackgroundColor(0, 0, 0);			//背景色
	SetFontSize(75);						//フォントサイズ
=======
	ChangeWindowMode(TRUE);				//ウィンドウモード
	SetGraphMode(640, 480, 32);		//画面モード変更
	SetBackgroundColor(0, 0, 0);	//背景色
	SetFontSize(75);					//フォントサイズ
	SetCameraNearFar(1.f,150.f);
>>>>>>> cd424402c48c74a7e30de5e110a747f3ccfdff7d

	if (DxLib_Init() == -1)					//ＤＸライブラリ初期化処理
	{
		return -1;							//エラーが起きたら直ちに終了
	}

<<<<<<< HEAD
	SetDrawScreen(DX_SCREEN_BACK);			//裏面に描画
=======
	player.Update();
>>>>>>> cd424402c48c74a7e30de5e110a747f3ccfdff7d

	//ゲームループ
	while (true)
	{
		if (ProcessMessage() != 0)
		{
			break;
		}

<<<<<<< HEAD
		ClearDrawScreen();					//描画されたもの削除
		clsDx();							//文字描画
=======
		//画面クリア
		ClearDrawScreen();

		player.Draw();

		//clsDx();
>>>>>>> cd424402c48c74a7e30de5e110a747f3ccfdff7d

		
		ScreenFlip();						//画面更新

	}

<<<<<<< HEAD
	DxLib_End();							 // ＤＸライブラリ使用の終了処理
=======
	SetDrawScreen(DX_SCREEN_BACK);

	DxLib_End();    // ＤＸライブラリ使用の終了処理
>>>>>>> cd424402c48c74a7e30de5e110a747f3ccfdff7d

	return 0;								 // ソフトの終了 
}