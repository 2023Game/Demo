#ifndef CCHARACTER3_H
#define CCHARACTER3_H
//�ϊ��s��N���X�̃C���N���[�h
#include "CTransform.h"
//���f���N���X�̃C���N���[�h
#include "CModel.h"
#include "CTask.h"

#include <memory>

//��ԃN���X
class CState;

//�R���C�_�N���X�̐錾
class CCollider;

/*
�L�����N�^�[�N���X
�Q�[���L�����N�^�̊�{�I�ȋ@�\���`����
*/
class CCharacter3 : public CTransform, public CTask {
public:
	enum class ETag
	{
		EZERO,
		EPLAYER,
		EENEMY,
	};
	enum class EState
	{
		EZERO,
		EIDLE,
		EWALK,
		ERUN,
		EATTACK,
		EHIT,
		EDEATH,
		EJUMP,
		EDAMAGE,
	};
	//�Փˏ���
	virtual void Collision(CCollider* m, CCollider* o) {}
	//�R���X�g���N�^
	CCharacter3();
	//�R���X�g���N�^
	CCharacter3(int priority, ETag tag);
	CCharacter3(ETag tag);
	//�f�X�g���N�^
	~CCharacter3();
	//���f���̐ݒ�
	//Model(���f���N���X�̃|�C���^)
	void Model(CModel* m);
	//�`�揈��
	void Render();
	void Tag(ETag t)
	{
		mTag = t;
	}
	ETag Tag()
	{
		return mTag;
	}
	EState State()
	{
		return mState;
	}
	EState State(EState state)
	{
		return mState = state;
	}
	void AddTargetPosition(const CVector& v)
	{
		mTargetPosition = mTargetPosition + v;
	}
	void TargetPosition(const CVector& v)
	{
		mTargetPosition = v;
	}
	CVector TargetPosition()
	{
		return mTargetPosition;
	}
	void VelocityG(float v)
	{
		mVelocityG = v;
	}
	const CVector& Velocity()
	{
		return mVelocity;
	}
	void Speed(float speed)
	{
		mSpeed = speed;
	}
	float Speed()
	{
		return mSpeed;
	}
	std::shared_ptr<CState> PState()
	{
		return mpState;
	}
	const CVector& Adjust()
	{
		return mAdjust;
	}
protected:
	std::shared_ptr<CState> mpState;
	CVector mAdjust;
	bool mGrounded;
	CVector mTargetPosition;
	float mGravity;
	float mVelocityG;
	float mSpeed;
	CVector mVelocity;

	ETag mTag;
	EState mState;
	CModel* mpModel; //���f���̃|�C���^
};

#endif

