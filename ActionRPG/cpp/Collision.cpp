#include "../h/Collision.h"

Collision::Collision()
{
	Add = 8;

	y = 0;

	i = 0;

	KabeNum = 0;

	YukaNum = 0;
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



}

void Collision::Draw()
{
   
}