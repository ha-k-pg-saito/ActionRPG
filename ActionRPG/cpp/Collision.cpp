#include "../h/Collision.h"

Collision::Collision()
{
	Add = 8;

	y = 0;

	i = 0;
}

Collision::~Collision()
{
    // 当たり判定情報の後始末
    MV1CollResultPolyDimTerminate(HitPolyDim);
}

void Collision::Update(Player* player)
{
	// ３Ｄモデルの移動位置を上下に移動させる
	y += Add;
	if (y < 0 || y > 600)
		Add = -Add;

	// モデル全体のコリジョン情報構築
	MV1SetupCollInfo(player->GetModel(), -1, 8, 8, 8);

	// 当たり判定を行う球の位置をセット（仮）
	SpherePos = VGet(250.0f, y, 600.0f);

	// モデルと球との当たり判定（仮）
	HitPolyDim = MV1CollCheck_Sphere(player->GetModel(), -1, SpherePos, 100.0f);

    // 当たったかどうかで処理を分岐（仮）
    if (HitPolyDim.HitNum >= 1)
    {
        // 当たった場合は衝突の情報を描画する

        // 当たったポリゴンの数を描画
        DrawFormatString(0, 0, GetColor(255, 255, 255), "Hit Poly Num   %d", HitPolyDim.HitNum);

        // 当たったポリゴンの数だけ繰り返し
        for (i = 0; i < HitPolyDim.HitNum; i++)
        {
            // 当たったポリゴンを描画
            DrawTriangle3D(
                HitPolyDim.Dim[i].Position[0],
                HitPolyDim.Dim[i].Position[1],
                HitPolyDim.Dim[i].Position[2], GetColor(0, 255, 255), TRUE);
        }
    }

}

void Collision::Draw()
{
    // 球の描画(仮）
    DrawSphere3D(SpherePos, 100.0f, 8, GetColor(255, 255, 0), GetColor(255, 255, 255), FALSE);
}