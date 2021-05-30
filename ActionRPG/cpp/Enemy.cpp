#include"../h/Enemy.h"
#include"math.h"

void Enemy::Init()
{
	m_Enemy_ModelHandle = MV1LoadModel("Tex/Cat/catoriginal.mv1");
	//走りモーション	
		//m_AnimHandle[ANIM_LIST::ANIM_RUN] = MV1LoadModel("Tex/Player/sisterwalk.mv1");
		//アニメーションのデバッグ用モデル読み込み処理
	m_Enemy_AnimHandle[ANIM_LIST::ANIM_RUN] = MV1LoadModel("Tex/Cat/catwalk.mv1");
	//指定したモデルにアニメーションをアタッチする
	//アタッチー＞付着させるetc...
	m_Enemy_AnimAttachIndex[ANIM_LIST::ANIM_RUN] =
		MV1AttachAnim(m_Enemy_ModelHandle, 0, m_Enemy_AnimHandle[ANIM_LIST::ANIM_RUN], FALSE);
	//アタッチしたアニメーションの総時間を取得する
	m_Enemy_AnimTotalTime[ANIM_LIST::ANIM_RUN] =
		MV1GetAttachAnimTotalTime(m_Enemy_ModelHandle, m_Enemy_AnimAttachIndex[ANIM_LIST::ANIM_RUN]);

	//待機モーション
	m_Enemy_AnimHandle[ANIM_LIST::ANIM_WAIT] = MV1LoadModel("Tex/Cat/catwait.mv1");
	m_Enemy_AnimAttachIndex[ANIM_LIST::ANIM_WAIT] =
		MV1AttachAnim(m_Enemy_ModelHandle, 0, m_Enemy_AnimHandle[ANIM_LIST::ANIM_WAIT], FALSE);
	m_Enemy_AnimTotalTime[ANIM_LIST::ANIM_WAIT] =
		MV1GetAttachAnimTotalTime(m_Enemy_ModelHandle, m_Enemy_AnimAttachIndex[ANIM_LIST::ANIM_WAIT]);

	m_Enemy_MoveFlag = FALSE;

	// ３Ｄモデルの座標を初期化
	m_Rand_Pos.x = rand() % 1000 - 100;
	m_Rand_Pos.z = rand() % 1000 - 100;
	m_Rand_Pos.y = 0.0f;
	m_Enemy_Position = VGet(m_Rand_Pos.x, m_Rand_Pos.y, m_Rand_Pos.z);
	m_Enemy_InitialPosition = VGet(m_Rand_Pos.x, m_Rand_Pos.y, m_Rand_Pos.z);

	m_Hp = 3;
	IsActive = true;
	
}

void Enemy::Update(VECTOR player_pos)
{
	// ３ＤモデルEnemyから３ＤモデルPlayerに向かうベクトルを算出
	m_Vector = VSub(player_pos, m_Enemy_Position);
	// ３ＤモデルEnemyから初期地点へのベクトルを算出
	m_Initial_EnemyVector = VSub(m_Enemy_InitialPosition, m_Enemy_Position);

	// atan2 を使用して角度を取得
	m_Enemy_Angle = atan2(m_Vector.x, m_Vector.z);
	m_Initial_EnemyAngle = atan2(m_Initial_EnemyVector.x, m_Initial_EnemyVector.z);

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
			if (m_Distance_Pos.x >= 10.0f) {
				m_Enemy_Position.x += m_Enemy_direction_x * m_Speed;
				m_Enemy_MoveFlag = TRUE;
			}
			if (m_Distance_Pos.z >= 10.0f) {
				m_Enemy_Position.z += m_Enemy_direction_z * m_Speed;
				m_Enemy_MoveFlag = TRUE;
			}
		}
	}
	else // 探知範囲外になると初期位置に戻る
	{
		MV1SetRotationXYZ(m_Enemy_ModelHandle, VGet(0.0f, m_Initial_EnemyAngle + DX_PI_F, 0.0f));

		if (m_SetEnemy_Pos.x >= 0.1f) {
			m_Enemy_Position.x += m_Setenemy_direction_x * m_Speed;
			m_Enemy_MoveFlag = TRUE;
		}
		if (m_SetEnemy_Pos.z >= 0.1f) {
			m_Enemy_Position.z += m_Setenemy_direction_z * m_Speed;
			m_Enemy_MoveFlag = TRUE;
		}
	}

	m_PlayTime++;
	if (m_PlayTime >= m_Enemy_AnimTotalTime[ANIM_LIST::ANIM_RUN] || m_PlayTime >= m_Enemy_AnimTotalTime[ANIM_LIST::ANIM_WAIT])
	{
		m_PlayTime = 0.f;
	}
	MV1SetPosition(m_Enemy_ModelHandle, m_Enemy_Position);
}

void Enemy::Draw()
{
		// 新しいアニメーションをアタッチ
		if (m_Enemy_MoveFlag)
		{
			// 移動
			MV1SetAttachAnimTime(m_Enemy_ModelHandle, m_Enemy_AnimAttachIndex[ANIM_LIST::ANIM_RUN], m_PlayTime);

			VECTOR CenterPos = m_Enemy_Position;
			CenterPos.y += 6;
			//当たったところを終点にする
			VECTOR HitPos = { 0 };
			if (m_MapRef.CollisionToModel(CenterPos, VAdd(CenterPos, m_Vector), &HitPos))
			{
				return;
			}

			//初期始点値からどれくらいずらすのか
			VECTOR vertical{ 0,6,0 };
			//始点は現在のポジションと移動量を保存している変数を足している
			m_StartLine = VAdd(m_Enemy_Position, m_Vector);
			m_StartLine.y += vertical.y;
			//初期始点値からどれくらい下にレイを出すのか
			VECTOR DownLine{ 0,-20,0 };
			m_EndLine = VAdd(m_StartLine, DownLine);
			//出したレイのマップとのあたり判定
			if (m_MapRef.CollisionToModel(m_StartLine, m_EndLine, &HitPos))
			{
				m_Enemy_Position = HitPos;
			}
			DrawLine3D(m_Enemy_Position, m_StartLine, GetColor(0, 0, 255));
			DrawLine3D(m_StartLine, m_EndLine, GetColor(0, 0, 255));
		}
		else
		{
			// 待機
			MV1SetAttachAnimTime(m_Enemy_ModelHandle, m_Enemy_AnimAttachIndex[ANIM_LIST::ANIM_WAIT], m_PlayTime);
		}

	
	MV1DrawModel(m_Enemy_ModelHandle);
}


void Enemy::DrawHp()
{
}


