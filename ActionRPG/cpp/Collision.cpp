#include "../h/Collision.h"

Collision::Collision(Player *player )
{
	Add = 8;

	y = 0;

	i = 0;

	KabeNum = 0;

	YukaNum = 0;

	NowPos = VAdd(player->GetPos(), player->MoveVector());
}

Collision::~Collision()
{
    // 当たり判定情報の後始末
    //MV1CollResultPolyDimTerminate(HitPoly);
}

void Collision::Update(Player* player, Map* map)
{
	HitDim =  MV1CollCheck_Sphere(player->GetModel(), -1, player->GetPos(), 800.0f + player->MoveVector());

	// モデルと攻撃判定
	MV1SetupCollInfo(player->GetModel(), -1, 8, 8, 8);

    // モデルとマップの当たり判定
    MV1SetupCollInfo(map->GetModel(), -1, 8, 8, 8); 

	// モデルと球との当たり判定（仮）
	//HitPoly = MV1CollCheck_Line(player->GetModel(), -1, SpherePos, 100.0f);

	for (i = 0; i < HitDim.HitNum; i++)
	{
		// ＸＺ平面に垂直かどうかはポリゴンの法線のＹ成分が０に限りなく近いかどうかで判断する
		if (HitDim.Dim[i].Normal.y < 0.000001f && HitDim.Dim[i].Normal.y > -0.000001f)
		{
			// 壁ポリゴンと判断された場合でも、キャラクターのＹ座標＋１．０ｆより高いポリゴンのみ当たり判定を行う
			if (HitDim.Dim[i].Position[0].y > player->GetPos().y + 1.0f ||
				HitDim.Dim[i].Position[1].y > player->GetPos().y + 1.0f ||
				HitDim.Dim[i].Position[2].y > player->GetPos().y + 1.0f)
			{
				// ポリゴンの数が列挙できる限界数に達していなかったらポリゴンを配列に追加
				if (KabeNum < 2048)
				{
					// ポリゴンの構造体のアドレスを壁ポリゴンポインタ配列に保存する
					Kabe[KabeNum] = &HitDim.Dim[i];

					// 壁ポリゴンの数を加算する
					KabeNum++;
				}
			}
		}
		else
		{
			// ポリゴンの数が列挙できる限界数に達していなかったらポリゴンを配列に追加
			if (YukaNum < CHARA_MAX_HITCOLL)
			{
				// ポリゴンの構造体のアドレスを床ポリゴンポインタ配列に保存する
				Yuka[YukaNum] = &HitDim.Dim[i];

				// 床ポリゴンの数を加算する
				YukaNum++;
			}
		}
	}

	// 床ポリゴンとの当たり判定
	if (YukaNum != 0)
	{
			float MaxY;

			// 下降中かジャンプ中ではない場合の処理

			// 床ポリゴンに当たったかどうかのフラグを倒しておく
			HitFlag = 0;

			// 一番高い床ポリゴンにぶつける為の判定用変数を初期化
			MaxY = 0.0f;

			// 床ポリゴンの数だけ繰り返し
			for (i = 0; i < YukaNum; i++)
			{
				// i番目の床ポリゴンのアドレスを床ポリゴンポインタ配列から取得
				Poly = Yuka[i];

				
					// 走っている場合は頭の先からそこそこ低い位置の間で当たっているかを判定( 傾斜で落下状態に移行してしまわない為 )
					LineRes = HitCheck_Line_Triangle(VAdd(NowPos, VGet(0.0f, PLAYER_HIT_HEIGHT, 0.0f)), VAdd(NowPos, VGet(0.0f, -40.0f, 0.0f)), Poly->Position[0], Poly->Position[1], Poly->Position[2]);
				

				// 当たっていなかったら何もしない
				if (LineRes.HitFlag == FALSE) continue;

				// 既に当たったポリゴンがあり、且つ今まで検出した床ポリゴンより低い場合は何もしない
				if (HitFlag == 1 && MaxY > LineRes.Position.y) continue;

				// ポリゴンに当たったフラグを立てる
				HitFlag = 1;

				// 接触したＹ座標を保存する
				MaxY = LineRes.Position.y;
			}

			// 床ポリゴンに当たったかどうかで処理を分岐
			if (HitFlag == 1)
			{
				// 当たった場合

				// 接触したポリゴンで一番高いＹ座標をプレイヤーのＹ座標にする
				NowPos.y = MaxY;

				

				
					// 移動していたかどうかで着地後の状態と再生するアニメーションを分岐する
					if (MoveFlag)
					{
						// 移動している場合は走り状態に
						Player_PlayAnim(1);
						pl.State = 1;
					}
					else
					{
						// 移動していない場合は立ち止り状態に
						Player_PlayAnim(4);
						pl.State = 0;
					}

					// 着地時はアニメーションのブレンドは行わない
					pl.AnimBlendRate = 1.0f;
				
			}
	}

}

void Collision::Draw()
{
   
}