#ifndef Camera_h_
#define Camera_h_
#include"DxLib.h"

class Camera 
{
public:
	Camera();
	~Camera();

	void Update();

private:
	VECTOR  m_Pos;
	float	m_Radius;
	float	m_Angle;
	float	m_Length;
};


#endif