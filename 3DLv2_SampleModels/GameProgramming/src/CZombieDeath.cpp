#include "CZombieDeath.h"
#include "CCamera.h"
#include "CTaskManager.h"

#define ANIMATION_FILE "res\\WorldZombie\\Zombie Death.x"
#define ANIMATION_SIZE 178

CZombieDeath::CZombieDeath(CZombie* parent)
{
	mpParent = parent;
	if (mpParent->Model()->IsLoaded())
	{
		mAnimNo = mpParent->Model()->AddAnimationSet(ANIMATION_FILE) - 1;
	}
}

void CZombieDeath::Start()
{
	mpParent->ChangeAnimation(mAnimNo, false, ANIMATION_SIZE);
	mpParent->AnimationFrame(0.3f);
	mState = CCharacter3::EState::EDEATH;
}

void CZombieDeath::Update()
{
	if (mpParent->IsAnimationFinished())
	{
		//íœ‚·‚é
		CTaskManager::Instance()->Delete(mpParent);
	}
}


