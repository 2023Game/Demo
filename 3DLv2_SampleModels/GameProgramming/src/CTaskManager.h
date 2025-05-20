#ifndef CTASKMANAGER_H
#define CTASKMANAGER_H
//タスククラスのインクルード
#include <list>
#include "CTask.h"
#include "CTreeManager.h"

#define TASK_RANGE 100

class CTaskManager : public CTreeManager
{
public:
	//インスタンスの取得
	static CTaskManager* Instance();
	//削除リストのタスクを削除
	void Delete();
	//削除リストに追加
	void Delete(CTask* task);
	//デストラクタ
	virtual ~CTaskManager();
	//更新
	void Update();
	//衝突
	void Collision();
	//描画
	void Render();
	void RenderUI();
private:
	//更新
	void Update(CTree* task);
	//衝突
	void Collision(CTree* task);
	//描画
	void Render(CTree* task);
	void RenderUI(CTree* task);
	//削除リスト
	std::list<CTask*> mDeleteTrees;
	//デフォルトコンストラクタ
	CTaskManager();
	//タスクマネージャのインスタンス
	static CTaskManager* mpInstance;
};

/*
タスクマネージャ
タスクリストの管理

class CTaskManager {
public:
	void Collision();
	//インスタンスの取得
	static CTaskManager* Instance();
	//タスクの削除
	void Delete();
	//リストから削除
	//Remove(タスクのポインタ)
	void Remove(CTask* task);
	//デストラクタ
	virtual ~CTaskManager();
	//リストに追加
	//Add(タスクのポインタ)
	void Add(CTask* addTask);
	//更新
	void Update();
	//描画
	void Render();
protected:
	//デフォルトコンストラクタ
	CTaskManager();
	CTask mHead;//先頭タスク
	CTask mTail;//最終タスク
private:
	//タスクマネージャのインスタンス
	static CTaskManager* mpInstance;
};
*/

#endif
