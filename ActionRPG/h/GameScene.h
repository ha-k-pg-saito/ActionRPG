#ifndef GameScene_h_
#define GameScene_h_

#include"Player.h"
#include"Camera.h"
#include"Map.h"
#include"../h/EnemyManager.h"
#include"../h/OnCollision.h"

class GameScene
{
public:
	GameScene() :
		m_SoundHandle{ 0 },
		IsAlive{ true },
		Player(&Map)
	{}
	~GameScene() {}
	void InitGameScene();
	void RunGameScene();
	void FinishGameScene();

public:
	void GameSceneUpdate();

private:
	int          m_SoundHandle;
	bool         IsAlive;
	bool		 m_IsCollision;
	Map          Map;
	Player       Player;
	Camera       Camera;
	EnemyManager EnemyMng;
};
#endif