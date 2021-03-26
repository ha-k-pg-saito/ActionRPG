#ifndef Camera_h_
#define Camera_h_

#include"Base.h"

class Camera :public Base
{
public:
	static Camera* Instance()
	{
		static Camera instance;
		return&instance;
	}
	void Update();

private:
	
	float	m_Radius;
	float	m_Angle;
	float	m_Length;
	Camera();
};


#endif