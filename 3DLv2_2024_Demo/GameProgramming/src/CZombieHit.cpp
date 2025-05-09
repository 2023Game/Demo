#include "CZombieHit.h"
#include "CCamera.h"

#define ANIMATION_FILE "res\\WorldZombie\\Zombie Reaction Hit.x"
#define ANIMATION_SIZE 121

CZombieHit::CZombieHit(CZombie* parent)
{
	mpParent = parent;
	if (mpParent->Model()->IsLoaded())
	{
		mAnimNo = mpParent->Model()->AddAnimationSet(ANIMATION_FILE) - 1;
	}
}

void CZombieHit::Start()
{
	mpParent->ChangeAnimation(mAnimNo, false, ANIMATION_SIZE);
	mpParent->AnimationFrame(0.3f);
	mState = CCharacter3::EState::EHIT;
}

void CZombieHit::Update()
{
	if (mpParent->IsAnimationFinished())
	{
		//mState = CCharacter3::EState::EWALK;
		mState = CCharacter3::EState::EATTACK;
	}
}

void CZombieHit::Collision(CCollider* m, CCollider* o)
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
					&& o->Tag() == CCollider::ETag::ESWORD
					&& o->Enable() )
				{
					if (CCollider::CollisionCapsuleCapsule(m, o, &adjust))
					{
						if (mState == CCharacter3::EState::EHIT)
						{
							mState = CCharacter3::EState::EDEATH;
						}
					}
				}
			}
			break;
		}
	}
}
