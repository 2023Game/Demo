#ifndef CCOLLISIONMANAGER_H
#define CCOLLISIONMANAGER_H
#include <list>
#include "CTreeManager.h"
#include "CCollider.h"

//衝突処理範囲より離れているコライダは衝突処理しない
#define COLLISIONRANGE 50

class CCollisionManager : public CTreeManager
{
public:
	//削除リストの要素を削除する
	void Delete();
	//削除リストに追加する
	void Delete(CCollider* c);

	//インスタンスの取得
	static CCollisionManager* Instance();
	//衝突処理
	void Collision(CCollider* m, CCollider* o, int low, int high);
	void Collision(CCollider* c);
	void Collision(CCollider* c, int range);
	//描画
	void Render();
	void Render(CTree* task);
private:
	//削除リスト
	std::list<CCollider*> mDeleteTrees;
	//デフォルトコンストラクタ
	CCollisionManager() {};
	//マネージャのインスタンス
	static CCollisionManager* mpInstance;
};

#endif
