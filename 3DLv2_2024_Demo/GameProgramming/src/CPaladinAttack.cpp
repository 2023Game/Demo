#include "CPaladinAttack.h"

#define ANIMATION_FILE "res\\paladin\\Sword And Shield Slash.x"
#define ANIMATION_SIZE 53

CPaladinAttack::CPaladinAttack(CPaladin* parent)
{
	mpParent = parent;
	if (mpParent->Model()->IsLoaded())
	{
		mAnimNo = mpParent->Model()->AddAnimationSet(ANIMATION_FILE) - 1;
	}
}

void CPaladinAttack::Start()
{
	mpParent->ChangeAnimation(mAnimNo, false, ANIMATION_SIZE);
	mState = CCharacter3::EState::EATTACK;
}

void CPaladinAttack::Update()
{
	//ˆÚ“®‚³‚¹‚È‚¢
	CVector adjust = mpParent->Adjust();
	adjust.Y(0.0f);
	adjust = adjust * -1.0f;
	mpParent->AddTargetPosition(adjust);

	if (mpParent->IsAnimationFinished())
	{
		mState = CCharacter3::EState::EIDLE;
	}
}
