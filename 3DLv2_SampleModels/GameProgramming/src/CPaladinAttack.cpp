#include "CPaladinAttack.h"

#define ANIMATION_FILE "res\\paladin\\Sword And Shield Slash.x"
#define ANIMATION_SIZE 53

CPaladinAttack::CPaladinAttack(CPaladin* parent)
{
	mpParent =
		parent;
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
	//移動させない
	CVector adjust = mpParent->Adjust();
	adjust.Y(0.0f);
	adjust = adjust * -1.0f;
	mpParent->AddTargetPosition(adjust);

	//ソードの有効範囲設定
	float animatioFrame = mpParent->AnimationFrame();

	if (0.5f < animatioFrame)
		mpParent->ColSword().Enable(false);
	else if (0.41f < animatioFrame)
	{
		mpParent->ColSword().Enable(true);
		mpParent->AnimationFrame(animatioFrame - 0.01);
	}

	if (mpParent->IsAnimationFinished())
	{
		mState = CCharacter3::EState::EIDLE;
	}
}
