#include<Math.h>
#include "../h/Player.h"
#include"../h/Calculation.h"
#include"../h/OnCollision.h"

void Player::Init()
{
	m_Pos={ 0.f,-3.f,0.f };
	m_HitCounter = 0;
	IsAlive = true;

#pragma region モデル・テクスチャ読み込み
//プレイヤ・剣モデルのテクスチャ読み込み
	m_GrHandle = LoadGraph("Tex/Player/RuneKnight_M_Ekard.tga");
	m_SwordGrHandle = LoadGraph("Tex/Player/Sword_12.tga");
//プレイヤ・剣モデル読み込み
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
//プレイヤのマテリアルのアンビエントカラー変更
	MV1SetMaterialAmbColor(m_ModelHandle, 0, GetColorF(1.f, 1.f, 1.f, 0.f));

#pragma endregion 

#pragma region アニメーション用文字列
	const char* anim_names[] =
	{
		"Tex/Payer/Ekard_BattleIdle.mv1",
		"Tex/Payer/Ekard_Run.mv1",
		"Tex/Ct/catattack.mv1",
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
	if (m_AnimKind != ANIM_ATTACK)
	{
		Move();
		Rotate();
	}
	Attack();
	UpdateAnimation();

	//剣を持たせるフレームを検索する
	int FrameNum = MV1SearchFrame(m_ModelHandle, "Bip001 R Hand");
	//フレーム座標の変換行列を設定する
	MATRIX Matrix = MV1GetFrameLocalWorldMatrix(m_ModelHandle, FrameNum);
	//当たり判定を更新
	MV1RefreshCollInfo(m_ModelHandle, -1);
	//モデルの座標変換用行列をセットする
	MV1SetMatrix(m_SwordHandle, Matrix);
}

//アニメーションの切り替えを制御する関数
void Player::UpdateAnimation()
{
//現在の状態を見てアニメーションを切り替える
	m_AnimKind = ANIM_IDLE;		//初期状態（待機）
	switch (m_AnimKind)
	{
	case ANIM_IDLE:						//待機モーション->走りモーション or攻撃モーション
		//移動量が0では無いとき
		if (m_OldMoveVec.x != PlayerState::None && m_OldMoveVec.z != PlayerState::None)
		{
			m_AnimKind = ANIM_RUN;	
		}
		//左クリックされたとき
		if ((GetMouseInput() & MOUSE_INPUT_LEFT) != PlayerState::None)
		{
			m_AnimKind = ANIM_ATTACK;
		}
		break;
	case ANIM_RUN:						//走りモーション->待機モーション or 攻撃モーション
		//移動量が0の時
		if (m_OldMoveVec.x == PlayerState::None && m_OldMoveVec.z == PlayerState::None)
		{
			m_AnimKind = ANIM_IDLE;		
		}
		//左クリックされたとき
		if ((GetMouseInput() & MOUSE_INPUT_LEFT) != PlayerState::None)
		{
			m_AnimKind = ANIM_ATTACK;
		}
		break;
	case ANIM_ATTACK:					//攻撃モーションー＞待機モーション or 走りモーション
		if (m_OldMoveVec.x == PlayerState::None && m_OldMoveVec.z == PlayerState::None)
		{
			m_AnimKind = ANIM_IDLE;
		}
		if (m_OldMoveVec.x != PlayerState::None && m_OldMoveVec.z != PlayerState::None)
		{
			m_AnimKind = ANIM_RUN;
		}
		break;
	default:
		break;
	}
	//状態に合わせたアニメーションをさせる
	Anim.SetAnimation(m_ModelHandle, m_AnimKind);
}

//プレイヤー描画
void Player::Draw()
{	
	if (IsAlive)
	{
#ifdef _DEBUG
		DrawLine3D(m_Pos, m_StartLine, GetColor(0, 0, 255));
		DrawLine3D(m_StartLine, m_EndLine, GetColor(0, 0, 255));
#endif
		MV1DrawModel(m_ModelHandle);
		MV1DrawModel(m_SwordHandle);
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
		m_OldMoveVec.x = m_Direction.x * (m_RotateSpeed * 1.f / FPS);
		m_OldMoveVec.z = m_Direction.z * (m_RotateSpeed * 1.f / FPS);

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
		//１フレームで動く距離を割り出している
		MoveVec.x -= m_Direction.x * (m_Speed * 1.f / FPS);
	    MoveVec.z -= m_Direction.z * (m_Speed * 1.f / FPS);
	}
	else if (CheckHitKey(KEY_INPUT_S)) 
	{
		MoveVec.x += m_Direction.x * (m_Speed * 1.f /FPS);
		MoveVec.z += m_Direction.z * (m_Speed * 1.f /FPS);
	}

#pragma endregion
	if (MoveVec.x != PlayerState::None && MoveVec.z != PlayerState::None)
	{
		MoveVec = Slerp(m_OldMoveVec, MoveVec, 0.2f);
	}
	
	//過去の移動ベクトル保存
	m_OldMoveVec = MoveVec;
	//移動ベクトルが0.1以上
	if (VSize(MoveVec) >= 0.1f)
	{
		//atan2を使うことで現在の向いている方向から180振り向く
		float Rad = (float)atan2f(-MoveVec.x, -MoveVec.z);

		MV1SetRotationXYZ(m_ModelHandle, VGet(0.f, Rad, 0.f));
		m_Digree_Y = Rad * 180.f / DX_PI_F;

		VECTOR CenterPos = m_Pos;
		CenterPos.y += 6.f;
		//当たったところを終点にする
		VECTOR HitPos{ 0.f };
		if (m_MapRef->CollisionToModel(CenterPos, VAdd(CenterPos, MoveVec), &HitPos))	return;

		// 移動後の座標を保存
		m_StartLine = VAdd(m_Pos, MoveVec);

		// レイの原点をもとめる (移動後の座標+高さ)
		VECTOR Vertical{ 0.f,RAY_ORIGIN,0.f };
		m_StartLine.y += Vertical.y;
		
		// レイの終点をもとめる (レイの原点 + 下向きベクトル)
		VECTOR DownLine{ 0.f,RAY_DOWN,0.f };
		m_EndLine = VAdd(m_StartLine, DownLine);

		// マップとの交差判定
		if (m_MapRef->CollisionToModel(m_StartLine, m_EndLine, &HitPos))
		{
			m_Pos = HitPos;
		}
	}
		// 画面に移るモデルの移動
		MV1SetPosition(m_ModelHandle, m_Pos);
}

void Player::DrawHP()
{
	const int HPX = 75;
	const int HPY = 960;
	int color = GetColor(0, 255, 0);
	DrawBox(HPX, HPY, 920, 1040, GetColor(255,0,0), TRUE);
	//HPゲージ描画
	if      (m_HitCounter == 0)  m_Hp = DrawBox(HPX, HPY, 920, 1040, color, TRUE);
	else if (m_HitCounter == 1)  m_Hp = DrawBox(HPX, HPY, 690, 1040,color, TRUE); 
	else if (m_HitCounter == 2)  m_Hp = DrawBox(HPX, HPY, 460, 1040,color, TRUE); 
	else if (m_HitCounter == 3)  m_Hp = DrawBox(HPX, HPY, 230, 1040,color, TRUE);
	else
	{
		m_Hp = DrawBox(HPX, HPY, 75, 1040, color, TRUE);
		Release();
		IsAlive = false;
	}
	//HPゲージ読み込み描画
	LoadGraphScreen(0, 900, "Tex/HPGauge.png", TRUE);
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
		OnColl::Inatance()->OnCollitionSphereToCap(this, &Enemy);
	}
}

//この関数はダメージを与えてきた敵にこの関数を呼び出す
void Player::Damage()
{
	m_HitCounter ++;
}