#include<Math.h>
#include "../h/Player.h"
#include"DxLib.h"

void Player::Init(int modelhandle,int grhandle)
{
	m_ModelHandle = modelhandle;
#pragma region モデルテクスチャ読み込み
	m_GrHandle[0] = grhandle;
	m_GrHandle[1] = LoadGraph("Tex/Player/sister_hood.png");
	m_GrHandle[2] = LoadGraph("Tex/Player/sister_juel.png");
	m_GrHandle[3] = LoadGraph("Tex/Player/sister_flame.png");
	m_GrHandle[4] = LoadGraph("Tex/Player/sister_pierce.png");
	m_GrHandle[5] = LoadGraph("Tex/Player/sister_hair.png");
	m_GrHandle[6] = LoadGraph("Tex/Player/sister_ahoge.png");
	m_GrHandle[7] = LoadGraph("Tex/Player/sister_rod.png");
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
		m_PlayTime = 0.f;
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
	if (CheckHitKey(KEY_INPUT_A)) { Digree -= RotateSpeed; }
	if (CheckHitKey(KEY_INPUT_D)) { Digree += RotateSpeed; }

	if (Digree != 0.f)
	{
		m_Digree_Y += Digree;
		//度数法からラジアンに変換
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
	//このCollisionはレイとマップのあたり判定を行っている
	Collision();
	
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
	//レイの描画
	//終点は移動前の場所から移動した分のベクトルを足して出している
	m_Line = VAdd(GetPos(), Move_Vec);
	DrawLine3D(m_Pos, m_Line, GetColor(0, 0, 255));
#pragma endregion

	//移動したのかを調べて移動していたならアニメーションする
	if (Move_Vec.x != 0.f || Move_Vec.z != 0.f)
	{
		//待機状態から走るモーションに切り替える
		m_AnimHandle[ANIM_LIST::ANIM_RUN] = MV1LoadModel("Tex/catwalk.mv1");
		//指定したモデルにアニメーションをアタッチする
		//アタッチー＞付着させるetc...
		m_AnimAttachIndex[ANIM_LIST::ANIM_RUN] = MV1AttachAnim(m_ModelHandle, 0, m_AnimHandle[ANIM_LIST::ANIM_RUN], TRUE);
		//アタッチしたアニメーションの総時間を取得する
		m_AnimTotalTime[ANIM_LIST::ANIM_RUN] = MV1GetAttachAnimTotalTime(m_ModelHandle, m_AnimAttachIndex[ANIM_LIST::ANIM_RUN]);
		//本来のポジション変数に一時的に保存していた値を加算する
		m_Pos.x += Move_Vec.x;
		m_Pos.z += Move_Vec.z;
	}
	else 
	{
		//動いてなければ待機モーション
		m_PlayTime = 0.f;
		m_AnimHandle[ANIM_LIST::ANIM_NUM] = MV1LoadModel("Tex/catwait.mv1");
		m_AnimAttachIndex[ANIM_LIST::ANIM_NUM] = MV1AttachAnim(m_ModelHandle, 0, m_AnimHandle[ANIM_LIST::ANIM_NUM], TRUE);
		m_AnimTotalTime[ANIM_LIST::ANIM_NUM] = MV1GetAttachAnimTotalTime(m_ModelHandle, m_AnimAttachIndex[ANIM_LIST::ANIM_NUM]);
	}
}

void Player::DrawHP()
{
	//HPバー描画（四角形）
	DrawBox(75, 65, 920, 140, GetColor(0,255,0), TRUE);
	//HPゲージ読み込み描画
	LoadGraphScreen(0, 0, "Tex/HPGauge.png", TRUE);
}

void Player::Release()
{
	//3Dモデルの削除
	MV1DeleteModel(m_ModelHandle);
	//テクスチャの削除
	DeleteGraph(m_GrHandle[8]);
}

void Player::Collision()
{
	//モデル全体のコリジョン情報構築
	MV1SetupCollInfo(m_ModelHandle, 0, 8, 8, 8);
	//0番目のフレームのコリジョン情報を更新する
	MV1RefreshCollInfo(m_ModelHandle, 0);
	//0番フレームとレイ都のあたり判定
	HitPoly= MV1CollCheck_Line(m_ModelHandle, 0, m_Pos, m_Line);

	//当たったならその位置をレイの終点とする
	if (HitPoly.HitFlag == 1)
	{
		m_Line = HitPoly.HitPosition;
	}
	// 当たったかどうかを表示する
	DrawFormatString(1500, 100, GetColor(255, 255, 255), "HIT:%d", HitPoly.HitFlag);
}
