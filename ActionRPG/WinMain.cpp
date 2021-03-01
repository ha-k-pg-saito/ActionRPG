#include"DxLib.h"

// プログラムは WinMain から始まります
int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_  HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nCmdShow)
{
	int ModelHandle;

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

	SetDrawScreen(DX_SCREEN_BACK);

	ModelHandle = MV1LoadModel("image/unitychan.mv1");

	//ゲームループ
	while (true)
	{
		if (ProcessMessage() != 0)
		{
			break;
		}

		MV1SetPosition(ModelHandle, VGet(320.0f, -300.0f, 600.0f));

		//画面クリア
		ClearDrawScreen();
		clsDx();

		//画面更新
		ScreenFlip();

	}

	// ３Ｄモデルの描画
	MV1DrawModel(ModelHandle);

	// モデルハンドルの削除
	MV1DeleteModel(ModelHandle);

	DxLib_End();    // ＤＸライブラリ使用の終了処理

	return 0;    // ソフトの終了 
}