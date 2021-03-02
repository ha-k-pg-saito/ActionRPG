#include "DxLib.h"
#include "h/Player.h"

// プログラムは WinMain から始まります
int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_  HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nCmdShow)
{
	Player player;  // PlayerClassのローカル変数
	//int m_Player = 0;
	 
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
	// モデルハンドルの削除
	//MV1DeleteModel(m_Player);

	player.Update();
	// モデルの読み込み
	//m_Player = MV1LoadModel("Tex/unitychan.mv1");

	// 画面に移るモデルの移動
	//MV1SetPosition(m_Player, VGet(320.0f, -300.0f, 600.0f));

	//ゲームループ
	while (true)
	{
		if (ProcessMessage() != 0)
		{
			break;
		}

		ClearDrawScreen();					//描画されたもの削除
		clsDx();							//文字削除
		// 3Dモデルの描画
		//MV1DrawModel(m_Player);

		player.Draw();
		
		ScreenFlip();						//画面更新


		//clsDx();

	}

	DxLib_End();							 // ＤＸライブラリ使用の終了処理
	SetDrawScreen(DX_SCREEN_BACK);

	return 0;								 // ソフトの終了 
}