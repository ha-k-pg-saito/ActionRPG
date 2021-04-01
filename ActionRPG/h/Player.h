#ifndef Player_h_
#define Player_h_
#include"Base.h"

class Player:public Base
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
	Player() {}
};


#endif // !Player_h_



