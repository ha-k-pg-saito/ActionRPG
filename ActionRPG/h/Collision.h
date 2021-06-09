//#ifndef Collison_h_
//#define Collison_h_
//
//#include "DxLib.h"
//#include <math.h>
//#include "../h/Player.h"
//#include "../h/Map.h"
//
//#define PLAYER_ENUM_DEFAULT_SIZE		800.0f		// 周囲のポリゴン検出に使用する球の初期サイズ
//
//class Collision
//{
//public:
//	Collision();
//	~Collision();
//
//	void Update(Player *player);
//	void Draw();
//
//private:
//	MV1_COLL_RESULT_POLY_DIM HitDim;			// キャラクターの周囲にあるポリゴンを検出した結果が代入される当たり判定結果構造体
//	int Add, y, i;
//	VECTOR SpherePos;
//	int KabeNum;						// 壁ポリゴンと判断されたポリゴンの数
//	int YukaNum;                        // 床ポリゴンと判断されたポリゴンの数
//	int HitFlag;                        // ポリゴンに当たったかどうかを記憶しておくのに使う変数( ０:当たっていない  １:当たった )  
//	int MoveFlag;						// 水平方向に移動したかどうかのフラグ( ０:移動していない  １:移動した )
//	HITRESULT_LINE LineRes;				// 線分とポリゴンとの当たり判定の結果を代入する構造体
//	VECTOR NowPos;
//
//#define CHARA_MAX_HITCOLL			2048		// 処理するコリジョンポリゴンの最大数
//	MV1_COLL_RESULT_POLY *Kabe[CHARA_MAX_HITCOLL];	// 壁ポリゴンと判断されたポリゴンの構造体のアドレスを保存しておくためのポインタ配列
//	MV1_COLL_RESULT_POLY *Yuka[CHARA_MAX_HITCOLL];	// 床ポリゴンと判断されたポリゴンの構造体のアドレスを保存しておくためのポインタ配列
//	MV1_COLL_RESULT_POLY* Poly;
//};
//#endif // !