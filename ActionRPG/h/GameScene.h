#ifndef GameScene_h_
#define GameScene_h_

#include"Player.h"
#include"Camera.h"
#include"Sound.h"
#include"Map.h"

class GameScene
{
public:
	GameScene();
	~GameScene() { Release(); }

public:
	void InitGameScene();
	void RunGameScene();
	void FinishGameScene();

public:
	void GameSceneUpdate();

private:
	void Release();

private:
	bool Push;
	Player player;
	Camera camera;
	Map    map;
};

#endif