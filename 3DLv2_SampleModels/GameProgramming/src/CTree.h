#pragma once

class CVector;
class CTreeManager;

//2���T���؂̃m�[�h
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
	bool mEnabled;	//�L���t���O
	CTree* mpParentNode; //�e�m�[�h
	CTree* mpLeft; //���m�[�h
	CTree* mpRight; //�E�m�[�h
	int mPriority; //�D��x
};