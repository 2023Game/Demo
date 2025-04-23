#ifndef CCOLLISIONMANAGER_H
#define CCOLLISIONMANAGER_H

//#include "CTaskManager.h"
#include "CTreeManager.h"
#include "CCollider.h"

//�Փˏ����͈͂�藣��Ă���R���C�_�͏Փˏ������Ȃ�
#define COLLISIONRANGE 30

class CCollisionManager : public CTreeManager  //: public CTaskManager
{
public:
	//�C���X�^���X�̎擾
	static CCollisionManager* Instance();
	void Collision(CCollider* m, CCollider* o, int low, int high);
	void Collision(CCollider* c);
	void Collision(CCollider* c, int range);
private:
	//�f�t�H���g�R���X�g���N�^
	CCollisionManager() {};
	//�}�l�[�W���̃C���X�^���X
	static CCollisionManager* mpInstance;
};

/*
class CCollisionManager //: public CTaskManager
{
public:
	//���X�g�ɒǉ�
	//Add(�^�X�N�̃|�C���^)
	void Add(CTask* add);
	void Add(CTask* parent, CTask* add);

	//���X�g����폜
	//Remove(�^�X�N�̃|�C���^)
	void Remove(CTask* remove);
	//�ő�l�̃m�[�h�̎擾
	CTask* Max(CTask* task);
	//�ŏ��l�̃m�[�h�̎擾
	CTask* Min(CTask* task);
	//src��dest�ֈړ�����
	void Move(CTask* dest, CTask* src);

	//�`��
	void Render();
	void Render(CTask* task);

	//low�`high�̊Ԃł���ΏՓˏ������s��
	void Collision(CCollider* m, CTask* o, int low, int high);
	//�Փˏ���
	//Collision(�R���C�_, �͈�)
	//�R���C�_�̗D��x+�͈́`�D��x-�͈͂܂ł̃R���C�_�ƏՓ˔�������s����
	void Collision(CCollider* c, int range);
	//�Փˏ���
	void Collision();
	//�C���X�^���X�̎擾
	static CCollisionManager* Instance();
private:
	//�f�t�H���g�R���X�g���N�^
	CCollisionManager() {};
	CTask mRoot;//�擪�^�X�N
	//�}�l�[�W���̃C���X�^���X
	static CCollisionManager* mpInstance;
};
*/

#endif
