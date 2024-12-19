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
	//移動方向へ移動
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
				switch (o->Tag())
				{
				case CCollider::ETag::ESWORD:
					if (o->ParentState() == CCharacter3::EState::EATTACK)
					{
						if (CCollider::CollisionCapsuleCapsule(m, o, &adjust))
						{
							// プレイヤーの攻撃が当たっている
							if (mState != CCharacter3::EState::EHIT)
							{
								mState = CCharacter3::EState::EHIT;
							}
						}
					}
					break;
				case CCollider::ETag::EBODY:
					if (CCollider::CollisionCapsuleCapsule(m, o, &adjust))
					{
						// プレイヤーに当たっていると、攻撃する
						mState = CCharacter3::EState::EATTACK;
						mpParent->Target(o->Parent());
					}
					break;
				}
			}
			break;
		}
	}
}
