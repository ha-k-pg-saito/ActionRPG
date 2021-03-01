#ifndef Camera_h_
#define Camera_h_

#include"Base.h"

class Camera:public Base
{
public:
	Camera();
	~Camera() {}

private:
	void Update();
	void Move();
	void Draw();

};


#endif