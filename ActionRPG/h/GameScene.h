#ifndef GameScene_h_
#define GameScene_h_

#include"DxLib.h"
#include"Player.h"

class GameScene
{
public:
	GameScene();
	~GameScene() {}

public:
	void InitGameScene();
	void RunGameScene();
	void FinishGameScene();

public:
	void GameSceneUpdate();

private:
	bool Push;
	Player player;
};

#endif