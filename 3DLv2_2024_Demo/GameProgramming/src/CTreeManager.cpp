#include "CTreeManager.h"

// コンストラクタ
CTreeManager::CTreeManager()
{
	mRoot.mPriority = -1;
}

// デストラクタ
CTreeManager::~CTreeManager()
{
}

void CTreeManager::Add(CTree* add)
{
	// ルートから追加開始
	Add(&mRoot, add);
}

void CTreeManager::Add(CTree* parent, CTree* add)
{
	//優先度同じ　左へ追加
	if (add->mPriority == parent->mPriority)
	{
		if (parent->mpLeft == nullptr)
		{
			// 左が無い時は、左へ追加
			add->mpParentNode = parent;
			parent->mpLeft = add;
		}
		else
		{
			// 左がある時は、親と左の間へ追加
			add->mpLeft = parent->mpLeft;
			parent->mpLeft->mpParentNode = add;
			parent->mpLeft = add;
			add->mpParentNode = parent;
		}
	}
	//優先度低い　左へ追加
	else if (add->mPriority < parent->mPriority)
	{
		if (parent->mpLeft == nullptr)
		{
			// 左が無い時は、左へ追加
			add->mpParentNode = parent;
			parent->mpLeft = add;
		}
		else
		{
			// 左がある時は、左へ移動
			Add(parent->mpLeft, add);
		}
	}
	//優先度高い　右へ追加
	else
	{
		if (parent->mpRight == nullptr)
		{
			// 右が無い時は、右へ追加
			add->mpParentNode = parent;
			parent->mpRight = add;
		}
		else
		{
			// 右があるときは、右へ移動
			Add(parent->mpRight, add);
		}
	}
}

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
			// Moveメソッド設定用に準備
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
			// Moveメソッド設定用に準備
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
