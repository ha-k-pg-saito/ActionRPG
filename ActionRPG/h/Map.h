#ifndef Map_h_
#define Map_h_

#include"DxLib.h"

class Map
{
public:
	Map() :
		m_MapHandle(0),
		m_Pos{0,0.9,0}
	{}
	~Map() {}

public:
	void Init(int maphandle,int grhandle,int lastmaphandle,int lastmapgrhandle);
	void Draw();

private:
	//マップモデル保存用変数
	int    m_MapHandle;
	//マップに貼るテクスチャ保存変数
	int    m_GrHandle[7];
	//ボスステージのモデル保存変数
	int    m_LastMHandle;
	//ボスステージのテクスチャ保存変数
	int    m_LastMGrHandle[4];
	VECTOR m_Pos;
};

#endif