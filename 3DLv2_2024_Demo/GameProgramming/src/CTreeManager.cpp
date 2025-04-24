#include "CTreeManager.h"

// �R���X�g���N�^
CTreeManager::CTreeManager()
{
	mRoot.mPriority = -1;
}

// �f�X�g���N�^
CTreeManager::~CTreeManager()
{
}

void CTreeManager::Add(CTree* add)
{
	// ���[�g����ǉ��J�n
	Add(&mRoot, add);
}

void CTreeManager::Add(CTree* parent, CTree* add)
{
	//�D��x�����@���֒ǉ�
	if (add->mPriority == parent->mPriority)
	{
		if (parent->mpLeft == nullptr)
		{
			// �����������́A���֒ǉ�
			add->mpParentNode = parent;
			parent->mpLeft = add;
		}
		else
		{
			// �������鎞�́A�e�ƍ��̊Ԃ֒ǉ�
			add->mpLeft = parent->mpLeft;
			parent->mpLeft->mpParentNode = add;
			parent->mpLeft = add;
			add->mpParentNode = parent;
		}
	}
	//�D��x�Ⴂ�@���֒ǉ�
	else if (add->mPriority < parent->mPriority)
	{
		if (parent->mpLeft == nullptr)
		{
			// �����������́A���֒ǉ�
			add->mpParentNode = parent;
			parent->mpLeft = add;
		}
		else
		{
			// �������鎞�́A���ֈړ�
			Add(parent->mpLeft, add);
		}
	}
	//�D��x�����@�E�֒ǉ�
	else
	{
		if (parent->mpRight == nullptr)
		{
			// �E���������́A�E�֒ǉ�
			add->mpParentNode = parent;
			parent->mpRight = add;
		}
		else
		{
			// �E������Ƃ��́A�E�ֈړ�
			Add(parent->mpRight, add);
		}
	}
}

void CTreeManager::Remove(CTree* remove)
{
	//�������鎞�́A���̍ő�l�m�[�h�Ɠ���
	if (remove->mpLeft != nullptr)
	{
		//���m�[�h���̍ő�l�m�[�h��Max�Ŏ擾
		CTree* move = Max(remove->mpLeft);
		//�ő�l��������
		if (move == remove->mpLeft)
		{
			// Move���\�b�h�ݒ�p�ɏ���
			remove->mpLeft = move->mpLeft;
		}
		//�ő�l�����ł͂Ȃ��ꍇ
		else
		{
			//�ő�l�̐e�m�[�h�̉E�ɁA�ő�l�m�[�h�̍����Γ�
			move->mpParentNode->mpRight = move->mpLeft;
			//�ő�l�m�[�h�̍�������ꍇ
			if (move->mpLeft != nullptr)
				//�ő�l�m�[�h�̍��̐e�ɁA�ő�l�m�[�h�̐e����
				move->mpLeft->mpParentNode = move->mpParentNode;
		}
		//remove�̈ʒu�ɁAmove���ړ�������
		Move(remove, move);
	}
	//�����Ȃ����́A�E�̍ŏ��l�m�[�h�Ɠ���
	else if (remove->mpRight != nullptr)
	{
		//�E�m�[�h�̍ŏ��l��Min�Ŏ擾
		CTree* move = Min(remove->mpRight);
		//�ŏ��l�������E�̏ꍇ
		if (move == remove->mpRight)
		{
			// Move���\�b�h�ݒ�p�ɏ���
			remove->mpRight = move->mpRight;
		}
		//�ŏ��l�������E�łȂ��ꍇ
		else
		{
			//�ŏ��l�̐e�m�[�h�̍��ɁA�ŏ��l�m�[�h�̉E����
			move->mpParentNode->mpLeft = move->mpRight;
			//�ŏ��l�m�[�h�̉E������ꍇ
			if (move->mpRight != nullptr)
				//�ŏ��l�m�[�h�̉E�̐e�ɁA�ŏ��l�m�[�h�̐e����
				move->mpRight->mpParentNode = move->mpParentNode;
		}
		//remove�̈ʒu�ɁAmove���ړ�������
		Move(remove, move);
	}
	//�q�m�[�h���Ȃ���
	else
	{

		if (remove->mpParentNode != nullptr)
		{
			//�폜�m�[�h���e�m�[�h�̍��̏ꍇ
			if (remove->mpParentNode->mpLeft == remove)
				//�폜�m�[�h�̐e�m�[�h�̍�������������
				remove->mpParentNode->mpLeft = nullptr;
			//�폜�m�[�h���e�m�[�h�̉E�̏ꍇ
			if (remove->mpParentNode->mpRight == remove)
				//�폜�m�[�h�̐e�m�[�h�̉E������������
				remove->mpParentNode->mpRight = nullptr;
		}

	}
	//�폜�m�[�h�̐e�A���A�E������������
	remove->mpParentNode = remove->mpLeft = remove->mpRight = nullptr;
}

CTree* CTreeManager::Max(CTree* task)
{
	//��ԉE�ɂ���m�[�h���ő�l
	//��ԉE�ɂ���m�[�h�̉E��nullptr
	if (task->mpRight == nullptr)
		return task;
	return Max(task->mpRight);
}

CTree* CTreeManager::Min(CTree* task)
{
	//��ԍ��ɂ���m�[�h���ŏ��l
	//��ԍ��ɂ���m�[�h�̍���nullptr
	if (task->mpLeft == nullptr)
		return task;
	return Min(task->mpLeft);
}

void CTreeManager::Move(CTree* remove, CTree* move)
{
	//�폜�m�[�h�̐e�̍����A�폜�m�[�h�̏ꍇ
	if (remove->mpParentNode->mpLeft == remove)
		//�폜�m�[�h�̐e�̍����ړ��m�[�h�ɂ���
		remove->mpParentNode->mpLeft = move;
	//�폜�m�[�h�̐e�̉E���A�폜�m�[�h�̏ꍇ
	if (remove->mpParentNode->mpRight == remove)
		//�폜�m�[�h�̐e�̉E���ړ��m�[�h�ɂ���
		remove->mpParentNode->mpRight = move;
	//�ړ��m�[�h�̐e�ɁA�폜�m�[�h�̐e����
	move->mpParentNode = remove->mpParentNode;

	// ���̍X�V
	// �폜�m�[�h�ɍ��������
	if (remove->mpLeft != nullptr)
	{
		//�폜�m�[�h�̍��̐e�ɁA�ړ��m�[�h����
		remove->mpLeft->mpParentNode = move;
	}
	//�ړ��m�[�h�̍��ɍ폜�m�[�h�̍�����
	move->mpLeft = remove->mpLeft;

	// �E�̍X�V
	// �폜�m�[�h�ɉE�������
	if (remove->mpRight != nullptr)
	{
		//�폜�m�[�h�̉E�̐e�ɁA�ړ��m�[�h����
		remove->mpRight->mpParentNode = move;
	}
	//�ړ��m�[�h�̉E�ɍ폜�m�[�h�̉E����
	move->mpRight = remove->mpRight;
}
