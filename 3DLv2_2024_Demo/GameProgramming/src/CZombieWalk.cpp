#include "CZombieWalk.h"
#include "CCamera.h"

// CPaladinWalk class

#define ANIMATION_FILE "res\\WorldZombie\\Zombie_Walk.fbx.x"
#define ANIMATION_SIZE 243

CZombieWalk::CZombieWalk(CZombie* parent)
{
	mpParent = parent;
	if (mpParent->Model()->IsLoaded())
	{
		mAnimNo = mpParent->Model()->AddAnimationSet(ANIMATION_FILE) - 1;
	}
}

void CZombieWalk::Start()
{
	mpParent->ChangeAnimation(mAnimNo, true, ANIMATION_SIZE);
	mState = CCharacter3::EState::EWALK;
}

void CZombieWalk::Update()
{
	//ˆÚ“®•ûŒü‚ÖˆÚ“®
	//mTargetPosition = mTargetPosition + move * VELOCITY;
	mpParent->AddTargetPosition(mpParent->MatrixRotate().VectorZ() * VELOCITY);
}