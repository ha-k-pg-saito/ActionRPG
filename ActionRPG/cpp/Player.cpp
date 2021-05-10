#include<Math.h>
#include "../h/Player.h"
#include"DxLib.h"

void Player::Init(int modelhandle,int grhandle)
{
	m_ModelHandle = modelhandle;
#pragma region モデルテクスチャ読み込み
	m_GrHandle[0] = grhandle;
	m_GrHandle[1] = LoadGraph("Tex/sister_hood.png");
	m_GrHandle[2] = LoadGraph("Tex/sister_juel.png");
	m_GrHandle[3] = LoadGraph("Tex/sister_flame.png");
	m_GrHandle[4] = LoadGraph("Tex/sister_pierce.png");
	m_GrHandle[5] = LoadGraph("Tex/sister_hair.png");
	m_GrHandle[6] = LoadGraph("Tex/sister_ahoge.png");
	m_GrHandle[7] = LoadGraph("Tex/sister_rod.png");
#pragma endregion 

	for (int i=0;i<8;i++)
	{
		MV1SetTextureGraphHandle(m_ModelHandle, i, m_GrHandle[i], FALSE);
	
		MV1SetMaterialAmbColor(m_ModelHandle, i ,GetColorF(0.5f, 0.5f, 0.5f, 1.f));
	}
	//マテリアル関数でジュエルだけを発光
	MV1SetMaterialEmiColor(m_ModelHandle, 2, GetColorF(0.f, 1.f, 0.f, 1.f));
}

void Player::Update()
{
	Rotate();
	Move();
	
	m_PlayTime++;

	if (m_PlayTime>=m_AnimTotalTime[ANIM_LIST::ANIM_RUN])
	{
		m_PlayTime = 0;
	}
	MV1SetAttachAnimTime(m_ModelHandle, m_AnimAttachIndex[ANIM_LIST::ANIM_RUN], m_PlayTime);
}

//プレイヤー描画
void Player::Draw()
{
	MV1DrawModel(m_ModelHandle);
	DrawHP();
}

//プレイヤーの回転
void Player::Rotate()
{
	float Digree = 0.f;
	float RotateSpeed = 5.f;

	//特定のキーを押したときにプレイヤーを回転させる
	if (CheckHitKey(KEY_INPUT_Q)) { Digree -= RotateSpeed; }
	if (CheckHitKey(KEY_INPUT_E)) { Digree += RotateSpeed; }

	if (Digree != 0.f)
	{
		m_Digree_Y += Digree;

		float Rad = m_Digree_Y * DX_PI_F / 180.0f;

		//３Dの向きベクトル算出(単位ベクトル＝１)
		m_Direction.x = sinf(Rad);
		m_Direction.z = cosf(Rad);
		//モデルの回転
		MV1SetRotationXYZ(m_ModelHandle, VGet(0.0f, Rad, 0.0f));
	}
}

void Player::Move()
{
	Collision();
	//レイの描画
	m_Line = VAdd(GetPos(), VGet(0.f, 0.f, 5.f));
	DrawLine3D(m_Pos, m_Line,GetColor(0, 0, 255));
	// 画面に移るモデルの移動
	MV1SetPosition(m_ModelHandle, m_Pos);
	
	//一時的に移動量を保存する
	VECTOR Move_Vec{ 0.f,0.f,0.f };
	
#pragma region 移動処理 
	//向いている方向に移動
	if (CheckHitKey(KEY_INPUT_W))
	{ 
		//60で割ることで60フレームで進むベクトルを出している
		Move_Vec.x -= m_Direction.x * (m_Speed * 1 / 60);
		Move_Vec.z -= m_Direction.z * (m_Speed * 1 / 60);
	}
	if (CheckHitKey(KEY_INPUT_S)) 
	{
		Move_Vec.x += m_Direction.x * (m_Speed * 1 / 60);
		Move_Vec.z += m_Direction.z * (m_Speed * 1 / 60);
	}
	if (CheckHitKey(KEY_INPUT_A)) 
	{	
		Move_Vec.x += m_Direction.x * (m_Speed * 1 / 60);
		Move_Vec.z -= m_Direction.z * (m_Speed * 1 / 60);
	}
	if (CheckHitKey(KEY_INPUT_D))
	{
		Move_Vec.x -= m_Direction.x * (m_Speed * 1 / 60); 
		Move_Vec.z += m_Direction.z * (m_Speed * 1 / 60); 
	}
#pragma endregion

	//移動したのかを調べて移動していたならアニメーションする
	if (Move_Vec.x != 0.f || Move_Vec.z != 0.f)
	{
		//アニメーション
		m_AnimHandle[ANIM_LIST::ANIM_RUN] = MV1LoadModel("Tex/unitychan_RUN00_F.mv1");
		m_AnimAttachIndex[ANIM_LIST::ANIM_RUN] = MV1AttachAnim(m_ModelHandle, 0, m_AnimHandle[ANIM_LIST::ANIM_RUN], TRUE);
		m_AnimTotalTime[ANIM_LIST::ANIM_RUN] = MV1GetAttachAnimTotalTime(m_ModelHandle, m_AnimAttachIndex[ANIM_LIST::ANIM_RUN]);
		m_Pos.x += Move_Vec.x;
		m_Pos.z += Move_Vec.z;
	}
}

void Player::DrawHP()
{
	//HPバー描画（四角形）
	DrawBox(100, 65, 900, 140, GetColor(0,255,0), TRUE);
	//HPゲージ読み込み描画
	LoadGraphScreen(0, 0, "Tex/HPGauge.png", TRUE);
}

void Player::Release()
{
	MV1DeleteModel(m_ModelHandle);
	DeleteGraph(m_GrHandle[8]);
}

void Player::Collision()
{
	MV1SetupCollInfo(m_ModelHandle, 0, 8, 8, 8);
	MV1RefreshCollInfo(m_ModelHandle, 0);
	HitPoly= MV1CollCheck_Line(m_ModelHandle, 0, m_Pos, m_Line);

	//当たったならその位置をレイの終点とする
	if (HitPoly.HitFlag == 1)
	{
		m_Line = HitPoly.HitPosition;
	}
	// 当たったかどうかを表示する
	DrawFormatString(900, 100, GetColor(255, 255, 255), "HIT:%d", HitPoly.HitFlag);
}
