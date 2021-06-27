#include"../h/Enemy.h"
#include<Math.h>

void Enemy::Init()
{
	
	const char* anim_names[] =
	{
		"Tex/Cat/catwait.mv1",
		"Tex/Cat/catwalk.mv1",
		"Tex/Cat/catattack.mv1",
		"Tex/Cat/catdamage.mv1",
		"Tex/Cat/catdied.mv1"
	};
	m_Enemy_ModelHandle = MV1LoadModel("Tex/Cat/catoriginal.mv1");
	m_GrHandle = LoadGraph("Tex/Cat/uvtexture.png");
	int texindex = MV1GetMaterialDifMapTexture(m_Enemy_ModelHandle, 0);
	int hand = MV1SetTextureGraphHandle(m_Enemy_ModelHandle, texindex, m_GrHandle, FALSE);
	Anim.InitAnimation(m_Enemy_ModelHandle, anim_names);
	m_Enemy_MoveFlag = FALSE;

	// ３Ｄモデルの座標を初期化
	m_Rand_Pos.x = rand() % 1000 - 100;
	m_Rand_Pos.z = rand() % 1000 - 100;
	m_Rand_Pos.y = 0.0f;
	m_Enemy_Position = VGet(m_Rand_Pos.x, m_Rand_Pos.y, m_Rand_Pos.z);
	m_Enemy_InitialPosition = VGet(m_Rand_Pos.x, m_Rand_Pos.y, m_Rand_Pos.z);

	m_Hp = 3;
	IsActive = true;
	MV1SetupCollInfo(m_Enemy_ModelHandle, -1, 1, 1, 1);
}

void Enemy::Update(VECTOR player_pos)
{
	// ３ＤモデルEnemyから３ＤモデルPlayerに向かうベクトルを算出
	m_Vector = VSub(player_pos, m_Enemy_Position);
	// ３ＤモデルEnemyから初期地点へのベクトルを算出
	m_Initial_EnemyVector = VSub(m_Enemy_InitialPosition, m_Enemy_Position);

	// atan2 を使用して角度を取得
	m_Enemy_Angle = atan2f(m_Vector.x, m_Vector.z);
	m_Initial_EnemyAngle = atan2f(m_Initial_EnemyVector.x, m_Initial_EnemyVector.z);

	// PlayerとEnemyの距離
	m_Distance_Pos.x = player_pos.x - m_Enemy_Position.x;
	m_Distance_Pos.z = player_pos.z - m_Enemy_Position.z;
	// Enemyの初期位置とEnemyの距離
	m_SetEnemy_Pos.x = m_Enemy_InitialPosition.x - m_Enemy_Position.x;
	m_SetEnemy_Pos.z = m_Enemy_InitialPosition.z - m_Enemy_Position.z;

	if (m_Distance_Pos.x < 0)
	{
		// Playerとの方向の+-を修正
		m_Enemy_direction_x = -1;
		// Playerとの距離の-を+に変更
		m_Distance_Pos.x *= -1;
	}
	else
	{
		m_Enemy_direction_x = 1;
	}
	if (m_Distance_Pos.z < 0)
	{
		m_Enemy_direction_z = -1;
		m_Distance_Pos.z *= -1;
	}
	else
	{
		m_Enemy_direction_z = 1;
	}

	if (m_SetEnemy_Pos.x < 0)
	{
		// 初期位置との方向の+-を修正
		m_Setenemy_direction_x = -1;
		// 初期位置との距離、-を+に変更
		m_SetEnemy_Pos.x *= -1;
	}
	else
	{
		m_Setenemy_direction_x = 1;
	}
	if (m_SetEnemy_Pos.z < 0)
	{
		m_Setenemy_direction_z = -1;
		m_SetEnemy_Pos.z *= -1;
	}
	else
	{
		m_Setenemy_direction_z = 1;
	}

	m_Enemy_MoveFlag = FALSE;

	// 一定距離になるとPlayerの方に向く
	if (m_Distance_Pos.x <= 50.0f && m_Distance_Pos.z <= 50.0f)
	{
		// atan2 で取得した角度に３Ｄモデルを正面に向かせるための補正値( DX_PI_F )を
		// 足した値を３Ｄモデルの Y軸回転値として設定
		MV1SetRotationXYZ(m_Enemy_ModelHandle, VGet(0.0f, m_Enemy_Angle + DX_PI_F, 0.0f));

		// 一定距離になるとPlayerの方に移動
		if (m_Distance_Pos.x <= 50.0f && m_Distance_Pos.z <= 50.0f)
		{
			if (m_Distance_Pos.x >= 4.2f) {
				m_Enemy_Position.x += m_Enemy_direction_x * (m_Speed * 1.f / 60.f);
				m_Enemy_MoveFlag = TRUE;
			}
			if (m_Distance_Pos.z >= 4.2f) {
				m_Enemy_Position.z += m_Enemy_direction_z * (m_Speed * 1.f / 60.f);
				m_Enemy_MoveFlag = TRUE;
			}
		}
	}
	else // 探知範囲外になると初期位置に戻る
	{
		MV1SetRotationXYZ(m_Enemy_ModelHandle, VGet(0.0f, m_Initial_EnemyAngle + DX_PI_F, 0.0f));

		if (m_SetEnemy_Pos.x >= 0.1f) {
			m_Enemy_Position.x += m_Setenemy_direction_x * (m_Speed * 1.f / 60.f);
			m_Enemy_MoveFlag = TRUE;
		}
		if (m_SetEnemy_Pos.z >= 0.1f) {
			m_Enemy_Position.z += m_Setenemy_direction_z * (m_Speed * 1.f / 60.f);
			m_Enemy_MoveFlag = TRUE;
		}
	}

	if (m_Enemy_MoveFlag)
	{
		VECTOR CenterPos = m_Enemy_Position;
		CenterPos.y += 6;
		//当たったところを終点にする
		VECTOR HitPos = { 0 };
		if (m_MapRef.CollisionToModel(CenterPos, VAdd(CenterPos, m_Enemy_Position), &HitPos))
		{
			return;
		}

		//初期始点値からどれくらいずらすのか
		VECTOR vertical{ 0,6,0 };
		//始点は現在のポジションと移動量を保存している変数を足している
		m_StartLine = VAdd(m_Pos, m_Enemy_Position);
		m_StartLine.y += vertical.y;
		//初期始点値からどれくらい下にレイを出すのか
		VECTOR DownLine{ 0,-20,0 };
		m_EndLine = VAdd(m_StartLine, DownLine);
		//出したレイのマップとのあたり判定
		if (m_MapRef.CollisionToModel(m_StartLine, m_EndLine, &HitPos))
		{
			m_Pos = HitPos;
		}
		DrawLine3D(m_Pos, m_StartLine, GetColor(0, 0, 255));
		DrawLine3D(m_StartLine, m_EndLine, GetColor(0, 0, 255));
	}


	MV1SetPosition(m_Enemy_ModelHandle, m_Enemy_Position);
	MV1RefreshCollInfo(m_Enemy_ModelHandle, -1);
}

void Enemy::Draw()
{
	//画面内に座標が入っているかどうか
	//入っているー＞描画　入っていないー＞描画しない
	if (CheckCameraViewClip(m_Enemy_Position) == FALSE)
	{
		// 新しいアニメーションをアタッチ
		if (m_Enemy_MoveFlag)
		{
			// 移動
			Anim.SetAnimation(m_Enemy_ModelHandle, ANIM_LIST::ANIM_RUN);
		}
		else
		{
			Anim.SetAnimation(m_Enemy_ModelHandle, ANIM_LIST::ANIM_IDLE);
		}

		MV1DrawModel(m_Enemy_ModelHandle);
	}
}


void Enemy::DrawHp()
{
}

void Enemy::Damage()
{
	m_Hp--;
	Anim.SetAnimation(m_Enemy_ModelHandle, ANIM_LIST::ANIM_DAMAGE);
}
