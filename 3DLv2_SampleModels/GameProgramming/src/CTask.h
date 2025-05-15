#ifndef CTASK_H
#define CTASK_H
#include "CTree.h"

class CTaskManager;
class CCollisionManager;
/*
�^�X�N�N���X
�^�X�N���X�g�̗v�f
*/
class CTask : public CTree {
	friend CTaskManager;
	friend CCollisionManager;
public:
	//�Փˏ���
	virtual void Collision() {}

	//�f�t�H���g�R���X�g���N�^
	CTask();
	//�f�X�g���N�^ virtual�ɂ��Ȃ��Ǝq�N���X�̃f�X�g���N�^���Ă΂�Ȃ�
	virtual ~CTask();
	//�X�V
	virtual void Update() {}
	//�`��
	virtual void Render() {}
//	bool Enable() { return mEnabled; }
//	bool Enable(bool enable) { return mEnabled = enable; }
//protected:
//	//int mPriority;	//�D��x
//	bool mEnabled;	//�L���t���O
private:
	CTask* mpNext;//���̃|�C���^
	CTask* mpPrev;//�O�̃|�C���^
	CTask* mpParent; //�e�|�C���^
};

#endif
