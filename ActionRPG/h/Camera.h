#ifndef Camera_h_
#define Camera_h_

#include"Base.h"

class Camera :public Base
{
public:
	Camera();
	~Camera() {}

	void Update();

private:
	float	m_Radius;
	float	m_Angle;
	float	m_Length;

};


#endif