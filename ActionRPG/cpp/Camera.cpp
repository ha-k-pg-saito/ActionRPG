#include"../h/Camera.h"
#include<math.h>

Camera::Camera()
{
    m_Pos = VGet(0.f, 85.f, 200.f);		//VGetによってm_Posにx,y,zの値代入
    m_Radius = 0.f;                     //半径
    m_Angle = 0.f;                      //角度
    m_Length = 200.f;                   //半径の長さ
}

void Camera::Update()
{

    if (CheckHitKey(KEY_INPUT_LEFT) == 1)
    {

        m_Angle -= 8.f;
        if (m_Angle < 0.f)
        {
            m_Angle += 360.f;
        }
    }
    if (CheckHitKey(KEY_INPUT_RIGHT) == 1)
    {

        m_Angle += 8.f;
        if (m_Angle > 360.f)
        {
            m_Angle -= 360.f;
        }

    }

    m_Radius = m_Angle * 3.14 / 180.f;      //度数法をラジアンに直す

    //カメラ座標の計算
    float Add_x = cos(m_Radius) * m_Length;
    float Add_z = sin(m_Radius) * m_Length;
    m_Pos.x = 0.f + Add_x;
    m_Pos.z = 0.f + Add_z;

    SetCameraNearFar(1.f, 1500.f);			//カメラの手前と億クリップの距離
    SetCameraPositionAndTarget_UpVecY(
        m_Pos,
        VGet(0.f, 85.f, 0.f));				//注視点は原点

}
