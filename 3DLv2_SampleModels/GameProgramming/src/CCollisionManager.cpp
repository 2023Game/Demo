#include "CCollisionManager.h"
#include "CCollider.h"

//マネージャのインスタンス
CCollisionManager* CCollisionManager::mpInstance = nullptr;
//インスタンスの取得
CCollisionManager* CCollisionManager::Instance()
{
	if (mpInstance == nullptr)
	{
		mpInstance = new CCollisionManager();
	}
	return mpInstance;
}

void CCollisionManager::Collision(CCollider* m, CCollider* o, int low, int high)
{
	if (o == nullptr) return;

	//oが下限以上の場合
	if (low <= o->mPriority)
	{
		//oの左と衝突判定
		Collision(m, (CCollider*)o->mpLeft, low, high);
		//戻って来てoが上限以下の場合はmと衝突判定
		if (o->mPriority <= high)
		{
			if (m != o)
				m->mpParent->Collision((CCollider*)m, (CCollider*)o);
		}
	}
	//oが上限以下の場合
	if (o->mPriority <= high)
	{
		//oの右と衝突判定
		Collision(m, (CCollider*)o->mpRight, low, high);
	}
}


void CCollisionManager::Collision(CCollider* c)
{
	//ルートノードから衝突判定開始
	Collision(c, COLLISIONRANGE);
}

void CCollisionManager::Collision(CCollider* c, int range)
{
	//範囲下限を設定
	int low = c->mPriority - range;
	//範囲上限を設定
	int high = c->mPriority + range;

	//ルートノードから衝突判定開始
	Collision(c, (CCollider*)&Root(), low, high);
}

void CCollisionManager::Render()
{
	Render(Root().Right());
}

void CCollisionManager::Render(CTree* task)
{
	if (task == nullptr) return;
	Render(task->Left());
	((CTask*)task)->Render();
	Render(task->Right());
}

void CCollisionManager::Delete()
{
	for (auto tree : mDeleteTrees)
		delete tree;
	mDeleteTrees.clear();
}

void CCollisionManager::Delete(CCollider* c)
{
	mDeleteTrees.push_back(c);
}
