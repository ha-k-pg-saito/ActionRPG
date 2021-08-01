#include"../h/OnCollision.h"

bool  OnColl::Update(const Capsule* player, const Capsule* enemy)
{
//Playerの半径２　Enemyの半径は４.3
    if (HitCheck_Capsule_Capsule(player->Bottom, player->Top,player->Radius , enemy->Bottom, enemy->Top, enemy->Radius) == TRUE)
    {
#ifdef _DEBUG

        DrawString(1700, 100, "Hit", GetColor(255, 255, 255));

#endif    
        return true;
    }

    return false;
}

//バウンディングボックスによる衝突判定
bool OnColl::OnCollisionAABB(const AABB* player, const AABB* enemy)
{
    if (player->Min.x > enemy->Max.x)  return false;
    if (player->Min.y > enemy->Max.y)  return false;
    if (player->Min.z > enemy->Max.z)  return false;
    if (player->Max.x < enemy->Min.x)  return false;
    if (player->Max.y < enemy->Min.y)  return false;
    if (player->Max.z < enemy->Min.z)  return false;

    return true;
}

void OnColl::Draw(Capsule* capsule)
{
#ifdef _DEBUG
    DrawCapsule3D(capsule->Bottom, capsule->Top, capsule->Radius, m_PolyFine, GetColor(255, 255, 0), GetColor(255, 255, 255), FALSE);
#endif
}