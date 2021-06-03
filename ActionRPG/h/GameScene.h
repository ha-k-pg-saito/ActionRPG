#ifndef GameScene_h_
#define GameScene_h_

#include"Player.h"
#include"Camera.h"
#include"Map.h"
#include"../EnemyManager.h"
#include"../h/OnCollision.h"

class GameScene
{
public:
	GameScene() :
		SoundHandle (0),
		Push(false),
		Player(&Map)
	{}
	~GameScene() {}
	void InitGameScene();
	void RunGameScene();
	void FinishGameScene();

public:
	void GameSceneUpdate();

private:
	int          SoundHandle;
	bool         Push;
	Map          Map;
	Player       Player;
	Camera       Camera;
	EnemyManager EnemyMng;
	OnColl		 oncoll;
};

#endif