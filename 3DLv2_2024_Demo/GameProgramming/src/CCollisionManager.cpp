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
	Collision(c, (CCollider*)&Root(), low, high);
}

void CCollisionManager::Render()
{
	Render(Root().Right());
}

void CCollisionManager::Render(CTree* task)
{
	if (task == nullptr) return;
	Render(task->Left());
	((CTask*)task)->Render();
	Render(task->Right());
}

void CCollisionManager::Delete()
{
	for (auto tree : mDeleteTrees)
		delete tree;
	mDeleteTrees.clear();
}

void CCollisionManager::Delete(CCollider* c)
{
	mDeleteTrees.push_back(c);
}
