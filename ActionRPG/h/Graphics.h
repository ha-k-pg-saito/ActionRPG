#ifndef Graphics_h_
#define Graphics_h_

class Graphics
{
public:
	static Graphics* Instance()
	{
		static Graphics instance;

		return &instance;
	}

private:
	void InitTexture();
	void ReleaseTexture();

private:
	//インスタンス化を防ぐための処理
	Graphics() {}
};

#endif