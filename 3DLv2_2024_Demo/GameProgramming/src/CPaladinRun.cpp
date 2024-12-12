#include "CPaladinRun.h"
#include "CActionCamera.h"

#define ANIMATION_FILE "res\\paladin\\Paladin WProp J Nordstrom@Sword And Shield Run.fbx.x"
#define ANIMATION_SIZE 33

CPaladinRun::CPaladinRun(CPaladin* parent)
{
	mpParent = parent;
	mState = CCharacter3::EState::ERUN;
	if (mpParent->Model()->IsLoaded())
	{
		mAnimNo = mpParent->Model()->AddAnimationSet(ANIMATION_FILE) - 1;
	}
}

void CPaladinRun::Start()
{
	mpParent->ChangeAnimation(mAnimNo, true, ANIMATION_SIZE);
	mState = CCharacter3::EState::ERUN;
}

void CPaladinRun::Update()
{
	//�J�����̑O��
	CVector cameraZ = CActionCamera::Instance()->VectorZ();
	//�J�����̍�����
	CVector cameraX = CActionCamera::Instance()->VectorX();
	//�L�����N�^�̑O��
	CVector charZ = mpParent->MatrixRotate().VectorZ();
	//XZ���ʂɂ��Đ��K��
	cameraZ.Y(0.0f); cameraZ = cameraZ.Normalize();
	cameraX.Y(0.0f); cameraX = cameraX.Normalize();
	charZ.Y(0.0f); charZ = charZ.Normalize();
	//�ړ������̐ݒ�
	CVector move;
	if (mInput.Key('A')) {
		move = move + cameraX;
	}
	if (mInput.Key('D')) {
		move = move - cameraX;
	}
	if (mInput.Key('W')) {
		move = move + cameraZ;
	}
	if (mInput.Key('S')) {
		move = move - cameraZ;
	}

	//�ړ�����
	if (move.Length() > 0.0f)
	{
		//�V��
		const float MARGIN = 0.06f;
		//���K��
		move = move.Normalize();
		//�����̌����ƌ��������������ŊO��
		float cross = charZ.Cross(move).Y();
		//�����̌����ƌ��������������œ���
		float dot = charZ.Dot(move);
		//�O�ς��v���X�͍���]
		if (cross > MARGIN) {
			CVector rot = mpParent->Rotation();
			rot.Y(rot.Y() + 5.0f);
			mpParent->Rotation(rot);
		}
		//�O�ς��}�C�i�X�͉E��]
		else if (cross < -MARGIN) {
			CVector rot = mpParent->Rotation();
			rot.Y(rot.Y() - 5.0f);
			mpParent->Rotation(rot);
			//mRotation.Y(mRotation.Y() - 5.0f);
		}
		//�O��̌����������Ƃ����ς�1.0
		else if (dot < 1.0f - MARGIN) {
			CVector rot = mpParent->Rotation();
			rot.Y(rot.Y() - 5.0f);
			mpParent->Rotation(rot);
			//mRotation.Y(mRotation.Y() - 5.0f);
		}
		//�ړ������ֈړ�
		//mTargetPosition = mTargetPosition + move * VELOCITY;
		mpParent->AddTargetPosition(move * VELOCITY);
		mState = CCharacter3::EState::EWALK;
	}
	else
	{
		mState = CCharacter3::EState::EIDLE;
	}

	if (mInput.Key(VK_LBUTTON))
	{
		mState = CCharacter3::EState::EATTACK;
	}

	if (mInput.Key(VK_SPACE))
	{
		mState = CCharacter3::EState::EJUMP;
	}
	else
	{
		if (mInput.Key(VK_SHIFT))
		{
			mState = CCharacter3::EState::ERUN;
		}
		else
		{
			mState = CCharacter3::EState::EWALK;
		}
	}

}