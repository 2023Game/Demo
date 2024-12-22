#include "CPaladinDamage.h"

#define ANIMATION_FILE "res\\paladin\\Dodging.fbx.x"
#define ANIMATION_SIZE 141
#define DASSHUTSU_POINT 5 //ダメージから脱出するキー押下回数

CPaladinDamage::CPaladinDamage(CPaladin* parent)
	: mCount(0)
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
	//移動させない
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
	if (mInput.Key(VK_LBUTTON))
	{
		flg = true;
	}
	if (flg)
	{
		mCount++;
	}
	if (mCount >= DASSHUTSU_POINT)
	{
		mState = CCharacter3::EState::EATTACK;
		mCount = 0;
	}
	//if (mInput.Key(VK_SPACE))
	//{
	//	mState = CCharacter3::EState::EJUMP;
	//}

}

