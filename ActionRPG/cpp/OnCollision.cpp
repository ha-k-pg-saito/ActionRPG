#include"../h/OnCollision.h"

void OnColl::Update(Player* player,Enemy* enemy)
{
    //毎フレーム0で初期化
    m_MoveVec = { 0 };
    //それぞれのモデルの頂点算出
    VECTOR PlayerTop = VAdd(player->GetPos(), player->GetHeight());
    VECTOR EnemyTop = VAdd(enemy->GetPos(), enemy->GetHeight());
  
    //移動後のPlayerの座標算出
    m_CharPos = VAdd(player->GetPos(), player->GetMoveVec());
    
    //  Playerの半径２　Enemyの半径は４
    if (HitCheck_Capsule_Capsule(m_CharPos, PlayerTop, 2.f, enemy->GetPos(), EnemyTop, 4.f) == TRUE)
    {
#ifdef _DEBUG
        DrawString(1700, 100, "Hit",GetColor(255, 255, 255));
#endif
        //PlayerからEnemyへのベクトル算出
        m_CharVec = VSub(m_CharPos, enemy->GetPos());
        //二つのobjectの距離算出
        m_Length = VSize(m_CharVec);
        //ベクトルの正規化
        m_PushVec = VScale(m_CharVec, 1.f / m_Length);
        // もし二人の距離から二人の大きさを引いた値に押し出し力を足して離れてしまう場合は、くっつく距離に移動する
        if (m_Length - 2.f + 4.f + 100 > 0.f)
        {
           m_CharPos = VAdd(enemy->GetPos(), VScale(m_PushVec, 2.f + 4.f));
        }
        else
        {
            //重なっている場合押し出す
           m_CharPos = VAdd(m_CharPos, VScale(m_PushVec, 100.f));
        }
    }
    m_MoveVec = VSub(m_CharPos, player->GetPos());
    player->SetPos(m_MoveVec);
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