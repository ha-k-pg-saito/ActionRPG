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
	
	VECTOR m_Camera_Pos;
	float	m_Radius;
	float	m_Angle;
	float	m_Length;
	Camera();
};


#endif