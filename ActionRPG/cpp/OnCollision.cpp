#include "..\h\OnCollision.h"

void OnColl::Update(Player* player,Enemy* enemy)
{
    VECTOR PlayerTop = VAdd(player->GetPos(), player->GetHeight());
    HitPolyDim = MV1CollCheck_Capsule(enemy->GetModel(), -1, player->GetPos(),PlayerTop, 1.f);

    // 当たったかどうかで処理を分岐
    if (HitPolyDim.HitNum >= 1)
    {
        // 当たったポリゴンの数を描画
        DrawFormatString(100, 200, GetColor(255, 255, 255), "Hit   %d", HitPolyDim.HitNum);

        // 当たったポリゴンの数だけ繰り返し
        for (int i = 0; i < HitPolyDim.HitNum; i++)
        {
            // 当たったポリゴンを描画
            DrawTriangle3D(
                HitPolyDim.Dim[i].Position[0],
                HitPolyDim.Dim[i].Position[1],
                HitPolyDim.Dim[i].Position[2], GetColor(0, 255, 255), TRUE);
        }
    }
}

void OnColl::Draw(Player* player)
{
    VECTOR PlayerTop = VAdd(player->GetPos(), player->GetHeight());

    DrawCapsule3D(player->GetPos(), PlayerTop, 2.f, 8, GetColor(255, 255, 0), GetColor(255, 255, 255), FALSE);
}
