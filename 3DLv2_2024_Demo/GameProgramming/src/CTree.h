#pragma once

class CVector;

//2���T���؂̃m�[�h
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

	CTree* mpParentNode; //�e�m�[�h
	CTree* mpLeft; //���m�[�h
	CTree* mpRight; //�E�m�[�h
	int mPriority; //�D��x
};