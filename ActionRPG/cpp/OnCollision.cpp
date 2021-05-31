#include "..\h\OnCollision.h"
#include"../h/Player.h"

void OnColl::Init(Player* player)
{
	//　playerのモデルハンドル,フレーム番号,XYZの空間分割
	MV1SetupCollInfo(player->GetModel(), -1, 1, 1, 1);
	//MV1SetupCollInfo(enemy->GetModel(), -1, 1, 1, 1);

}

void OnColl::Update(Player* player)
{
    MV1RefreshCollInfo(player->GetModel(), -1);
	SpherePos = VGet( 100.f, 0.f, 100.f );

	HitPolyDim = MV1CollCheck_Sphere(player->GetModel(), -1, SpherePos, 100.f);

	DrawSphere3D(SpherePos, 10.f, 8, GetColor(255, 0, 0), GetColor(255, 255, 255), TRUE);

    // 当たったかどうかで処理を分岐
    if (HitPolyDim.HitNum >= 1)
    {
        // 当たった場合は衝突の情報を描画する

        // 当たったポリゴンの数を描画
        DrawFormatString(100, 200, GetColor(255, 255, 255), "Hit Poly Num   %d", HitPolyDim.HitNum);

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
