#include"../h/Camera.h"

Camera::Camera()
{
	m_Pos = VGet(340.f, 480.f, 400.f);		//VGetによってm_Posにx,y,zの値代入
	SetCameraNearFar(1.f, 150.f);			//カメラの描画距離
	SetCameraPositionAndTargetAndUpVec(
		VGet(0.f, 0.f, -800.f),				//視点はZ軸-800の位置
		VGet(0.f, 0.f, 0.f),				//注視点は原点
		VGet(0.f,0.f,0.f));					//上方向
}

void Camera::Update()
{

}

void Camera::Move()
{


}

void Camera::Draw()
{


}
