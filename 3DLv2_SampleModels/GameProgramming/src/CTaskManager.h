#ifndef CTASKMANAGER_H
#define CTASKMANAGER_H
//�^�X�N�N���X�̃C���N���[�h
#include <list>
#include "CTask.h"
#include "CTreeManager.h"

#define TASK_RANGE 100

class CTaskManager : public CTreeManager
{
public:
	//�C���X�^���X�̎擾
	static CTaskManager* Instance();
	//�폜���X�g�̃^�X�N���폜
	void Delete();
	//�폜���X�g�ɒǉ�
	void Delete(CTask* task);
	//�f�X�g���N�^
	virtual ~CTaskManager();
	//�X�V
	void Update();
	//�Փ�
	void Collision();
	//�`��
	void Render();
	void RenderUI();
private:
	//�X�V
	void Update(CTree* task);
	//�Փ�
	void Collision(CTree* task);
	//�`��
	void Render(CTree* task);
	void RenderUI(CTree* task);
	//�폜���X�g
	std::list<CTask*> mDeleteTrees;
	//�f�t�H���g�R���X�g���N�^
	CTaskManager();
	//�^�X�N�}�l�[�W���̃C���X�^���X
	static CTaskManager* mpInstance;
};

/*
�^�X�N�}�l�[�W��
�^�X�N���X�g�̊Ǘ�

class CTaskManager {
public:
	void Collision();
	//�C���X�^���X�̎擾
	static CTaskManager* Instance();
	//�^�X�N�̍폜
	void Delete();
	//���X�g����폜
	//Remove(�^�X�N�̃|�C���^)
	void Remove(CTask* task);
	//�f�X�g���N�^
	virtual ~CTaskManager();
	//���X�g�ɒǉ�
	//Add(�^�X�N�̃|�C���^)
	void Add(CTask* addTask);
	//�X�V
	void Update();
	//�`��
	void Render();
protected:
	//�f�t�H���g�R���X�g���N�^
	CTaskManager();
	CTask mHead;//�擪�^�X�N
	CTask mTail;//�ŏI�^�X�N
private:
	//�^�X�N�}�l�[�W���̃C���X�^���X
	static CTaskManager* mpInstance;
};
*/

#endif
