#include"../h/Enemy.h"
#include"math.h"

void Enemy::Init(VECTOR pos)
{
	Enemy_ModelHandle = MV1LoadModel("DxChara.x");

	// 走っているフラグを倒す
	Enemy_RunFlag = FALSE;

	// 待機アニメーションをアタッチ
	Enemy_AnimAttachIndex = MV1AttachAnim(Enemy_ModelHandle, 4);

	// 待機アニメーションの総時間を取得しておく
	Enemy_AnimTotalTime = MV1GetAttachAnimTotalTime(Enemy_ModelHandle, Enemy_AnimAttachIndex);

	// アニメーション再生時間を初期化
	Enemy_AnimNowTime = 0.0f;
	MV1SetAttachAnimTime(Enemy_ModelHandle, Enemy_AnimAttachIndex, Enemy_AnimNowTime);

	// アニメーションで移動をしているフレームの番号を検索する
	Enemy_MoveAnimFrameIndex = MV1SearchFrame(Enemy_ModelHandle, "BasePoint");

	// アニメーションで移動をしているフレームを無効にする
	MV1SetFrameUserLocalMatrix(Enemy_ModelHandle, Enemy_MoveAnimFrameIndex, MV1GetFrameLocalMatrix(Enemy_ModelHandle, Enemy_MoveAnimFrameIndex));

	// ３Ｄモデルの座標を初期化
	Enemy_Position = VGet(pos.x, pos.y, pos.z);
	Enemy_InitialPosition = VGet(pos.x, pos.y, pos.z);

	IsActive = false;
}

void Enemy::Update(VECTOR player_pos)
{
	// ３Ｄモデル２から３Ｄモデル１に向かうベクトルを算出
	SubVector = VSub(player_pos, Enemy_Position);
	// ３Ｄモデル２から初期地点へのベクトルを算出
	Initial_EnemyVector = VSub(Enemy_InitialPosition, Enemy_Position);

	// atan2 を使用して角度を取得
	Enemy_Angle = atan2(SubVector.x, SubVector.z);
	Initial_EnemyAngle = atan2(Initial_EnemyVector.x, Initial_EnemyVector.z);

	// プレイヤーとエネミーの距離
	Distance_Pos.x = player_pos.x - Enemy_Position.x;
	Distance_Pos.z = player_pos.z - Enemy_Position.z;
	// エネミーの初期位置とエネミーの距離
	SetEnemy_Pos.x = Enemy_InitialPosition.x - Enemy_Position.x;
	SetEnemy_Pos.z = Enemy_InitialPosition.z - Enemy_Position.z;

	if (Distance_Pos.x < 0)
	{
		// プレイヤーとの方向の+-を修正
		Enemy_direction_x = -1;
		// プレイヤーとの距離の-を+に変更
		Distance_Pos.x *= -1;
	}
	else
	{
		Enemy_direction_x = 1;
	}
	if (Distance_Pos.z < 0)
	{
		Enemy_direction_z = -1;
		Distance_Pos.z *= -1;
	}
	else
	{
		Enemy_direction_z = 1;
	}

	if (SetEnemy_Pos.x < 0)
	{
		// 初期位置との方向の+-を修正
		Setenemy_direction_x = -1;
		// 初期位置との距離、-を+に変更
		SetEnemy_Pos.x *= -1;
	}
	else
	{
		Setenemy_direction_x = 1;
	}
	if (SetEnemy_Pos.z < 0)
	{
		Setenemy_direction_z = -1;
		SetEnemy_Pos.z *= -1;
	}
	else
	{
		Setenemy_direction_z = 1;
	}

	Enemy_MoveFlag = FALSE;

	// 一定距離になるとプレイヤーの方に向く
	if (Distance_Pos.x <= 4000.0f && Distance_Pos.z <= 4000.0f)
	{
		// atan2 で取得した角度に３Ｄモデルを正面に向かせるための補正値( DX_PI_F )を
		// 足した値を３Ｄモデルの Y軸回転値として設定
		MV1SetRotationXYZ(Enemy_ModelHandle, VGet(0.0f, Enemy_Angle + DX_PI_F, 0.0f));

		// 一定距離になるとプレイヤーの方に移動
		if (Distance_Pos.x <= 3000.0f && Distance_Pos.z <= 3000.0f)
		{
			if (Distance_Pos.x >= 300.0f) {
				Enemy_Position.x += Enemy_direction_x * m_Speed;
				Enemy_MoveFlag = TRUE;
			}
			if (Distance_Pos.z >= 300.0f) {
				Enemy_Position.z += Enemy_direction_z * m_Speed;
				Enemy_MoveFlag = TRUE;
			}
		}
	}
	else // 探知範囲外になると初期位置に戻る
	{
		MV1SetRotationXYZ(Enemy_ModelHandle, VGet(0.0f, Initial_EnemyAngle + DX_PI_F, 0.0f));

		if (SetEnemy_Pos.x >= 0.1f) {
			Enemy_Position.x += Setenemy_direction_x * m_Speed;
			Enemy_MoveFlag = TRUE;
		}
		if (SetEnemy_Pos.z >= 0.1f) {
			Enemy_Position.z += Setenemy_direction_z * m_Speed;
			Enemy_MoveFlag = TRUE;
		}
	}

}

void Enemy::Draw()
{
	if (Enemy_RunFlag != Enemy_MoveFlag)
	{
		// 走っているかどうかのフラグを保存
		Enemy_RunFlag = Enemy_MoveFlag;

		// 今までアタッチしていたアニメーションをデタッチ
		MV1DetachAnim(Enemy_ModelHandle, Enemy_AnimAttachIndex);

		// 新しいアニメーションをアタッチ
		if (Enemy_RunFlag)
		{
			Enemy_AnimAttachIndex = MV1AttachAnim(Enemy_ModelHandle, 1);
		}
		else
		{
			Enemy_AnimAttachIndex = MV1AttachAnim(Enemy_ModelHandle, 4);
		}

		// アニメーションの総時間を取得しておく
		Enemy_AnimTotalTime = MV1GetAttachAnimTotalTime(Enemy_ModelHandle, Enemy_AnimAttachIndex);

		// アニメーション再生時間を初期化
		Enemy_AnimNowTime = 0.0f;
	}
	else
	{
		// アニメーション再生時間を進める
		Enemy_AnimNowTime += 200.0f;

		// アニメーション再生時間がアニメーションの総時間を越えていたらループさせる
		if (Enemy_AnimNowTime >= Enemy_AnimTotalTime)
		{
			// 新しいアニメーション再生時間は、アニメーション再生時間からアニメーション総時間を引いたもの
			Enemy_AnimNowTime -= Enemy_AnimTotalTime;
		}
	}

	// 新しいアニメーション再生時間をセット
	MV1SetAttachAnimTime(Enemy_ModelHandle, Enemy_AnimAttachIndex, Enemy_AnimNowTime);

	MV1SetPosition(Enemy_ModelHandle, Enemy_Position);
	MV1DrawModel(Enemy_ModelHandle);
}


void Enemy::DrawHp()
{
}


