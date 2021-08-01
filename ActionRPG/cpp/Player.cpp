#include<Math.h>
#include "../h/Player.h"
#include"../h/Calculation.h"
#include"../h/OnCollision.h"
#include"../h/Enemy.h"

void Player::Init()
{
	m_Pos={ 0.f,-3.f,0.f };
	m_HitCounter = 0;
	IsAlive = true;
	//カプセルの初期化
	m_Capsule.OldPos = m_Pos;
	m_Capsule.Bottom = m_Pos;
	m_Capsule.Top = VAdd(m_Pos,m_HeightCapsule);
	m_Capsule.Radius = m_RadSize;
	//AABBの初期化
	m_AABB.OldPos = m_Pos;
	m_AABB.Max = m_Capsule.Top;
	m_AABB.Min = m_Pos;
	m_AnimKind = ANIM_LIST::ANIM_IDLE;		//初期状態（待機）

#pragma region モデル・テクスチャ読み込み

//プレイヤ・剣モデルのテクスチャ読み込み
	m_GrHandle = LoadGraph("Tex/Player/knight_01.jpg");
	m_SwordGrHandle = LoadGraph("Tex/Player/sword_01.jpg");
//プレイヤ読み込み
	m_ModelHandle = MV1LoadModel("Tex/Player/knight_low.mv1");
	//モデルのスケール変更
	VECTOR Scale = { 3.f,3.f,3.f };
	MV1SetScale(m_ModelHandle, Scale);
	
	if (m_GrHandle <= -1)
	{
		//指定マテリアルのテクスチャ番号を取得
		int TexIndex = MV1GetMaterialDifMapTexture(m_ModelHandle, 0);
		int SworIindex = MV1GetMaterialDifMapTexture(m_ModelHandle, 1);
		//モデルにテクスチャを貼る
		MV1SetTextureGraphHandle(m_ModelHandle, TexIndex, m_GrHandle, FALSE);
		MV1SetTextureGraphHandle(m_ModelHandle, SworIindex, m_SwordGrHandle, FALSE);
	}
//プレイヤのマテリアルのアンビエントカラー変更
	MV1SetMaterialAmbColor(m_ModelHandle, 0, GetColorF(1.f, 1.f, 1.f, 0.f));

#pragma endregion 

	m_Anim.InitAnimation(m_ModelHandle, "idle_1");
	
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
	m_AABB.Update(m_Pos);
	m_Capsule.Update(m_Pos);

	//当たり判定を更新
	MV1RefreshCollInfo(m_ModelHandle, -1);
}

//アニメーションの切り替えを制御する関数
void Player::UpdateAnimation()
{
	InitAnim();
	m_PlayTime++;
//現在の状態を見てアニメーションを切り替える
	float CurrentFrame = m_MotionList[m_AnimKind].StartFrame;
		switch (m_AnimKind)
		{
		case ANIM_IDLE:						//待機モーション->走りモーション or攻撃モーション
			//移動量が0では無いとき
			if (m_OldMoveVec.x != PlayerState::None && m_OldMoveVec.z != PlayerState::None)
			{
				ChangeAnim(ANIM_RUN);
			}
			//左クリックされたとき
			else if ((GetMouseInput() & MOUSE_INPUT_LEFT) != PlayerState::None)
			{
				ChangeAnim(ANIM_ATTACK);
				IsPushed = true;
			}
			if (m_PlayTime >= m_MotionList[m_AnimKind].FinishFrame)
			{
				CurrentFrame = m_MotionList[m_AnimKind].StartFrame;
				m_PlayTime = CurrentFrame;
			}
			break;
		case ANIM_RUN:						//走りモーション->待機モーション or 攻撃モーション
			//移動量が0の時
			if (VSize(m_OldMoveVec) <= 0.1f)
			{
				//待機モーションへ
				ChangeAnim(ANIM_IDLE);
			}
			//左クリックされたとき
			else if ((GetMouseInput() & MOUSE_INPUT_LEFT) != PlayerState::None)
			{
				//攻撃モーションへ
				ChangeAnim(ANIM_ATTACK);
				IsPushed = true;
			}
			if (m_PlayTime >= m_MotionList[m_AnimKind].FinishFrame)
			{
				CurrentFrame = m_MotionList[m_AnimKind].StartFrame;
				m_PlayTime = CurrentFrame;
			}
			break;
		case ANIM_ATTACK:					
			if (VSize(m_OldMoveVec) >= 0.1f && IsPushed == false)
			{
				ChangeAnim(ANIM_IDLE);
			}
			else if (VSize(m_OldMoveVec) <= 0.1f && IsPushed == false)
			{
				ChangeAnim(ANIM_RUN);
			}
			if (m_PlayTime >= m_MotionList[m_AnimKind].FinishFrame)
			{
				CurrentFrame = m_MotionList[m_AnimKind].StartFrame;
				m_PlayTime = CurrentFrame;
				IsPushed = false;
			}
			break;
		default:
			break;
		}

		//状態に合わせたアニメーションをさせる
		MV1SetAttachAnimTime(m_ModelHandle, m_AnimKind, m_PlayTime);
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

		DrawFormatString(200, 200, GetColor(255, 255, 255), "移動量Xは: %d", m_OldMoveVec.x);
		DrawFormatString(200, 250, GetColor(255, 255, 255), "移動量Zは: %d", m_OldMoveVec.z);
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
		MoveVec.x += m_Direction.x * (m_Speed * 1.f / FPS);
		MoveVec.z += m_Direction.z * (m_Speed * 1.f / FPS);
	}
	else if (CheckHitKey(KEY_INPUT_S))
	{
		MoveVec.x -= m_Direction.x * (m_Speed * 1.f / FPS);
		MoveVec.z -= m_Direction.z * (m_Speed * 1.f / FPS);
	}

#pragma endregion
	if (MoveVec.x !=0.f || MoveVec.z != 0.f)
	{
		MoveVec = Slerp(m_OldMoveVec, MoveVec, 0.2f);
	}

	//過去の移動ベクトル保存
	m_OldMoveVec = MoveVec;

	//移動ベクトルが0.1以上
	if (VSize(MoveVec) >= 0.1f)
	{
		m_OldPos = m_Pos;
		//atan2を使うことで現在の向いている方向から180振り向く
		float Rad = (float)atan2f(MoveVec.x, MoveVec.z);

		MV1SetRotationXYZ(m_ModelHandle, VGet(0.f, Rad, 0.f));
		m_Digree_Y = Rad * 180.f / DX_PI_F;

		VECTOR CenterPos = m_Pos;
		CenterPos.y += 6.f;
		//当たったところを終点にする
		VECTOR HitPos{ 0.f };
		if (MapRef->CollisionToModel(CenterPos, VAdd(CenterPos, MoveVec), &HitPos))	return;

		// 移動後の座標を保存
		m_StartLine = VAdd(m_Pos, MoveVec);

		// レイの原点をもとめる (移動後の座標+高さ)
		VECTOR Vertical{ 0.f,RAY_ORIGIN,0.f };
		m_StartLine.y += Vertical.y;

		// レイの終点をもとめる (レイの原点 + 下向きベクトル)
		VECTOR DownLine{ 0.f,RAY_DOWN,0.f };
		m_EndLine = VAdd(m_StartLine, DownLine);

		// マップとの交差判定
		if (MapRef->CollisionToModel(m_StartLine, m_EndLine, &HitPos))
		{
			//あたっているところをプレイヤのポジションにする
			m_Pos = HitPos;
		}
		//プレイヤの座標からオフセット値分だけずらすため
		m_AfterPos = VAdd(m_Pos, m_OffSet);
	}
	else
	{
		m_OldMoveVec.x = 0.f;
		m_OldMoveVec.y = 0.f;
		m_OldMoveVec.z = 0.f;
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
		if (OnColl::Inatance()->OnCollisionAABB(this->GetAABB(),m_Enemy->GetAABB()));
		{
			DrawString(1700, 200, "Hit", GetColor(255, 255, 255));

			m_Enemy->Release();
		}
	}
}

//この関数はダメージを与えてきた敵にこの関数を呼び出す
void Player::Damage()
{
	m_HitCounter ++;
}

void Player::NoticeHit()
{
	m_Pos = m_OldPos;
}

//アニメーションが直接fbxに含まれているからフレーム指定して切り取る
void Player::InitAnim()
{
	//待機モーション
	m_MotionList[ANIM_LIST::ANIM_IDLE].StartFrame = 1380;
	m_MotionList[ANIM_LIST::ANIM_IDLE].FinishFrame = 1830;
	//走りモーション
	m_MotionList[ANIM_LIST::ANIM_RUN].StartFrame = 170;
	m_MotionList[ANIM_LIST::ANIM_RUN].FinishFrame = 220;
	//攻撃モーション
	m_MotionList[ANIM_LIST::ANIM_ATTACK].StartFrame = 440;
	m_MotionList[ANIM_LIST::ANIM_ATTACK].FinishFrame = 520;
	//ダメージモーション
	m_MotionList[ANIM_LIST::ANIM_DAMAGE].StartFrame = 1040;
	m_MotionList[ANIM_LIST::ANIM_DAMAGE].FinishFrame = 1080;
}

void Player::ChangeAnim(ANIM_LIST type)
{
	m_AnimKind = type;
	m_PlayTime = m_MotionList[m_AnimKind].StartFrame;
}
