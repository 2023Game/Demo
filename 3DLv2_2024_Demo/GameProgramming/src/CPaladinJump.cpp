#include "CPaladinJump.h"
#include "CCamera.h"

#define ANIMATION_FILE "res\\paladin\\Sword And Shield Jump.x"
#define ANIMATION_SIZE 51

CPaladinJump::CPaladinJump(CPaladin* parent)
{
	mpParent = parent;
	if (mpParent->Model()->IsLoaded())
	{
		mAnimNo = mpParent->Model()->AddAnimationSet(ANIMATION_FILE) - 1;
	}
}

void CPaladinJump::Start()
{
	mpParent->ChangeAnimation(mAnimNo, false, ANIMATION_SIZE);
	mState = CCharacter3::EState::EJUMP;
	mpParent->VelocityG(2.0);
	mpParent->Position(mpParent->Position() + CVector(0.0f, 0.5f, 0.0f));
	mVelocity = mpParent->Velocity();
	mVelocity.Y(0.0f);
}

void CPaladinJump::Update()
{
	if (mpParent->IsAnimationFinished())
	{
		mState = CCharacter3::EState::EIDLE;
	}
	mpParent->Position(mpParent->Position() + mVelocity);

	//CCamera::Instance()->TargetPosition(mpParent->Position() + CVector(0.0f, 2.0f, 0.0f));
}
