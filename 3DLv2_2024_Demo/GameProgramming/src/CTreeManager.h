#pragma once
#include "CTree.h"

/// <summary>
/// 2���T���؂̊Ǘ��N���X
/// </summary>
class CTreeManager
{
public:
	//�Q���T���؂�add��ǉ�����
	void Add(CTree* add);

	// Remove(�폜�m�[�h)
	void Remove(CTree* remove);

	//2���T���؂̃��[�g�擾
	CTree& Root() { return mRoot; }
	// �R���X�g���N�^
	CTreeManager();
	// �f�X�g���N�^
	~CTreeManager();
private:
	void Add(CTree* parent, CTree* add);
	// �ő�l���ʃm�[�h�̎擾
	CTree* Max(CTree* task);
	// �ŏ��l���ʃm�[�h�̎擾
	CTree* Min(CTree* task);
	// Move(�ړ���, �ړ����j
	void Move(CTree* dest, CTree* src);

	//2���T���؂̃��[�g
	CTree mRoot;
};
