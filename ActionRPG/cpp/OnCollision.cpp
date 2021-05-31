#include "..\h\OnCollision.h"

void OnColl::Update(Player* player,Enemy* enemy)
{
    VECTOR PlayerTop = VAdd(player->GetPos(), player->GetHeight());
    HitPolyDim = MV1CollCheck_Capsule(enemy->GetModel(), -1, player->GetPos(),PlayerTop, 1.f);

    // “–‚½‚Á‚½‚©‚Ç‚¤‚©‚Åˆ—‚ğ•ªŠò
    if (HitPolyDim.HitNum >= 1)
    {
        // “–‚½‚Á‚½ƒ|ƒŠƒSƒ“‚Ì”‚ğ•`‰æ
        DrawFormatString(100, 200, GetColor(255, 255, 255), "Hit   %d", HitPolyDim.HitNum);

        // “–‚½‚Á‚½ƒ|ƒŠƒSƒ“‚Ì”‚¾‚¯ŒJ‚è•Ô‚µ
        for (int i = 0; i < HitPolyDim.HitNum; i++)
        {
            // “–‚½‚Á‚½ƒ|ƒŠƒSƒ“‚ğ•`‰æ
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
