#include "CZombieWalk.h"
#include "CCamera.h"

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

void CZombieWalk::Collision(CCollider* m, CCollider* o)
{
	CVector adjust;
	switch (m->Type())
	{
	case CCollider::EType::ECAPSULE:
		switch (o->Type())
		{
		case CCollider::EType::ECAPSULE:
			switch (o->ParentTag())
			{
			case CCharacter3::ETag::EPLAYER:
				if (o->ParentState() == CCharacter3::EState::EATTACK
					|| o->Tag() == CCollider::ETag::ESWORD )
				{
					//if (mCntNoDame > 0) return;
					if (CCollider::CollisionCapsuleCapsule(m, o, &adjust))
					{
						if (mState != CCharacter3::EState::EHIT)
						{
							//mCntNoDame = 60;
							mState = CCharacter3::EState::EHIT;
							//ChangeAnimation(1, false, 121);
							//AnimationFrame(0.3f);
						}
						//else if (mState == CCharacter3::EState::EHIT)
						//{
						//	mState = CCharacter3::EState::EDEATH;
						//	ChangeAnimation(2, false, 178);
						//	AnimationFrame(0.3f);
						//}
					}
				}
			}
			break;
		}
	}
}
