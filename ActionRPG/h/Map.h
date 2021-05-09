#ifndef Map_h_
#define Map_h_

#include"DxLib.h"

class Map
{
public:
	Map() :
		m_MapHandle(0),
		m_Pos{0}
	{}
	~Map() {}

public:
	void Init(int maphandle,int grhandle);
	void Draw();
	int GetModel(){ return m_MapHandle; }

private:
	int    m_MapHandle;
	int    m_GrHandle[7];
	VECTOR m_Pos;
};

#endif