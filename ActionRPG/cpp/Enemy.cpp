#include"../h/Enemy.h"
#include"math.h"

void Enemy::Init()
{
	m_Enemy_ModelHandle = MV1LoadModel("DxChara.x");

	m_Enemy_RunFlag = FALSE;

	// 待機アニメーションをアタッチ
	m_Enemy_AnimAttachIndex = MV1AttachAnim(m_Enemy_ModelHandle, 4);

	// 待機アニメーションの総時間を取得しておく
	m_Enemy_AnimTotalTime = MV1GetAttachAnimTotalTime(m_Enemy_ModelHandle, m_Enemy_AnimAttachIndex);

	// アニメーション再生時間を初期化
	m_Enemy_AnimNowTime = 0.0f;
	MV1SetAttachAnimTime(m_Enemy_ModelHandle, m_Enemy_AnimAttachIndex, m_Enemy_AnimNowTime);

	// アニメーションで移動をしているフレームの番号を検索する
	m_Enemy_MoveAnimFrameIndex = MV1SearchFrame(m_Enemy_ModelHandle, "BasePoint");

	// アニメーションで移動をしているフレームを無効にする
	MV1SetFrameUserLocalMatrix(m_Enemy_ModelHandle, m_Enemy_MoveAnimFrameIndex, MV1GetFrameLocalMatrix(m_Enemy_ModelHandle, m_Enemy_MoveAnimFrameIndex));

	// ３Ｄモデルの座標を初期化
	m_Rand_Pos.x = rand() % 5000 - 2500;
	m_Rand_Pos.z = rand() % 5000 - 2500;
	m_Rand_Pos.y = 0.0f;
	m_Enemy_Position = VGet(m_Rand_Pos.x, m_Rand_Pos.y, m_Rand_Pos.z);
	m_Enemy_InitialPosition = VGet(m_Rand_Pos.x, m_Rand_Pos.y, m_Rand_Pos.z);

	m_Hp = 3;
	IsActive = true;
}

void Enemy::Update(VECTOR player_pos)
{
	// ３ＤモデルEnemyから３ＤモデルPlayerに向かうベクトルを算出
	m_SubVector = VSub(player_pos, m_Enemy_Position);
	// ３ＤモデルEnemyから初期地点へのベクトルを算出
	m_Initial_EnemyVector = VSub(m_Enemy_InitialPosition, m_Enemy_Position);

	// atan2 を使用して角度を取得
	m_Enemy_Angle = atan2(m_SubVector.x, m_SubVector.z);
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
	if (m_Distance_Pos.x <= 4000.0f && m_Distance_Pos.z <= 4000.0f)
	{
		// atan2 で取得した角度に３Ｄモデルを正面に向かせるための補正値( DX_PI_F )を
		// 足した値を３Ｄモデルの Y軸回転値として設定
		MV1SetRotationXYZ(m_Enemy_ModelHandle, VGet(0.0f, m_Enemy_Angle + DX_PI_F, 0.0f));

		// 一定距離になるとPlayerの方に移動
		if (m_Distance_Pos.x <= 3000.0f && m_Distance_Pos.z <= 3000.0f)
		{
			if (m_Distance_Pos.x >= 300.0f) {
				m_Enemy_Position.x += m_Enemy_direction_x * m_Speed;
				m_Enemy_MoveFlag = TRUE;
			}
			if (m_Distance_Pos.z >= 300.0f) {
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

}

void Enemy::Draw()
{
	if (m_Enemy_RunFlag != m_Enemy_MoveFlag)
	{
		// 走っているかどうかのフラグを保存
		m_Enemy_RunFlag = m_Enemy_MoveFlag;

		// 今までアタッチしていたアニメーションをデタッチ
		MV1DetachAnim(m_Enemy_ModelHandle, m_Enemy_AnimAttachIndex);

		// 新しいアニメーションをアタッチ
		if (m_Enemy_RunFlag)
		{
			// 移動
			m_Enemy_AnimAttachIndex = MV1AttachAnim(m_Enemy_ModelHandle, 1);
		}
		else
		{
			// 待機
			m_Enemy_AnimAttachIndex = MV1AttachAnim(m_Enemy_ModelHandle, 4);
		}

		// アニメーションの総時間を取得しておく
		m_Enemy_AnimTotalTime = MV1GetAttachAnimTotalTime(m_Enemy_ModelHandle, m_Enemy_AnimAttachIndex);

		// アニメーション再生時間を初期化
		m_Enemy_AnimNowTime = 0.0f;
	}
	else
	{
		// アニメーション再生時間を進める
		m_Enemy_AnimNowTime += 200.0f;

		// アニメーション再生時間がアニメーションの総時間を越えていたらループさせる
		if (m_Enemy_AnimNowTime >= m_Enemy_AnimTotalTime)
		{
			// 新しいアニメーション再生時間は、アニメーション再生時間からアニメーション総時間を引いたもの
			m_Enemy_AnimNowTime -= m_Enemy_AnimTotalTime;
		}
	}

	// 新しいアニメーション再生時間をセット
	MV1SetAttachAnimTime(m_Enemy_ModelHandle, m_Enemy_AnimAttachIndex, m_Enemy_AnimNowTime);

	MV1SetPosition(m_Enemy_ModelHandle, m_Enemy_Position);
	MV1DrawModel(m_Enemy_ModelHandle);
}


void Enemy::DrawHp()
{
}


