#ifndef Player_h
#define Player_H

class Player
{
public:
	
	Player();
	~Player();

	void Update();
	void Draw();

private:
	// モデルを保存する変数
	int m_Player;

};


#endif // !Player_h



