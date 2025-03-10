#include "DxLib.h"
#include"h/Scene.h"

// プログラムは WinMain から始まります
int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_  HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nCmdShow)
{ 
	//ウインドウモードに変更
	SetOutApplicationLogValidFlag(FALSE);
	ChangeWindowMode(TRUE);					//ウィンドウモード
	SetGraphMode(1920, 1080, 32);			//画面モード変更
	SetBackgroundColor(120, 120, 120);		//背景色
	SetFontSize(40);						//フォントサイズ
	SetUseLighting(TRUE);	                //ライト
	SetUsePremulAlphaConvertLoad(FALSE);	//乗算済みα画像に変換するかどうか
	SetUseTransColor(FALSE);				//透明色を使用するかどうか

	if (DxLib_Init() == -1)					//ＤＸライブラリ初期化処理
	{
		return -1;							//エラーが起きたら直ちに終了
	}

	SetDrawScreen(DX_SCREEN_BACK);

	//ゲームループ
	while (true)
	{
		if (ProcessMessage() != 0)
		{
			break;
		}

		//Escapeキーでゲーム強制終了
		if (CheckHitKey(KEY_INPUT_ESCAPE))
		{
			break;
		}

		ClearDrawScreen();					//描画されたもの削除
		clsDx();							//文字削除
		
		SceneUpdate();

		ScreenFlip();						//画面更新
	}

	DxLib_End();							 // ＤＸライブラリ使用の終了処理

	return 0;								 // ソフトの終了 
}