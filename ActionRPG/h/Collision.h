#ifndef Collison_h_
#define Collison_h_

#include "DxLib.h"
#include "../h/Player.h"
#include "../h/Map.h"

class Collision
{
public:
	Collision();
	~Collision();

	void Update(Player *player, Map *map);
	void Draw();

private:
	MV1_COLL_RESULT_POLY_DIM HitDim;			// キャラクターの周囲にあるポリゴンを検出した結果が代入される当たり判定結果構造体
	int Add, y, i;
	VECTOR SpherePos;
	int KabeNum;						// 壁ポリゴンと判断されたポリゴンの数
	int YukaNum;                        // 床ポリゴンと判断されたポリゴンの数

#define CHARA_MAX_HITCOLL			2048		// 処理するコリジョンポリゴンの最大数
	MV1_COLL_RESULT_POLY *Kabe[CHARA_MAX_HITCOLL];	// 壁ポリゴンと判断されたポリゴンの構造体のアドレスを保存しておくためのポインタ配列
	MV1_COLL_RESULT_POLY *Yuka[CHARA_MAX_HITCOLL];	// 床ポリゴンと判断されたポリゴンの構造体のアドレスを保存しておくためのポインタ配列

};

#endif // !1



