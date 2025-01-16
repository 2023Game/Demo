#include "CZombieAttack.h"
#include "CCamera.h"

#define ANIMATION_FILE "res\\WorldZombie\\Zombie Neck Bite.fbx.x"
#define ANIMATION_SIZE 251
#define TURN_ROT 4.0f // 回転速度

CZombieAttack::CZombieAttack(CZombie* parent)
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
	mpParent->AnimationFrame(0.125f);
	mState = CCharacter3::EState::EATTACK;
}

void CZombieAttack::Update()
{
	if (mpParent->Target() != nullptr)
	{
		mpParent->TargetPosition(mpParent->Target()->Position());

		// プレイヤーの方へ向かせる
		CVector toPlayer = mpParent->Target()->Position() - mpParent->Position();
		CVector cross = toPlayer.Cross(mpParent->MatrixRotate().VectorZ());
		if (cross.Y() > 0.0f)
		{
			CVector y = mpParent->Rotation();
			y.Y(y.Y() - TURN_ROT);
			mpParent->Rotation(y);
		}
		else
		{
			CVector y = mpParent->Rotation();
			y.Y(y.Y() + TURN_ROT);
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
				case CCollider::ETag::EBODY:
					if (CCollider::CollisionCapsuleCapsule(m, o, &adjust))
					{
						if (o->ParentState() == CCharacter3::EState::EATTACK)
						{
							//mState = CCharacter3::EState::EHIT;
						}
						else
						{
							// プレイヤーにめり込まない
							mpParent->Position(mpParent->Position() + adjust);
							o->Parent()->PState()->State(CCharacter3::EState::EDAMAGE);
						}
					}
					break;
				case CCollider::ETag::ESWORD:
					if (o->Enable())
					{
						if (CCollider::CollisionCapsuleCapsule(m, o, &adjust))
						{
							// プレイヤーの攻撃が当たっている
							if (mState != CCharacter3::EState::EHIT)
							{
								mState = CCharacter3::EState::EHIT;
								mpParent->Target(o->Parent());
							}
						}
					}
					break;
				}
			}
			break;
		}
	}
}
