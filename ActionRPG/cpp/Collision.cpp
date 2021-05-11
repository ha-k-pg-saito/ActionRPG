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

void Collision::Update(Player* player, Map* map)
{
	// ３Ｄモデルの移動位置を上下に移動させる
	y += Add;
	if (y < 0 || y > 600)
		Add = -Add;

	// モデルと攻撃判定
	MV1SetupCollInfo(player->GetModel(), -1, 8, 8, 8);

    // モデルとマップの当たり判定
    MV1SetupCollInfo(map->GetModel(), -1, 8, 8, 8);
	
	// モデルと球との当たり判定（仮）
	HitPolyDim = MV1CollCheck_Sphere(player->GetModel(), -1, SpherePos, 100.0f);

    // 当たったかどうかで処理を分岐
    if (HitPolyDim.HitNum >= 1)
    {
        
    }

}

void Collision::Draw()
{
   
}