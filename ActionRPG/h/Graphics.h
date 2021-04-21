#ifndef Graphics_h_
#define Graphics_h_

class Graphics
{
public:
	//シングルトン
	static Graphics* Instance()
	{
		static Graphics instance;

		return &instance;
	}

private:
	void InitTexture();			
	void ReleaseTexture();		
	void Start();				//描画開始
	void End();					//描画終了

private:
	//インスタンス化を防ぐための処理
	Graphics() {}
};

#endif