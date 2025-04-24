#pragma once

class CVector;

//2分探索木のノード
class CTree
{
public:
	CTree()
		: mpParentNode(nullptr)
		, mpLeft(nullptr)
		, mpRight(nullptr)
		, mPriority(0)
	{}

	void Priority(const CVector& v);
	void Priority(const CVector& v, const CVector& v2);
	void Priority(const CVector& v, const CVector& v2, const CVector& v3);

	CTree* mpParentNode; //親ノード
	CTree* mpLeft; //左ノード
	CTree* mpRight; //右ノード
	int mPriority; //優先度
};