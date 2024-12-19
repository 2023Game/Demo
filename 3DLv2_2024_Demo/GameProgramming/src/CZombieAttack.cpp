#include "CZombieAttack.h"
#include "CCamera.h"

#define ANIMATION_FILE "res\\WorldZombie\\Zombie Neck Bite.fbx.x"
#define ANIMATION_SIZE 251

CZombieAttack::CZombieAttack(CZombie* parent)
	: mpTarget(nullptr)
{
	mpParent = parent;
	if (mpParent->Model()->IsLoaded())
	{
		mAnimNo = mpParent->Model()->AddAnimationSet(ANIMATION_FILE) - 1;
	}
}

void CZombieAttack::Start()
{
	mpParent->ChangeAnimation(mAnimNo, true, ANIMATION_SIZE);
	//mpParent->AnimationFrame(0.3f);
	mState = CCharacter3::EState::EATTACK;
}

void CZombieAttack::Update()
{
	if (mpTarget != nullptr)
	{
		mpParent->TargetPosition(mpTarget->Position());

		// プレイヤーの方へ向かせる
		CVector toPlayer = mpTarget->Position() - mpParent->Position();
		float dot = toPlayer.Dot(mpParent->MatrixRotate().VectorX());
		if (dot > 0.0f)
		{
			CVector y = mpParent->Rotation();
			y.Y(y.Y() + 1.1f);
			mpParent->Rotation(y);
		}
		else if (dot < 0.0f)
		{
			CVector y = mpParent->Rotation();
			y.Y(y.Y() - 1.1f);
			mpParent->Rotation(y);
		}
	}

	if (mpParent->IsAnimationFinished())
	{
		//mState = CCharacter3::EState::EWALK;
	}
}

void CZombieAttack::Collision(CCollider* m, CCollider* o)
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

				switch (o->Tag())
				{
				case CCollider::ETag::ESWORD:
					if (o->ParentState() == CCharacter3::EState::EATTACK)
					{
						if (CCollider::CollisionCapsuleCapsule(m, o, &adjust))
						{
							mState = CCharacter3::EState::EWALK;
						}
					}
					break;
				case CCollider::ETag::EBODY:
					// プレイヤーのポインタ取得
					if (CCollider::CollisionCapsuleCapsule(m, o, &adjust))
					{
						mpTarget = o->Parent();
					}
					break;
				}
			}
			break;
		}
	}
}
