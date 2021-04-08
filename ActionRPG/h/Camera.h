#ifndef Camera_h_
#define Camera_h_
#include"DxLib.h"

class Camera 
{
public:
	static Camera* Instance()
	{
		static Camera instance;
		return&instance;
	}
	void Update();

private:
	Camera();
	
	VECTOR  m_Pos;
	float	m_Radius;
	float	m_Angle;
	float	m_Length;
};


#endif