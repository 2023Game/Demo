#include "CPaladinDamage.h"

#define ANIMATION_FILE "res\\paladin\\Dodging.fbx.x"
#define ANIMATION_SIZE 135

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
}

void CPaladinDamage::Update()
{
	//bool flg = false;
	//if (mInput.Key('A')) {
	//	flg = true;
	//}
	//if (mInput.Key('D')) {
	//	flg = true;
	//}
	//if (mInput.Key('W')) {
	//	flg = true;
	//}
	//if (mInput.Key('S')) {
	//	flg = true;
	//}
	//if (flg)
	//{
	//	mState = CCharacter3::EState::EWALK;
	//}
	//if (mInput.Key(VK_SPACE))
	//{
	//	mState = CCharacter3::EState::EJUMP;
	//}
	//if (mInput.Key(VK_LBUTTON))
	//{
	//	mState = CCharacter3::EState::EATTACK;
	//}
}

