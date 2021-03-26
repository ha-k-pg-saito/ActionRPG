#ifndef Player_h_
#define Player_h_

#include"DxLib.h"

class Player
{
	//シングルトン
public :
	static Player* Instance()
	{
		static Player instance;
		return& instance;
	}

public:
	void Update();
	void Draw();

private:
	// モデルを保存する変数
	int m_Player;
};


#endif // !Player_h_



