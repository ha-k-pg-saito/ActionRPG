#ifndef Map_h_
#define Map_h_

#include"DxLib.h"

class Map
{
public:
	Map() :
		m_Pos{0}
	{}
	~Map() {}

public:
	void Init();
	void Draw();

private:
	int    m_MapHandle;
	VECTOR m_Pos;
};

#endif