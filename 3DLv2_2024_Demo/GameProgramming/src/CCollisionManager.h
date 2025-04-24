#ifndef CCOLLISIONMANAGER_H
#define CCOLLISIONMANAGER_H

#include "CTreeManager.h"
#include "CCollider.h"

//衝突処理範囲より離れているコライダは衝突処理しない
#define COLLISIONRANGE 30

class CCollisionManager : public CTreeManager
{
public:
	//インスタンスの取得
	static CCollisionManager* Instance();
	void Collision(CCollider* m, CCollider* o, int low, int high);
	void Collision(CCollider* c);
	void Collision(CCollider* c, int range);
	void Render();
	void Render(CTree* task);
private:
	//デフォルトコンストラクタ
	CCollisionManager() {};
	//マネージャのインスタンス
	static CCollisionManager* mpInstance;
};

#endif
