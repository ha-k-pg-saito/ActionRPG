#ifndef MiniMap_h_
#define MiniMap_h_
#include"../h/Player.h"
#include"DxLib.h"
#include"../h/Player.h"

class MiniMap
{
public: 
	MiniMap() :
		m_MiniHandle{ 0 },
		m_CircleHandle{ 0 },
		m_MapPos{ 0.f },
		m_Wide{ 0. },
		m_Height{ 0. },
		m_CirPos{ 50.f,0.f,50.f },
		m_PlayerPos{ 0.f }
	{}
	~MiniMap() {}
 
	void Init();
	void Update(Player* player);
	void Draw();


private:
#define CIRCLE_RAD 10    //円の半径
#define INIT_TEX_POS 0   //テクスチャの左上座標
#define TEX_WIDE   1700.  //テクスチャの横幅
#define TEX_HEIGHT 2480.  //テクスチャの縦幅
#define TEXUV_SIZE 300   //テクスチャUVのサイズ
#define MAP_WIDE   997.357951 //マップの横幅
#define MAP_HEIGHT 1001.126301 //マップの縦幅

	int m_MiniHandle;
	int m_CircleHandle;
	double m_Wide;
	double m_Height;
	VECTOR m_MapPos;
	VECTOR m_CirPos;
	VECTOR m_PlayerPos;
};

#endif