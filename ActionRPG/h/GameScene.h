#ifndef GameScene_h_
#define GameScene_h_

#include"Player.h"
#include"Camera.h"
#include"Map.h"

class GameScene
{
public:
	void InitGameScene();
	void RunGameScene();
	void FinishGameScene();

public:
	void GameSceneUpdate();

private:
	int SoundHandle;
	bool   Push;
	Player player;
	Camera camera;
	Map    map;
};

#endif