#ifndef Camera_h_
#define Camera_h_
#include"DxLib.h"
#include"../h/Player.h"
class Camera 
{
public:
	Camera();
	~Camera();

	void Update(Player* player);

private:
	//VECTOR  m_Pos;
	//float	m_Radius;
	//float	m_Angle;
	//float	m_Length;

	float	m_AngleH;			// 水平角度
	float	m_AngleV;			// 垂直角度
	float   m_Speed;			// 移動速度
	VECTOR	m_Pos;				// カメラ座標
	VECTOR	m_Target;			// 注視点座標
};


#endif