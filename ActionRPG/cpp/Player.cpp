#include<Math.h>
#include "../h/Player.h"
#include"../h/Calculation.h"
#include"../h/OnCollision.h"

void Player::Init()
{
	m_Pos={ 0.f };
	m_HitCounter = 0;
	IsAlive = true;

#pragma region モデル・テクスチャ読み込み
	
	m_GrHandle = LoadGraph("Tex/Player/RuneKnight_M_Ekard.tga");
	m_SwordGrHandle = LoadGraph("Tex/Player/Sword_12.tga");
	
	m_ModelHandle = MV1LoadModel("Tex/Player/Ekard.mv1");
	m_SwordHandle = MV1LoadModel("Tex/Player/Sword_12.mv1");
	//モデルのスケール変更
	Scale = { 0.15f,0.15f,0.15f };
	MV1SetScale(m_ModelHandle, Scale);
	MV1SetScale(m_SwordHandle, Scale);
	
//指定マテリアルのテクスチャ番号を取得
	int texindex = MV1GetMaterialDifMapTexture(m_ModelHandle, 0);
	int tex2 = MV1GetMaterialDifMapTexture(m_SwordHandle, 0);
//モデルにテクスチャを貼る
	int hand = MV1SetTextureGraphHandle(m_ModelHandle, texindex, m_GrHandle, FALSE);
	MV1SetTextureGraphHandle(m_SwordHandle, tex2, m_SwordGrHandle, FALSE);
	int FrameNum = MV1SearchFrame(m_ModelHandle, "W_R");
		//フレーム座標取得
	MV1GetFrameLocalWorldMatrix(m_SwordHandle, FrameNum);
		//MV1SetMaterialAmbColor(m_ModelHandle, 0 ,GetColorF(0.5f, 0.5f, 0.5f, 1.f));
#pragma endregion 
	//MV1SetRotationXYZ(m_ModelHandle, );
	
#pragma region アニメーション用文字列
	const char* anim_names[] =
	{
		"Tex/Player/Ekard_BattleIdle.mv1",
		"Tex/Player/Ekard_Run.mv1",
		"Tex/Player/Anim_Attack1.mv1",
		"Tex/Ct/catdamage.mv1",
		"Tex/Ct/catdied.mv1"
	};
	
	//文字列の先頭を選べる
	Anim.InitAnimation(m_ModelHandle, anim_names);
#pragma endregion
	
//playerのモデルハンドル,フレーム番号,XYZの空間分割
	MV1SetupCollInfo(m_ModelHandle, -1, 1, 1, 1);
}

void Player::Update()
{
	m_PlayTime++;
	Move();
	Rotate();
	Attack();


//現在の再生時間が総再生時間を超えたら再生時間を0に戻す
	if (m_PlayTime >= Anim.m_AnimTotalTime[Anim.ANIM_LIST::ANIM_RUN]|| m_PlayTime >= Anim.m_AnimTotalTime[Anim.ANIM_LIST::ANIM_WAIT])
	{
		m_PlayTime = 0.f;
	}

	//当たり判定を更新
	MV1RefreshCollInfo(m_ModelHandle, -1);
}

//プレイヤー描画
void Player::Draw()
{	
	if (IsAlive)
	{
		MV1DrawModel(m_ModelHandle);
		MV1DrawModel(m_SwordHandle);
#ifdef _DEBUG
		DrawLine3D(m_Pos, m_StartLine, GetColor(0, 0, 255));
		DrawLine3D(m_StartLine, m_EndLine, GetColor(0, 0, 255));
#endif
		DrawHP();
	}
}

//プレイヤーの回転
void Player::Rotate()
{
	float Angle{ 0.f };

	//特定のキーを押したときにプレイヤーを回転させる
	if      (CheckHitKey(KEY_INPUT_D))  Angle += m_RotateSpeed;
	else if (CheckHitKey(KEY_INPUT_A))  Angle -= m_RotateSpeed;

	//角度が０ではない場合
	if (Angle != PlayerState::None)
	{
		m_Digree_Y += Angle;
		//度数法からラジアンに変換
		float Rad = m_Digree_Y * DX_PI_F / 180.f;

		//３Dの向きベクトル算出(単位ベクトル＝１)
		m_Direction.x = sinf(Rad);
		m_Direction.z = cosf(Rad);
		m_OldMoveVec.x = m_Direction.x * (m_RotateSpeed * 1.f / 60.f);
		m_OldMoveVec.z = m_Direction.z * (m_RotateSpeed * 1.f / 60.f);

		//モデルの回転
		MV1SetRotationXYZ(m_ModelHandle, VGet(0.f, Rad, 0.f));
	}
}

void Player::Move()
{
//毎フレーム0で初期化する
	VECTOR MoveVec{ 0.f };

#pragma region 移動処理 
//特定のキーを押したときに移動
	if (CheckHitKey(KEY_INPUT_W))
	{ 
		//60で割ることで60フレームで進むベクトルを出している
		MoveVec.x -= m_Direction.x * (m_Speed * 1.f / 60.f);
	    MoveVec.z -= m_Direction.z * (m_Speed * 1.f / 60.f);
	}
	else if (CheckHitKey(KEY_INPUT_S)) 
	{
		MoveVec.x += m_Direction.x * (m_Speed * 1.f / 60.f);
		MoveVec.z += m_Direction.z * (m_Speed * 1.f / 60.f);
	}

#pragma endregion
	if (MoveVec.x != PlayerState::None && MoveVec.z != PlayerState::None)
	{
		MoveVec = Slerp(m_OldMoveVec, MoveVec, 0.2f);
	}
	
	//過去の移動ベクトル保存
	m_OldMoveVec = MoveVec;

	//移動したのかを調べて移動していたならアニメーションする
	if (VSize(MoveVec) >= 0.1f)
	{
		//atan2を使うことで現在の向いている方向から180振り向く
		float Rad = (float)atan2f(-MoveVec.x, -MoveVec.z);

		MV1SetRotationXYZ(m_ModelHandle, VGet(0.f, Rad, 0.f));
		m_Digree_Y = Rad * 180.f / DX_PI_F;
		//走るアニメーション
		Anim.SetAnimation(m_ModelHandle, Anim.ANIM_LIST::ANIM_RUN, m_PlayTime);

		VECTOR CenterPos = m_Pos;
		CenterPos.y += 6.f;
		//当たったところを終点にする
		VECTOR HitPos{ 0.f };
		if (m_MapRef->CollisionToModel(CenterPos, VAdd(CenterPos, MoveVec), &HitPos))	return;

		//初期始点値からどれくらいずらすのか
		VECTOR vertical{ 0.f,4.f,0.f };
		//始点は現在のポジションと移動量を保存している変数を足している
		m_StartLine = VAdd(m_Pos, MoveVec);
		m_StartLine.y += vertical.y;
		//初期始点値からどれくらい下にレイを出すのか
		VECTOR DownLine{ 0.f,-16.f,0.f };
		m_EndLine = VAdd(m_StartLine, DownLine);
		//出したレイのマップとのあたり判定
		if (m_MapRef->CollisionToModel(m_StartLine, m_EndLine, &HitPos))
		{
			m_Pos = HitPos;
		}

		// 画面に移るモデルの移動
		MV1SetPosition(m_ModelHandle, m_Pos);
		MV1SetMatrix(m_SwordHandle, MMult(MGetScale(Scale), MGetTranslate(m_SwordPos)));
	}
	else 
	{
		//待機モーション
		Anim.SetAnimation(m_ModelHandle, Anim.ANIM_LIST::ANIM_WAIT, m_PlayTime);
	}
}

void Player::DrawHP()
{
	const int HPX = 75;
	const int HPY = 65;
	int color = GetColor(0, 255, 0);
	DrawBox(HPX, HPY, 920, 140, GetColor(255,0,0), TRUE);
	//HPゲージ描画
	if      (m_HitCounter == 0)  m_Hp = DrawBox(HPX, HPY, 920, 140, color, TRUE);
	else if (m_HitCounter == 1)  m_Hp = DrawBox(HPX, HPY, 709, 140,color, TRUE); 
	else if (m_HitCounter == 2)  m_Hp = DrawBox(HPX, HPY, 498, 140,color, TRUE); 
	else if (m_HitCounter == 3)  m_Hp = DrawBox(HPX, HPY, 287, 140,color, TRUE);
	else
	{
		m_Hp = DrawBox(HPX, HPY, 75, 140, color, TRUE);
		Anim.SetAnimation(m_ModelHandle, Anim.ANIM_LIST::ANIM_DIED, m_PlayTime);
		if (m_PlayTime >= Anim.m_AnimAttachIndex[Anim.ANIM_LIST::ANIM_DIED])  Release();
		IsAlive = false;
		//m_HitCounter = 0;
	}
	//HPゲージ読み込み描画
	LoadGraphScreen(0, 0, "Tex/HPGauge.png", TRUE);
}

void Player::Release()
{
	//3Dモデルの削除
	MV1DeleteModel(m_ModelHandle);
		//テクスチャの削除
		DeleteGraph(m_GrHandle);
}

void Player::Attack()
{
	if ((GetMouseInput() & MOUSE_INPUT_LEFT) != PlayerState::None)
	{
		//攻撃アニメーション
		Anim.SetAnimation(m_ModelHandle, Anim.ANIM_LIST::ANIM_ATTACK, m_PlayTime);
		OnColl::Inatance()->OnCollitionSphereToCap(this, &Enemy);
	}
}

//この関数はダメージを与えてきた敵にこの関数を呼び出す
void Player::Damage()
{
	m_HitCounter ++;
	Anim.SetAnimation(m_ModelHandle, Anim.ANIM_LIST::ANIM_DAMAGE, m_PlayTime);
}