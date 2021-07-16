#ifndef GameScene_h_
#define GameScene_h_

#include"Player.h"
#include"Camera.h"
#include"Map.h"
#include"../h/EnemyManager.h"
#include"../h/OnCollision.h"
#include"../h/MiniMap.h"
#include"../h/Shape.h"

class GameScene
{
public:
	GameScene() :
		m_SoundHandle{ 0 },
		IsAlive{ true },
		m_Player(&m_Map)
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
	Map          m_Map;
	Player       m_Player;
	Camera       m_Camera;
	EnemyManager m_EnemyMng;
	MiniMap      m_MiniMap;
};
#endif