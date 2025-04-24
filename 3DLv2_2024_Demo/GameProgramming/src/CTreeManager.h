#pragma once
//#include <list>
#include "CTree.h"

/// <summary>
/// 2���T���؂̊Ǘ��N���X
/// </summary>
class CTreeManager
{
public:
	/// <summary>
	/// �C���X�^���X���擾
	/// </summary>
	/// <returns>�C���X�^���X</returns>
	//static CTreeManager* Instance();
	// �C���X�^���X�̔j��
	//static void ClearInstance();

	/// <summary>
	/// �w�肵���R���C�_�[�����X�g�ɒǉ�
	/// </summary>
	/// <param name="col">�ǉ�����R���C�_�[</param>
	//void Add(CCollider* col);
	/// <summary>
	/// �w�肵���R���C�_�[�����X�g�����菜��
	/// </summary>
	/// <param name="col">��菜���R���C�_�[</param>
	//void Remove(CCollider* col);

	/// <summary>
	/// �w�肵��2�̃R���C�_�[�̏Փˏ������s��
	/// </summary>
	/// <param name="col0">�Փˏ������s���R���C�_�[ 1��</param>
	/// <param name="col1">�Փˏ������s���R���C�_�[ 2��</param>
	//void Collision(CCollider* col0, CCollider* col1);
	/// <summary>
	/// �w�肵���R���C�_�[�Ƒ��̑S�ẴR���C�_�[�Ƃ̏Փˏ������s��
	/// </summary>
	/// <param name="col">�Փˏ������s���R���C�_�[</param>
	//void Collision(CCollider* col);
	/// <summary>
	/// �S�ẴR���C�_�[�̏Փˏ������s��
	/// </summary>
	//void CollisionAll();

	//// �S�R���C�_�[��`��
	//void Render();

	//void Render(CTree* task);

	//�Q���T����

	//�Q���T���؂�add��ǉ�����
	void Add(CTree* add);
	void Add(CTree* parent, CTree* add);

	////collider�̏Փ˔�����s��
	//void Collision(CTree* collider);
	//void Collision(CTree* collider, int range);
	////o�������`����͈̔͂Ȃ�m��o�̏Փ˔�����s��
	//void Collision(CTree* m, CTree* o, int low, int high);

	//
	//CCollider* CollisionTrigger(CTree* collider);
	//CCollider* CollisionTrigger(CTree* collider, int range);
	//CCollider* CollisionTrigger(CCollider* col0, CCollider* col1);
	//CCollider* CollisionTrigger(CTree* m, CTree* o, int low, int high);

	// Remove(�폜�m�[�h)
	void Remove(CTree* remove);
	// �ő�l���ʃm�[�h�̎擾
	CTree* Max(CTree* task);
	// �ŏ��l���ʃm�[�h�̎擾
	CTree* Min(CTree* task);
	// Move(�ړ���, �ړ����j
	void Move(CTree* dest, CTree* src);
	//void UpdateAllNode(CTree* t);

	//2���T���؂̃��[�g
	CTree& Root() { return mRoot; }
	// �R���X�g���N�^
	CTreeManager();
	// �f�X�g���N�^
	~CTreeManager();
private:
	//2���T���؂̃��[�g
	CTree mRoot;
};

