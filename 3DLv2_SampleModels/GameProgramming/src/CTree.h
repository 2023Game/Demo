#pragma once

class CVector;
class CTreeManager;

//2分探索木のノード
class CTree
{
	friend CTreeManager;
public:
	CTree()
		: mpParentNode(nullptr)
		, mpLeft(nullptr)
		, mpRight(nullptr)
		, mPriority(0)
		, mEnabled(true)
	{}

	void Priority(const CVector& v);
	void Priority(const CVector& v, const CVector& v2);
	void Priority(const CVector& v, const CVector& v2, const CVector& v3);

	bool Enable() { return mEnabled; }
	bool Enable(bool enable) { return mEnabled = enable; }

	CTree* Left() { return mpLeft; }
	CTree* Right() { return mpRight; }
protected:
	bool mEnabled;	//有効フラグ
	CTree* mpParentNode; //親ノード
	CTree* mpLeft; //左ノード
	CTree* mpRight; //右ノード
	int mPriority; //優先度
};