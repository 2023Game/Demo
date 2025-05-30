#include "CTaskManager.h"

//タスクマネージャのインスタンス
CTaskManager* CTaskManager::mpInstance = nullptr;

//インスタンスの取得
CTaskManager* CTaskManager::Instance()
{
	//インスタンスが無ければ
	if (mpInstance == nullptr)
	{	//インスタンスを生成する
		mpInstance = new CTaskManager();
	}
	return mpInstance;
}

//デフォルトコンストラクタ
CTaskManager::CTaskManager()
{
}

CTaskManager::~CTaskManager()
{
}

void CTaskManager::Delete()
{
	for (auto tree : mDeleteTrees)
		delete tree;
	mDeleteTrees.clear();
}

void CTaskManager::Delete(CTask* task)
{
	mDeleteTrees.push_back(task);
}

void CTaskManager::Update() 
{
	Update(Root().Right());
}
//更新
void CTaskManager::Update(CTree* task)
{
	if (task == nullptr) return;
	Update(task->Left());
	((CTask*)task)->Update();
	Update(task->Right());
}

void CTaskManager::Render()
{
	Render(Root().Right());
}

//描画
//優先度の降順に描画
void CTaskManager::Render(CTree* task) {
	if (task == nullptr) return;
	Render(task->Right());
	((CTask*)task)->Render();
	Render(task->Left());
}

void CTaskManager::RenderUI()
{
	RenderUI(Root().Right());
}

//描画
//優先度の降順に描画
void CTaskManager::RenderUI(CTree* task) {
	if (task == nullptr) return;
	RenderUI(task->Right());
	((CTask*)task)->RenderUI();
	RenderUI(task->Left());
}

//衝突処理
void CTaskManager::Collision()
{
	Collision(Root().Right());
}

void CTaskManager::Collision(CTree* task) {
	if (task == nullptr) return;
	Collision(task->Left());
	((CTask*)task)->Collision();
	Collision(task->Right());
}


/*

//デフォルトコンストラクタ
CTaskManager::CTaskManager()
{
	mHead.mpNext = &mTail;
	mTail.mpPrev = &mHead;
}

void CTaskManager::Delete() {
	//先頭から最後まで繰り返し
	CTask* task = mHead.mpNext;
	while (task->mpNext) {
		CTask* del = task;
		//次へ
		task = task->mpNext;
		//mEnabledがfalseなら削除
		if (del->mEnabled == false) {
			delete del;
		}
	}
}

void CTaskManager::Remove(CTask* task)
{
	//タスクの前の次を、タスクの次にする
	task->mpPrev->mpNext = task->mpNext;
	//タスクの次の前を、タスクの前にする
	task->mpNext->mpPrev = task->mpPrev;
}
CTaskManager::~CTaskManager() {
}
//リストに追加
//Add(タスクのポインタ)
void CTaskManager::Add(CTask* addTask)
{
	//mHeadの次から検索
	CTask* task = mHead.mpNext;

	//優先度の大きい順に挿入する
	//挿入位置の検索（優先度が同じか大きくなった前）
	//mPriority>=0のこと
	while (addTask->mPriority < task->mPriority)
	{
		task = task->mpNext; //次へ
	}

	//addTaskの次をtask
	addTask->mpNext = task;
	//addTaskの前をtaskの前に
	addTask->mpPrev = task->mpPrev;
	//addTaskの前の次をaddTaskに
	addTask->mpPrev->mpNext = addTask;
	//taskの前をaddTaskに
	task->mpPrev = addTask;
}

//更新
void CTaskManager::Update() {
	//先頭から最後まで繰り返し
	CTask* task = mHead.mpNext;
	while (task->mpNext) {
		//更新処理を呼ぶ
		task->Update();
		//次へ
		task = task->mpNext;
	}
}

//描画
void CTaskManager::Render() {
	//最後から先頭まで繰り返し
	CTask* task = mTail.mpPrev;
	while (task->mpPrev) {
		//描画処理を呼ぶ
		task->Render();
		//次へ
		task = task->mpPrev;
	}
}

//衝突処理
void CTaskManager::Collision()
{
	//先頭から最後まで繰り返し
	CTask* task = mHead.mpNext;
	while (task->mpNext) {
		//衝突処理を呼ぶ
		task->Collision();
		//次へ
		task = task->mpNext;
	}
}

*/