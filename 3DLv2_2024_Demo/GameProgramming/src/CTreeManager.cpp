#include "CTreeManager.h"

//// �R���W�����}�l�[�W���̃C���X�^���X
//CTreeManager* CTreeManager::mpInstance = nullptr;
//
//// �C���X�^���X���擾
//CTreeManager* CTreeManager::Instance()
//{
//	if (mpInstance == nullptr)
//	{
//		mpInstance = new CTreeManager();
//	}
//	return mpInstance;
//}
//
//// �C���X�^���X�̔j��
//void CTreeManager::ClearInstance()
//{
//	delete mpInstance;
//	mpInstance = nullptr;
//}

// �R���X�g���N�^
CTreeManager::CTreeManager()
	: mIsShowCollider(false)
	, mpRoot(nullptr)
{
}

// �f�X�g���N�^
CTreeManager::~CTreeManager()
{
}


void CTreeManager::Add(CTree* add)
{
	if (mpRoot == nullptr)
	{
		mpRoot = add;
		add->mpParentNode = mpRoot;
	}
	else
	{
		Add(mpRoot, add);
	}
}

void CTreeManager::Add(CTree* parent, CTree* add)
{
	if (add->mPriority == parent->mPriority)
	{
		if (parent->mpLeft == nullptr)
		{
			add->mpParentNode = parent;
			parent->mpLeft = add;
		}
		else
		{
			add->mpLeft = parent->mpLeft;
			parent->mpLeft->mpParentNode = add;
			parent->mpLeft = add;
			add->mpParentNode = parent;
		}
	}
	else if (add->mPriority < parent->mPriority)
	{
		if (parent->mpLeft == nullptr)
		{
			add->mpParentNode = parent;
			parent->mpLeft = add;
		}
		else
		{
			Add(parent->mpLeft, add);
		}
	}
	else
	{
		if (parent->mpRight == nullptr)
		{
			add->mpParentNode = parent;
			parent->mpRight = add;
		}
		else
		{
			Add(parent->mpRight, add);
		}
	}
}

//int max = 0;
//int nest = 0;

/*
CCollider* CTreeManager::CollisionTrigger(CTree* m, CTree* o, int low, int high)
{
	CCollider* collider = nullptr;

	if (o == nullptr) return nullptr;
	//printf("%ld:%ld\n", m->mPriority, o->mPriority);
	//o�������ȏ�̏ꍇ
	if (low <= o->mPriority)
	{
		//o�̍��ƏՓ˔���
		collider = CollisionTrigger(m, o->mpLeft, low, high);
		if (collider != nullptr) return collider;
		//�߂��ė���o������ȉ��̏ꍇ��m�ƏՓ˔���
		if (o->mPriority <= high)
		{
			if (m != o)
				collider = CollisionTrigger((CCollider*)m, (CCollider*)o);
		}
		if (collider != nullptr) return collider;
	}
	//o������ȉ��̏ꍇ
	if (o->mPriority <= high)
	{
		//o�̉E�ƏՓ˔���
		collider = CollisionTrigger(m, o->mpRight, low, high);
	}
	if (collider != nullptr) return collider;
}

#define COLLISION_RANGE 100 //�Փ˔���͈�
CCollider* CTreeManager::CollisionTrigger(CTree* c)
{
	//���[�g�m�[�h����Փ˔���J�n
	return (CCollider*)CollisionTrigger(c, COLLISION_RANGE);
}

CCollider* CTreeManager::CollisionTrigger(CTree* c, int range)
{
	//�͈͉�����ݒ�
	int low = c->mPriority - range;
	//�͈͏����ݒ�
	int high = c->mPriority + range;

	//���[�g�m�[�h����Փ˔���J�n
	return (CCollider*)CollisionTrigger(c, mpRoot, low, high);
}
*/
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
		//�폜�m�[�h�����[�g�̏ꍇ
		if (remove->mpParentNode == remove)
		{
			//���[�g�������l�ɂ���
			//CTreeManager::Instance()->mpRoot = nullptr;
			mpRoot = nullptr;
		}
		//�폜�m�[�h�����[�g�ȊO�̏ꍇ
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
	// �e�̍X�V
	//���[�g�m�[�h�́A�e�|�C���^�����g�̃|�C���^�ɂ��Ă���
	if (remove->mpParentNode == remove)
	{
		// �폜�m�[�h�����[�g�̏ꍇ
		//���[�g���ړ��m�[�h�ɂ��āA�ړ��m�[�h�̐e�����g�̃|�C���^�ɂ���
		//CTreeManager::Instance()->mpRoot = move;
		mpRoot = move;
		move->mpParentNode = move;
	}
	else
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
	}

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

void CTreeManager::Render()
{
	Render(mpRoot);
}

void CTreeManager::Render(CTree* task)
{
	if (task == nullptr) return;
	Render(task->mpLeft);
	((CTask*)task)->Render();
	Render(task->mpRight);
}

//void CTreeManager::UpdateAllNode(CTree* t)
//{
//	if (t->mpLeft)
//		UpdateAllNode(t->mpLeft);
//	((CCollider*)t)->Update();
//	((CCollider*)t)->UpdateCol();
//	if (t->mpRight)
//		UpdateAllNode(t->mpRight);
//}