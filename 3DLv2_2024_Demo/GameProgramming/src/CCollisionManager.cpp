#include "CCollisionManager.h"
#include "CCollider.h"


//�}�l�[�W���̃C���X�^���X
CCollisionManager* CCollisionManager::mpInstance = nullptr;
//�C���X�^���X�̎擾
CCollisionManager* CCollisionManager::Instance()
{
	if (mpInstance == nullptr)
	{
		mpInstance = new CCollisionManager();
	}
	return mpInstance;
}

void CCollisionManager::Collision(CCollider* m, CCollider* o, int low, int high)
{
	if (o == nullptr) return;

	//o�������ȏ�̏ꍇ
	if (low <= o->mPriority)
	{
		//o�̍��ƏՓ˔���
		Collision(m, (CCollider*)o->mpLeft, low, high);
		//�߂��ė���o������ȉ��̏ꍇ��m�ƏՓ˔���
		if (o->mPriority <= high)
		{
			if (m != o)
				m->mpParent->Collision((CCollider*)m, (CCollider*)o);
		}
	}
	//o������ȉ��̏ꍇ
	if (o->mPriority <= high)
	{
		//o�̉E�ƏՓ˔���
		Collision(m, (CCollider*)o->mpRight, low, high);
	}
}


void CCollisionManager::Collision(CCollider* c)
{
	//���[�g�m�[�h����Փ˔���J�n
	Collision(c, COLLISIONRANGE);
}

void CCollisionManager::Collision(CCollider* c, int range)
{
	//�͈͉�����ݒ�
	int low = c->mPriority - range;
	//�͈͏����ݒ�
	int high = c->mPriority + range;

	//���[�g�m�[�h����Փ˔���J�n
	Collision(c, (CCollider*)mpRoot, low, high);
}


/*
void CCollisionManager::Collision(CCollider* m, CTask* o, int low, int high)
{
	if (o == nullptr) return;
	if (low <= o->mPriority)
	{
		Collision(m, o->mpPrev, low, high);
		if (o->mPriority <= high)
		{
			if (m->mpParent && m != o)
				m->mpParent->Collision(m, (CCollider*)o);
		}
	}
	if (o->mPriority <= high)
	{
		Collision(m, o->mpNext, low, high);
	}
}

void CCollisionManager::Collision(CCollider* c, int range)
{
	int low = c->mPriority - range;
	int high = c->mPriority + range;

	Collision(c, mRoot.mpPrev, low, high);
}

void CCollisionManager::Collision()
{
	////���݈ʒu��擪�ɂ���
	//CCollider* task = (CCollider*)mHead.mpNext;
	////�Ō�܂ł�����I������
	//while (task->mpNext) {
	//	//���݈ʒu�̎������߂�
	//	CCollider* next = (CCollider*)task->mpNext;
	//	//����0�ɂȂ�����I��
	//	while (next->mpNext) {
	//		//�e�̏Փˏ������Ăяo��
	//		//�����̏Փˏ���
	//		if (task->mpParent)
	//			task->mpParent->Collision(task, next);
	//		//����̏Փˏ���
	//		if (next->mpParent)
	//			next->mpParent->Collision(next, task);
	//		//�������߂�
	//		next = (CCollider*)next->mpNext;
	//	}
	//	//���݈ʒu�����ɂ���
	//	task = (CCollider*)task->mpNext;
	//}
}
*/


/*
void CCollisionManager::Add(CTask* add)
{
	if (mRoot.mpPrev == nullptr)
	{
		mRoot.mpPrev = add;
		add->mpParent = &mRoot;
	}
	else
	{
		Add(mRoot.mpPrev, add);
	}
}

void CCollisionManager::Add(CTask* parent, CTask* add)
{
	if (add->mPriority == parent->mPriority)
	{
		if (parent->mpPrev == nullptr)
		{
			add->mpParent = parent;
			parent->mpPrev = add;
		}
		else
		{
			add->mpPrev = parent->mpPrev;
			parent->mpPrev->mpParent = add;
			parent->mpPrev = add;
			add->mpParent = parent;
		}
	}
	else if (add->mPriority < parent->mPriority)
	{
		if (parent->mpPrev == nullptr)
		{
			add->mpParent = parent;
			parent->mpPrev = add;
		}
		else
		{
			Add(parent->mpPrev, add);
		}
	}
	else
	{
		if (parent->mpNext == nullptr)
		{
			add->mpParent = parent;
			parent->mpNext = add;
		}
		else
		{
			Add(parent->mpNext, add);
		}
	}
}

void CCollisionManager::Remove(CTask* remove)
{
	if (remove->mpPrev != nullptr)
	{
		CTask* move = Max(remove->mpPrev);
		if (move != remove->mpPrev)
		{
			move->mpParent->mpNext = move->mpPrev;
			Move(remove, move);
		}
		else
		{
			remove->mpPrev = move->mpPrev;
			Move(remove, move);
		}
	}
	else if (remove->mpNext != nullptr)
	{
		CTask* move = Min(remove->mpNext);

		if (move != remove->mpNext)
		{
			move->mpParent->mpPrev = move->mpNext;
			Move(remove, move);
		}
		else
		{
			remove->mpNext = move->mpNext;
			Move(remove, move);
		}
	}
	else
	{
		//�폜�m�[�h�����[�g�̏ꍇ
		if (remove->mpParent == remove)
		{
			//���[�g�������l�ɂ���
			CCollisionManager::Instance()->mRoot.mpPrev = nullptr;
		}
		else
		{
			if (remove->mpParent != nullptr)
			{
				if (remove->mpParent->mpPrev == remove)
					remove->mpParent->mpPrev = nullptr;
				if (remove->mpParent->mpNext == remove)
					remove->mpParent->mpNext = nullptr;
			}
		}
	}
	remove->mpParent = remove->mpPrev = remove->mpNext = nullptr;
}

CTask* CCollisionManager::Max(CTask* task)
{
	if (task->mpNext == nullptr)
		return task;
	return Max(task->mpNext);
}

CTask* CCollisionManager::Min(CTask* task)
{
	if (task->mpPrev == nullptr)
		return task;
	return Min(task->mpPrev);
}

void CCollisionManager::Move(CTask* dest, CTask* src)
{
	if (dest->mpParent->mpPrev == dest)
		dest->mpParent->mpPrev = src;
	if (dest->mpParent->mpNext == dest)
		dest->mpParent->mpNext = src;
	src->mpParent = dest->mpParent;

	if (dest->mpPrev != nullptr)
	{
		dest->mpPrev->mpParent = src;
	}
	src->mpPrev = dest->mpPrev;

	if (dest->mpNext != nullptr)
	{
		dest->mpNext->mpParent = src;
	}
	src->mpNext = dest->mpNext;
}

void CCollisionManager::Render()
{
	Render(mRoot.mpPrev);
}

void CCollisionManager::Render(CTask* task)
{
	if (task == nullptr) return;
	Render(task->mpPrev);
	task->Render();
	Render(task->mpNext);
}
*/