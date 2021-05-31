#include<Math.h>
#include "../h/Player.h"
#include"../h/Map.h"

void Player::Init(int modelhandle,int grhandle)
{
	m_ModelHandle = modelhandle;
#pragma region モデルテクスチャ読み込み・貼り付け
	m_GrHandle[0] = grhandle;
	m_GrHandle[1] = LoadGraph("Tex/Player/sister_hood.png");
	m_GrHandle[2] = LoadGraph("Tex/Player/sister_juel.png");
	m_GrHandle[3] = LoadGraph("Tex/Player/sister_flame.png");
	m_GrHandle[4] = LoadGraph("Tex/Player/sister_pierce.png");
	m_GrHandle[5] = LoadGraph("Tex/Player/sister_hair.png");
	m_GrHandle[6] = LoadGraph("Tex/Player/sister_ahoge.png");
	m_GrHandle[7] = LoadGraph("Tex/Player/sister_rod.png");
	
	//モデルに貼るテクスチャ分だけfor文を回す
	for (int i=0;i<8;i++)
	{
		MV1SetTextureGraphHandle(m_ModelHandle, i, m_GrHandle[i], FALSE);
	
		MV1SetMaterialAmbColor(m_ModelHandle, i ,GetColorF(0.5f, 0.5f, 0.5f, 1.f));
	}
#pragma endregion 
	
	//マテリアル関数でジュエルだけを発光
	MV1SetMaterialEmiColor(m_ModelHandle, 2, GetColorF(0.f, 1.f, 0.f, 1.f));
	
#pragma region アニメーション読み込み	
//待機モーション
	m_AnimHandle[ANIM_LIST::ANIM_WAIT] = MV1LoadModel("Tex/Cat/catwait.mv1");
	m_AnimAttachIndex[ANIM_LIST::ANIM_WAIT] =
		MV1AttachAnim(m_ModelHandle, 0, m_AnimHandle[ANIM_LIST::ANIM_WAIT], FALSE);
	m_AnimTotalTime[ANIM_LIST::ANIM_WAIT] =
		MV1GetAttachAnimTotalTime(m_ModelHandle, m_AnimAttachIndex[ANIM_LIST::ANIM_WAIT]);

//走りモーション	
	//m_AnimHandle[ANIM_LIST::ANIM_RUN] = MV1LoadModel("Tex/Player/sisterwalk.mv1");
	//アニメーションのデバッグ用モデル読み込み処理
	m_AnimHandle[ANIM_LIST::ANIM_RUN] = MV1LoadModel("Tex/Cat/catwalk.mv1");
	//指定したモデルにアニメーションをアタッチする
	m_AnimAttachIndex[ANIM_LIST::ANIM_RUN] = 
		MV1AttachAnim(m_ModelHandle, 0, m_AnimHandle[ANIM_LIST::ANIM_RUN], FALSE);
	//アタッチしたアニメーションの総時間を取得する
	m_AnimTotalTime[ANIM_LIST::ANIM_RUN] =
		MV1GetAttachAnimTotalTime(m_ModelHandle, m_AnimAttachIndex[ANIM_LIST::ANIM_RUN]);

//攻撃モーション
	m_AnimHandle[ANIM_LIST::ANIM_ATTACK] = MV1LoadModel("Tex/Cat/catattack.mv1");
	m_AnimAttachIndex[ANIM_LIST::ANIM_ATTACK] = 
		MV1AttachAnim(m_ModelHandle, 0, m_AnimHandle[ANIM_LIST::ANIM_ATTACK], TRUE);
	//アタッチしたアニメーションの総時間を取得する
	m_AnimTotalTime[ANIM_LIST::ANIM_ATTACK] = 
		MV1GetAttachAnimTotalTime(m_ModelHandle, m_AnimAttachIndex[ANIM_LIST::ANIM_ATTACK]);

//ダメージモーション
	m_AnimHandle[ANIM_LIST::ANIM_DAMAGE] = MV1LoadModel("Tex/Cat/catdamage.mv1");
	m_AnimAttachIndex[ANIM_LIST::ANIM_DAMAGE] = 
		MV1AttachAnim(m_ModelHandle, 0, m_AnimHandle[ANIM_LIST::ANIM_DAMAGE], TRUE);
	//アタッチしたアニメーションの総時間を取得する
	m_AnimTotalTime[ANIM_LIST::ANIM_DAMAGE] = 
		MV1GetAttachAnimTotalTime(m_ModelHandle, m_AnimAttachIndex[ANIM_LIST::ANIM_DAMAGE]);

//死亡モーション
	m_AnimHandle[ANIM_LIST::ANIM_DAMAGE] = MV1LoadModel("Tex/Cat/catdied.mv1");
	m_AnimAttachIndex[ANIM_LIST::ANIM_DAMAGE] =
		MV1AttachAnim(m_ModelHandle, 0, m_AnimHandle[ANIM_LIST::ANIM_DAMAGE], TRUE);
	//アタッチしたアニメーションの総時間を取得する
	m_AnimTotalTime[ANIM_LIST::ANIM_DAMAGE] =
		MV1GetAttachAnimTotalTime(m_ModelHandle, m_AnimAttachIndex[ANIM_LIST::ANIM_DAMAGE]);

#pragma endregion
	//　playerのモデルハンドル,フレーム番号,XYZの空間分割
	MV1SetupCollInfo(m_ModelHandle, -1, 1, 1, 1);
}

void Player::Update()
{
	m_PlayTime++;
	Rotate();
	Move();
	Attack();
	//collision.Update(this)

	//デバッグ用ダメージ関数の呼び出し
	if (CheckHitKey(KEY_INPUT_RETURN)) Damage();

	//現在の再生時間が総再生時間を超えたら再生時間を0に戻す
	if (m_PlayTime >= m_AnimTotalTime[ANIM_LIST::ANIM_RUN]|| m_PlayTime >= m_AnimTotalTime[ANIM_LIST::ANIM_WAIT])
	{
		m_PlayTime = 0.f;
	}

	MV1RefreshCollInfo(m_ModelHandle, -1);
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
	if (CheckHitKey(KEY_INPUT_D)) { Digree += RotateSpeed; }
	else if (CheckHitKey(KEY_INPUT_A)) { Digree -= RotateSpeed; }
	
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
	//一時的に移動量を保存する
	m_MoveVec = { 0.f };
#pragma region 移動処理 
	//向いている方向に移動
	if (CheckHitKey(KEY_INPUT_W))
	{ 
		//60で割ることで60フレームで進むベクトルを出している
		m_MoveVec.x -= m_Direction.x * (m_Speed * 1 / 60);
		m_MoveVec.z -= m_Direction.z * (m_Speed * 1 / 60);
	}
	else if (CheckHitKey(KEY_INPUT_S)) 
	{
		m_MoveVec.x += m_Direction.x * (m_Speed * 1 / 60);
		m_MoveVec.z += m_Direction.z * (m_Speed * 1 / 60);
	}	

#pragma endregion
	
	//移動したのかを調べて移動していたならアニメーションする
	if (m_MoveVec.x != 0.f || m_MoveVec.z != 0.f)
	{
		//atan2を使うことで現在の向いている方向から180振り向く
		float Rad = atan2(-m_MoveVec.x, -m_MoveVec.z);
		MV1SetRotationXYZ(m_ModelHandle, VGet(0.0f, Rad, 0.0f));
		m_Digree_Y = Rad * 180.f / DX_PI_F;
		//走るアニメーション
		MV1SetAttachAnimTime(m_ModelHandle, m_AnimAttachIndex[ANIM_LIST::ANIM_RUN], m_PlayTime);
		
		VECTOR CenterPos = m_Pos;
		CenterPos.y += 6;
		//当たったところを終点にする
		VECTOR HitPos = { 0 };
		if (m_MapRef->CollisionToModel(CenterPos,VAdd(CenterPos,m_MoveVec),&HitPos))
		{
			return;
		}

		//初期始点値からどれくらいずらすのか
		VECTOR vertical{ 0,6,0 };
		//始点は現在のポジションと移動量を保存している変数を足している
		m_StartLine = VAdd(m_Pos, m_MoveVec);
		m_StartLine.y +=vertical.y ;
		//初期始点値からどれくらい下にレイを出すのか
		VECTOR DownLine{ 0,-20,0 };
		m_EndLine = VAdd(m_StartLine, DownLine);
		//出したレイのマップとのあたり判定
		if (m_MapRef->CollisionToModel(m_StartLine, m_EndLine, &HitPos))
		{
			m_Pos = HitPos;
		}
		DrawLine3D(m_Pos, m_StartLine, GetColor(0, 0, 255));
		DrawLine3D(m_StartLine, m_EndLine, GetColor(0, 0, 255));
		// 画面に移るモデルの移動
		MV1SetPosition(m_ModelHandle, m_Pos);
	}
	else 
	{
		//待機モーション
		MV1SetAttachAnimTime(m_ModelHandle, m_AnimAttachIndex[ANIM_LIST::ANIM_WAIT], m_PlayTime);
	}
}

void Player::DrawHP()
{
	const int HPX = 75;
	const int HPY = 65;
	//HPゲージ描画
	if (m_HitCounter == 0)       m_Hp = DrawBox(HPX, HPY, 920, 140, GetColor(0, 255, 0), TRUE);
	else if (m_HitCounter == 1)  m_Hp = DrawBox(HPX, HPY, 709, 140, GetColor(0, 255, 0), TRUE); 
	else if (m_HitCounter == 2)  m_Hp = DrawBox(HPX, HPY, 498, 140, GetColor(0, 255, 0), TRUE); 
	else if (m_HitCounter == 3)  m_Hp = DrawBox(HPX, HPY, 287, 140, GetColor(0, 255, 0), TRUE);
	else if (m_HitCounter <= 4) 
	{
		m_Hp = DrawBox(HPX, HPY, 75, 140, GetColor(0, 255, 0), TRUE);
		MV1SetAttachAnimTime(m_ModelHandle, m_AnimAttachIndex[ANIM_LIST::ANIM_DIED], m_PlayTime);
		if (m_PlayTime >= m_AnimAttachIndex[ANIM_LIST::ANIM_DIED])  Release();
	}
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

void Player::Attack()
{
	if ((GetMouseInput() & MOUSE_INPUT_LEFT) != 0)
	{
		//攻撃アニメーション
		MV1SetAttachAnimTime(m_ModelHandle, m_AnimAttachIndex[ANIM_LIST::ANIM_ATTACK], m_PlayTime);
	}
}

//この関数はダメージを与えてきた敵にこの関数を呼び出す
void Player::Damage()
{
	m_HitCounter ++;
	MV1SetAttachAnimTime(m_ModelHandle, m_AnimAttachIndex[ANIM_LIST::ANIM_DAMAGE], m_PlayTime);
}
