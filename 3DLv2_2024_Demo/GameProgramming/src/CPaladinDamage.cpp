#include "CPaladinDamage.h"

#define ANIMATION_FILE "res\\paladin\\Dodging.fbx.x"
#define ANIMATION_SIZE 141

CPaladinDamage::CPaladinDamage(CPaladin* parent)
{
	mpParent = parent;
	if (mpParent->Model()->IsLoaded())
	{
		mAnimNo = mpParent->Model()->AddAnimationSet(ANIMATION_FILE) - 1;
	}
}

void CPaladinDamage::Start()
{
	mpParent->ChangeAnimation(mAnimNo, true, ANIMATION_SIZE);
	mState = CCharacter3::EState::EDAMAGE;
	mCount = 0;
}

void CPaladinDamage::Update()
{
	//ˆÚ“®‚³‚¹‚È‚¢
	CVector adjust = mpParent->Adjust();
	adjust.Y(0.0f);
	adjust = adjust * -1.0f;
	mpParent->AddTargetPosition(adjust);

	bool flg = false;
	if (mInput.KeyDown('A')) {
		flg = true;
	}
	if (mInput.KeyDown('D')) {
		flg = true;
	}
	if (mInput.KeyDown('W')) {
		flg = true;
	}
	if (mInput.KeyDown('S')) {
		flg = true;
	}
	if (flg)
	{
		mCount++;
	}
	if (mCount > 5)
	{
		mState = CCharacter3::EState::EATTACK;
		mCount = 0;
	}
	//if (mInput.Key(VK_SPACE))
	//{
	//	mState = CCharacter3::EState::EJUMP;
	//}
	//if (mInput.Key(VK_LBUTTON))
	//{
	//	mState = CCharacter3::EState::EATTACK;
	//}
}

