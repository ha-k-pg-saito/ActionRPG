#include"../h/Camera.h"

#include<math.h>

Camera::Camera()
{
    //m_Pos = VGet(0.f, 9.f, 0.f);		//VGetによってm_Posにx,y,zの値代入
    //m_Radius = 0.f;                     //半径
    //m_Angle = 0.f;                      //角度
    //m_Length = 20.f;                   //半径の長さ

    m_AngleH = 180.f;			// 水平角度
    m_AngleV = 0.0f;			// 垂直角度
    m_Speed  = 0.1f;            // 移動速度
    m_Pos    = VGet(0.f, 0.f, 0.f);// カメラ座標
    m_Target = VGet(0.f, 0.f, 0.f);// 注視点座標
}

Camera::~Camera()
{
}

void Camera::Update(Player* player)
{
    //サンプル
    //マウスポインタ情報の使用
    int X, Y;
    GetMousePoint(&X, &Y);
    DrawCircle(X, Y, 5.f, GetColor(0, 255, 0), TRUE);
    //視覚情報の補填のオブジェクト
    DrawSphere3D(VGet(20.0f, 0.0f, 0.0f), 8.0f, 32, GetColor(255, 0, 0), GetColor(255, 255, 255), TRUE);
    
    //カメラの上下左右移動
    //if (CheckHitKey(KEY_INPUT_UP) == 1)
    if (CheckHitKey(KEY_INPUT_T) == 1)
    {
        m_AngleV += m_Speed;
        // ある一定角度以上にはならないようにする
        if (m_AngleV > DX_PI_F / 2.0f - 1.0f)
        {
            m_AngleV = DX_PI_F / 2.0f - 1.0f;
        }
    }
    //if (CheckHitKey(KEY_INPUT_DOWN) == 1)
    if (CheckHitKey(KEY_INPUT_G) == 1)
    {
        m_AngleV -= m_Speed;
        // ある一定角度以下にはならないようにする
        if (m_AngleV < -DX_PI_F / 2.0f + 1.0f)
        {
            m_AngleV = -DX_PI_F / 2.0f + 1.0f;
        }
    }
    //if (CheckHitKey(KEY_INPUT_LEFT) == 1)
    if (CheckHitKey(KEY_INPUT_F) == 1)
    {
        m_AngleH += m_Speed;
    }
    //if (CheckHitKey(KEY_INPUT_RIGHT) == 1)
    if (CheckHitKey(KEY_INPUT_H) == 1)
    {
        m_AngleH -= m_Speed;
    }

    //注視点の設定
    m_Target = VAdd(player->GetPos(), VGet(0.f, 10.f, 0.f));

    MATRIX RotZ, RotY;
    float Camera_Player_Length;
    MV1_COLL_RESULT_POLY_DIM HRes;
    int HitNum;

    // 水平方向の回転はＹ軸回転
    RotY = MGetRotY(m_AngleH);

    // 垂直方向の回転はＺ軸回転 )
    RotZ = MGetRotZ(m_AngleV);

    // カメラからプレイヤーまでの初期距離をセット
    Camera_Player_Length = 30.f;

    // カメラの座標を算出
    // Ｘ軸にカメラとプレイヤーとの距離分だけ伸びたベクトルを
    // 垂直方向回転( Ｚ軸回転 )させたあと水平方向回転( Ｙ軸回転 )して更に
    // 注視点の座標を足したものがカメラの座標
    m_Pos = VAdd(VTransform(VTransform(VGet(-Camera_Player_Length, 0.0f, 0.0f), RotZ), RotY), m_Target);



    SetCameraNearFar(1.f, 1500.f);			//カメラの手前と奥クリップの距離
    SetCameraPositionAndTarget_UpVecY(
        m_Pos,
        m_Target);				//注視点はPlayer
}
