#pragma once
#include "CTree.h"

/// <summary>
/// 2文探索木の管理クラス
/// </summary>
class CTreeManager
{
public:
	//２分探索木にaddを追加する
	void Add(CTree* add);

	// Remove(削除ノード)
	void Remove(CTree* remove);

	//2分探索木のルート取得
	CTree& Root() { return mRoot; }
	// コンストラクタ
	CTreeManager();
	// デストラクタ
	~CTreeManager();
private:
	void Add(CTree* parent, CTree* add);
	// 最大値下位ノードの取得
	CTree* Max(CTree* task);
	// 最小値下位ノードの取得
	CTree* Min(CTree* task);
	// Move(移動先, 移動元）
	void Move(CTree* dest, CTree* src);

	//2分探索木のルート
	CTree mRoot;
};
