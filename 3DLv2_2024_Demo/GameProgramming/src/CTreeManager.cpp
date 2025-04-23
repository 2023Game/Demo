#include "CTreeManager.h"

//// コリジョンマネージャのインスタンス
//CTreeManager* CTreeManager::mpInstance = nullptr;
//
//// インスタンスを取得
//CTreeManager* CTreeManager::Instance()
//{
//	if (mpInstance == nullptr)
//	{
//		mpInstance = new CTreeManager();
//	}
//	return mpInstance;
//}
//
//// インスタンスの破棄
//void CTreeManager::ClearInstance()
//{
//	delete mpInstance;
//	mpInstance = nullptr;
//}

// コンストラクタ
CTreeManager::CTreeManager()
	: mIsShowCollider(false)
	, mpRoot(nullptr)
{
}

// デストラクタ
CTreeManager::~CTreeManager()
{
}


void CTreeManager::Add(CTree* add)
{
	if (mpRoot == nullptr)
	{
		mpRoot = add;
		add->mpParentNode = mpRoot;
	}
	else
	{
		Add(mpRoot, add);
	}
}

void CTreeManager::Add(CTree* parent, CTree* add)
{
	if (add->mPriority == parent->mPriority)
	{
		if (parent->mpLeft == nullptr)
		{
			add->mpParentNode = parent;
			parent->mpLeft = add;
		}
		else
		{
			add->mpLeft = parent->mpLeft;
			parent->mpLeft->mpParentNode = add;
			parent->mpLeft = add;
			add->mpParentNode = parent;
		}
	}
	else if (add->mPriority < parent->mPriority)
	{
		if (parent->mpLeft == nullptr)
		{
			add->mpParentNode = parent;
			parent->mpLeft = add;
		}
		else
		{
			Add(parent->mpLeft, add);
		}
	}
	else
	{
		if (parent->mpRight == nullptr)
		{
			add->mpParentNode = parent;
			parent->mpRight = add;
		}
		else
		{
			Add(parent->mpRight, add);
		}
	}
}

//int max = 0;
//int nest = 0;

/*
CCollider* CTreeManager::CollisionTrigger(CTree* m, CTree* o, int low, int high)
{
	CCollider* collider = nullptr;

	if (o == nullptr) return nullptr;
	//printf("%ld:%ld\n", m->mPriority, o->mPriority);
	//oが下限以上の場合
	if (low <= o->mPriority)
	{
		//oの左と衝突判定
		collider = CollisionTrigger(m, o->mpLeft, low, high);
		if (collider != nullptr) return collider;
		//戻って来てoが上限以下の場合はmと衝突判定
		if (o->mPriority <= high)
		{
			if (m != o)
				collider = CollisionTrigger((CCollider*)m, (CCollider*)o);
		}
		if (collider != nullptr) return collider;
	}
	//oが上限以下の場合
	if (o->mPriority <= high)
	{
		//oの右と衝突判定
		collider = CollisionTrigger(m, o->mpRight, low, high);
	}
	if (collider != nullptr) return collider;
}

#define COLLISION_RANGE 100 //衝突判定範囲
CCollider* CTreeManager::CollisionTrigger(CTree* c)
{
	//ルートノードから衝突判定開始
	return (CCollider*)CollisionTrigger(c, COLLISION_RANGE);
}

CCollider* CTreeManager::CollisionTrigger(CTree* c, int range)
{
	//範囲下限を設定
	int low = c->mPriority - range;
	//範囲上限を設定
	int high = c->mPriority + range;

	//ルートノードから衝突判定開始
	return (CCollider*)CollisionTrigger(c, mpRoot, low, high);
}
*/
void CTreeManager::Remove(CTree* remove)
{
	//左がある時は、左の最大値ノードと入替
	if (remove->mpLeft != nullptr)
	{
		//左ノード内の最大値ノードをMaxで取得
		CTree* move = Max(remove->mpLeft);
		//最大値がすぐ左
		if (move == remove->mpLeft)
		{
			remove->mpLeft = move->mpLeft;
		}
		//最大値が左ではない場合
		else
		{
			//最大値の親ノードの右に、最大値ノードの左を歳入
			move->mpParentNode->mpRight = move->mpLeft;
			//最大値ノードの左がある場合
			if (move->mpLeft != nullptr)
				//最大値ノードの左の親に、最大値ノードの親を代入
				move->mpLeft->mpParentNode = move->mpParentNode;
		}
		//removeの位置に、moveを移動させる
		Move(remove, move);
	}
	//左がない時は、右の最小値ノードと入替
	else if (remove->mpRight != nullptr)
	{
		//右ノードの最小値をMinで取得
		CTree* move = Min(remove->mpRight);
		//最小値がすぐ右の場合
		if (move == remove->mpRight)
		{
			remove->mpRight = move->mpRight;
		}
		//最小値がすぐ右でない場合
		else
		{
			//最小値の親ノードの左に、最小値ノードの右を代入
			move->mpParentNode->mpLeft = move->mpRight;
			//最小値ノードの右がある場合
			if (move->mpRight != nullptr)
				//最小値ノードの右の親に、最小値ノードの親を代入
				move->mpRight->mpParentNode = move->mpParentNode;
		}
		//removeの位置に、moveを移動させる
		Move(remove, move);
	}
	//子ノードがない時
	else
	{
		//削除ノードがルートの場合
		if (remove->mpParentNode == remove)
		{
			//ルートを初期値にする
			//CTreeManager::Instance()->mpRoot = nullptr;
			mpRoot = nullptr;
		}
		//削除ノードがルート以外の場合
		else
		{
			if (remove->mpParentNode != nullptr)
			{
				//削除ノードが親ノードの左の場合
				if (remove->mpParentNode->mpLeft == remove)
					//削除ノードの親ノードの左を初期化する
					remove->mpParentNode->mpLeft = nullptr;
				//削除ノードが親ノードの右の場合
				if (remove->mpParentNode->mpRight == remove)
					//削除ノードの親ノードの右を初期化する
					remove->mpParentNode->mpRight = nullptr;
			}
		}
	}
	//削除ノードの親、左、右を初期化する
	remove->mpParentNode = remove->mpLeft = remove->mpRight = nullptr;
}

CTree* CTreeManager::Max(CTree* task)
{
	//一番右にあるノードが最大値
	//一番右にあるノードの右はnullptr
	if (task->mpRight == nullptr)
		return task;
	return Max(task->mpRight);
}

CTree* CTreeManager::Min(CTree* task)
{
	//一番左にあるノードが最小値
	//一番左にあるノードの左はnullptr
	if (task->mpLeft == nullptr)
		return task;
	return Min(task->mpLeft);
}

void CTreeManager::Move(CTree* remove, CTree* move)
{
	// 親の更新
	//ルートノードは、親ポインタを自身のポインタにしている
	if (remove->mpParentNode == remove)
	{
		// 削除ノードがルートの場合
		//ルートを移動ノードにして、移動ノードの親を自身のポインタにする
		//CTreeManager::Instance()->mpRoot = move;
		mpRoot = move;
		move->mpParentNode = move;
	}
	else
	{
		//削除ノードの親の左が、削除ノードの場合
		if (remove->mpParentNode->mpLeft == remove)
			//削除ノードの親の左を移動ノードにする
			remove->mpParentNode->mpLeft = move;
		//削除ノードの親の右が、削除ノードの場合
		if (remove->mpParentNode->mpRight == remove)
			//削除ノードの親の右を移動ノードにする
			remove->mpParentNode->mpRight = move;
		//移動ノードの親に、削除ノードの親を代入
		move->mpParentNode = remove->mpParentNode;
	}

	// 左の更新
	// 削除ノードに左があれば
	if (remove->mpLeft != nullptr)
	{
		//削除ノードの左の親に、移動ノードを代入
		remove->mpLeft->mpParentNode = move;
	}
	//移動ノードの左に削除ノードの左を代入
	move->mpLeft = remove->mpLeft;

	// 右の更新
	// 削除ノードに右があれば
	if (remove->mpRight != nullptr)
	{
		//削除ノードの右の親に、移動ノードを代入
		remove->mpRight->mpParentNode = move;
	}
	//移動ノードの右に削除ノードの右を代入
	move->mpRight = remove->mpRight;
}

void CTreeManager::Render()
{
	Render(mpRoot);
}

void CTreeManager::Render(CTree* task)
{
	if (task == nullptr) return;
	Render(task->mpLeft);
	((CTask*)task)->Render();
	Render(task->mpRight);
}

//void CTreeManager::UpdateAllNode(CTree* t)
//{
//	if (t->mpLeft)
//		UpdateAllNode(t->mpLeft);
//	((CCollider*)t)->Update();
//	((CCollider*)t)->UpdateCol();
//	if (t->mpRight)
//		UpdateAllNode(t->mpRight);
//}