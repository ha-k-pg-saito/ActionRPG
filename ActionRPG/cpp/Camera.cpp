#include"../h/Camera.h"

#include<math.h>

Camera::Camera()
{
    m_MouseX = 960;                 // マウスのX座標
    m_MouseY = 540;                 // マウスのY座標
    m_BeforeMouseX = 960;           // 1フレーム前のマウスのX座標
    m_BeforeMouseY = 540;           // 1フレーム前のマウスのY座標
    m_FrameCounter = 0;             // フレームカウンター
    m_AngleH = 180.f;			    // 水平角度
    m_AngleV = 0.0f;			    // 垂直角度
    m_Speed  = 0.1f;                // 移動速度
    m_Pos    = VGet(0.f, 0.f, 0.f); // カメラ座標
    m_Target = VGet(0.f, 0.f, 0.f); // 注視点座標
}

Camera::~Camera()
{
}

void Camera::Update(Player* player)
{   
    //マウスカーソルを見えなくする
    SetMouseDispFlag(FALSE);

    //GetMousePoint((int*)&m_Mouse.m_BeforeMouseX, (int*)&m_Mouse.m_BeforeMouseY);
    GetMousePoint(&m_MouseX, &m_MouseY);

    if (m_FrameCounter % 30 == 0)
    {
        //マウスカーソルを中心に移動
        SetMousePoint(960, 540);
        m_MouseX = 960;
        m_MouseY = 540;
        m_BeforeMouseX = 960;
        m_BeforeMouseY = 540;
    }

    m_FrameCounter++;
 
    //カメラ座標の更新
    m_AngleV -= (m_MouseY - m_BeforeMouseY) / 100.f;
    m_AngleH += (m_MouseX - m_BeforeMouseX) / 100.f;

    //マウス座標の保存
    m_BeforeMouseX = m_MouseX;
    m_BeforeMouseY = m_MouseY;

    // ある一定角度以上にはならないようにする
    if (m_AngleV > DX_PI_F / 2.0f - 1.0f)
    {
        m_AngleV = DX_PI_F / 2.0f - 1.0f;
    }
    // ある一定角度以下にはならないようにする
    if (m_AngleV < -DX_PI_F / 2.0f + 1.0f)
    {
        m_AngleV = -DX_PI_F / 2.0f + 1.0f;
    }

    //注視点の設定
    m_Target = VAdd(player->GetPos(), VGet(0.f, 10.f, 0.f));

    MATRIX RotZ, RotY;
    float Camera_Plam_BeforeMouseYer_Length;
    MV1_COLL_RESULT_POLY_DIM HRes;
    int HitNum;

    // 水平方向の回転はＹ軸回転
    RotY = MGetRotY(m_AngleH);

    // 垂直方向の回転はＺ軸回転 )
    RotZ = MGetRotZ(m_AngleV);

    // カメラからプレイヤーまでの初期距離をセット
    Camera_Plam_BeforeMouseYer_Length = 30.f;

    // カメラの座標を算出
    m_Pos = VAdd(VTransform(VTransform(VGet(-Camera_Plam_BeforeMouseYer_Length, 0.0f, 0.0f), RotZ), RotY), m_Target);

    //カメラの手前と奥クリップの距離
    SetCameraNearFar(1.f, 1500.f);	

    //カメラの座標更新
    SetCameraPositionAndTarget_UpVecY(
        m_Pos,
        m_Target);				//注視点はPlam_BeforeMouseYer
}
