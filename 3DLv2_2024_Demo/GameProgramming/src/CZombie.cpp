#include "CZombie.h"
#include "CCollisionManager.h"
#include "CZombieWalk.h"
#include "CZombieHit.h"



#define MODEL_PATH "res\\WorldZombie\\world_war_zombie.x"
//追加のアニメーションセット
#define ANIMATION_WALK "res\\WorldZombie\\Zombie_Walk.fbx.x"
#define ANIMATION_HIT "res\\WorldZombie\\Zombie Reaction Hit.x"
#define ANIMATION_DEATH "res\\WorldZombie\\Zombie Death.x"

CModelX CZombie::sModel;

CZombie::CZombie()
	: CXCharacter(CCharacter3::ETag::EENEMY)
	, mColBody(
		this, 
		nullptr, 
		CVector(0.0f, -90.0f, 0.0f),
		CVector(0.0f, 70.0f, 0.0f), 
		0.15f)
	, mCntNoDame(0)
{
	if (sModel.IsLoaded() == false)
	{
		sModel.Load(MODEL_PATH);
		//アニメーションの追加
		sModel.AddAnimationSet(ANIMATION_WALK); //0
		//sModel.AddAnimationSet(ANIMATION_HIT); //1
		//sModel.AddAnimationSet(ANIMATION_DEATH); //2
	}
	Init(&sModel);
	mColBody.Matrix(&mpCombinedMatrix[3]);

	mpState = mpWalk = new CZombieWalk(this);
	mpWalk->Start();
	mState = mpWalk->State();
	// Status 追加
	mpHit = new CZombieHit(this);
}

CZombie::~CZombie()
{
	delete mpWalk;
	delete mpHit;
}

CZombie::CZombie(const CVector& pos, const CVector& rot, const CVector& scale)
	: CZombie()
{
	Position(pos);
	Rotation(rot);
	Scale(scale);
}

void CZombie::Update()
{
	mTargetPosition = mPosition + mAdjust;

	if (mState == mpState->State())
	{
		mpState->Update();
	}
	else
	{
		mState = mpState->State();
		switch (mState)
		{
		//case EState::ERUN:
		//	mpState = mpRun;
		//	break;
		//case EState::EJUMP:
		//	mpState = mpJump;
		//	break;
		//case EState::EIDLE:
		//	mpState = mpIdle;
		//	break;
		//case EState::EATTACK:
		//	mpState = mpAttack;
		//	break;
		case EState::EWALK:
			mpState = mpWalk;
			break;
		case EState::EHIT:
			mpState = mpHit;
			break;
		}
		mpState->Start();
		mpState->Update();
	}

	if (mState != EState::EIDLE || !mGrounded)
	{
		mVelocityG += mGravity;
		mTargetPosition = mTargetPosition + CVector(0.0f, mVelocityG, 0.0f);

		CVector v = mTargetPosition - mPosition;

		if (v.Length() > 0.001f)
		{
			if (v.Length() < mSpeed)
			{
				mSpeed -= 0.005f;
			}
			else if (mSpeed < VELOCITY)
			{
				mSpeed += 0.005f;
			}
			mVelocity = v.Normalize() * mSpeed;
			mPosition = mPosition + mVelocity;
		}
		else
		{
			mSpeed = 0.0f;
		}
	}

	CXCharacter::Update();
	mColBody.Update();

	mGrounded = false;
	mAdjust = CVector();

#ifdef _DEBUG

	//printf("y=%f\n", mPosition.Y());

#endif

}

void CZombie::Collision(CCollider* m, CCollider* o)
{
	mpState->Collision(m, o);
	CVector adjust;
	switch (m->Type())
	{
	case CCollider::EType::ECAPSULE:
		switch (o->Type())
		{
		//case CCollider::EType::ECAPSULE:
		//	switch (o->ParentTag())
		//	{
		//	case CCharacter3::ETag::EPLAYER:
		//		if (o->ParentState() == CCharacter3::EState::EATTACK)
		//		{
		//			if (mCntNoDame > 0) return;
		//			if (CCollider::CollisionCapsuleCapsule(m, o, &adjust))
		//			{
		//				if (mState != CCharacter3::EState::EHIT)
		//				{
		//					mState = CCharacter3::EState::EHIT;
		//					mCntNoDame = 60;
		//					ChangeAnimation(1, false, 121);
		//					AnimationFrame(0.3f);
		//				}
		//				else if (mState == CCharacter3::EState::EHIT)
		//				{
		//					mState = CCharacter3::EState::EDEATH;
		//					ChangeAnimation(2, false, 178);
		//					AnimationFrame(0.3f);
		//				}
		//			}
		//		}
		//	}
		//	break;
		case CCollider::EType::ETRIANGLE:
			if (CCollider::CollisionCapsuleTriangle(m, o, &adjust))
			{
				mVelocityG = 0.0f;
				mGrounded = true;
				mAdjust = mAdjust + adjust;
//				mVelocityG = 0.0f;
//				mPosition = mPosition + adjust;
			}
			break;
		}
		break;
	}
}

void CZombie::Hit()
{
	if (mCntNoDame > 0) mCntNoDame--;
	ChangeAnimation(1, false, 121);
	if (IsAnimationFinished())
	{
		mState = CCharacter3::EState::EWALK;
	}
}

void CZombie::Death()
{
	ChangeAnimation(2, false, 178);
}

void CZombie::Collision()
{
	CCollisionManager::Instance()->Collision(&mColBody, COLLISIONRANGE);
}
