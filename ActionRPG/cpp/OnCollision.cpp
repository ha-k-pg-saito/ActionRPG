#include"../h/OnCollision.h"

void OnColl::Update(Player* player,Enemy* enemy)
{
//毎フレーム0で初期化
    m_CharPos = { 0.f };

//それぞれのモデルの頂点算出
    VECTOR PlayerTop = VAdd(player->GetPos(), player->GetHeight());
    VECTOR EnemyTop = VAdd(enemy->GetPos(), enemy->GetHeight());
//移動前のPlayerの座標保存
    m_CharPos = player->GetPos();
//過去のポジションが入る
    m_OldCharPos = m_CharPos;
   
//  Playerの半径２　Enemyの半径は４
    if (HitCheck_Capsule_Capsule(player->GetPos(), PlayerTop, 2.f, enemy->GetPos(), EnemyTop, 4.f) == TRUE)
    {
#ifdef _DEBUG
        DrawString(1700, 100, "Hit", GetColor(255, 255, 255));
#endif     
       
        //当たっているなら移動前の座標を返す
        player->SetPos(m_OldCharPos);
    }
}

void OnColl::Draw(Player* player,Enemy* enemy)
{
#ifdef _DEBUG
    VECTOR PlayerTop = VAdd(player->GetPos(), player->GetHeight());
    VECTOR EnemyTop = VAdd(enemy->GetPos(), enemy->GetHeight());

    DrawCapsule3D(player->GetPos(), PlayerTop, 2.f, 4, GetColor(255, 255, 0), GetColor(255, 255, 255), FALSE);
    DrawCapsule3D(enemy->GetPos(), EnemyTop, 4.f, 4, GetColor(255, 255, 0), GetColor(255, 255, 255), FALSE);

#endif
}