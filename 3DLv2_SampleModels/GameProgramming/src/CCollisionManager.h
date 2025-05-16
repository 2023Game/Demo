#ifndef CCOLLISIONMANAGER_H
#define CCOLLISIONMANAGER_H
#include <list>
#include "CTreeManager.h"
#include "CCollider.h"

//�Փˏ����͈͂�藣��Ă���R���C�_�͏Փˏ������Ȃ�
#define COLLISIONRANGE 50

class CCollisionManager : public CTreeManager
{
public:
	//�폜���X�g�̗v�f���폜����
	void Delete();
	//�폜���X�g�ɒǉ�����
	void Delete(CCollider* c);

	//�C���X�^���X�̎擾
	static CCollisionManager* Instance();
	//�Փˏ���
	void Collision(CCollider* m, CCollider* o, int low, int high);
	void Collision(CCollider* c);
	void Collision(CCollider* c, int range);
	//�`��
	void Render();
	void Render(CTree* task);
private:
	//�폜���X�g
	std::list<CCollider*> mDeleteTrees;
	//�f�t�H���g�R���X�g���N�^
	CCollisionManager() {};
	//�}�l�[�W���̃C���X�^���X
	static CCollisionManager* mpInstance;
};

#endif
