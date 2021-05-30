#ifndef GameScene_h_
#define GameScene_h_

#include"Player.h"
#include"Camera.h"
#include"Map.h"
#include"../EnemyManager.h"

class GameScene
{
public:
	GameScene() :
		SoundHandle (0),
		Push(false),
		player(&map)
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
	Map          map;
	Player       player;
	Camera       camera;
	EnemyManager EnemyMng;
};

#endif