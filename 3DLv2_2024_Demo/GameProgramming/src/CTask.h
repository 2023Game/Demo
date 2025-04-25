#ifndef CTASK_H
#define CTASK_H
#include "CTree.h"

class CTaskManager;
class CCollisionManager;
/*
タスククラス
タスクリストの要素
*/
class CTask : public CTree {
	friend CTaskManager;
	friend CCollisionManager;
public:
	//衝突処理
	virtual void Collision() {}

	//デフォルトコンストラクタ
	CTask();
	//デストラクタ virtualにしないと子クラスのデストラクタが呼ばれない
	virtual ~CTask();
	//更新
	virtual void Update() {}
	//描画
	virtual void Render() {}
//	bool Enable() { return mEnabled; }
//	bool Enable(bool enable) { return mEnabled = enable; }
//protected:
//	//int mPriority;	//優先度
//	bool mEnabled;	//有効フラグ
private:
	CTask* mpNext;//次のポインタ
	CTask* mpPrev;//前のポインタ
	CTask* mpParent; //親ポインタ
};

#endif
