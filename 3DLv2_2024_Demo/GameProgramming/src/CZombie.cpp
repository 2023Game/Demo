#include "CZombie.h"
#include "CCollisionManager.h"
#include "CZombieWalk.h"
#include "CZombieHit.h"
#include "CZombieDeath.h"

#define MODEL_PATH "res\\WorldZombie\\world_war_zombie.x"
//追加のアニメーションセット
#define ANIMATION_WALK "res\\WorldZombie\\Zombie_Walk.fbx.x"

CModelX CZombie::sModel;

CZombie::CZombie()
	: CXCharacter(CCharacter3::ETag::EENEMY)
	, mColBody(
		this, 
		nullptr, 
		CVector(0.0f, -90.0f, 0.0f),
		CVector(0.0f, 70.0f, 0.0f), 
		0.175f)
{
	if (sModel.IsLoaded() == false)
	{
		sModel.Load(MODEL_PATH);
		//アニメーションの追加
		sModel.AddAnimationSet(ANIMATION_WALK); //0
	}
	Init(&sModel);
	mColBody.Matrix(&mpCombinedMatrix[3]);
	//初期状態設定
	mpState = mpWalk = new CZombieWalk(this);
	mpWalk->Start();
	mState = mpWalk->State();
	// Status 追加
	mpHit = new CZombieHit(this);
	mpDeath = new CZombieDeath(this);
}

CZombie::~CZombie()
{
	delete mpWalk;
	delete mpHit;
	delete mpDeath;
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

	if (mState != mpState->State())
	{
		mState = mpState->State();
		switch (mState)
		{
		//case EState::EATTACK:
		//	mpState = mpAttack;
		//	break;
		case EState::EWALK:
			mpState = mpWalk;
			break;
		case EState::EHIT:
			mpState = mpHit;
			break;
		case EState::EDEATH:
			mpState = mpDeath;
			break;
		}
		mpState->Start();
	}
	mpState->Update();

	if (mState != EState::EDEATH || !mGrounded)
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
		case CCollider::EType::ETRIANGLE:
			if (CCollider::CollisionCapsuleTriangle(m, o, &adjust))
			{
				mVelocityG = 0.0f;
				mGrounded = true;
				mAdjust = mAdjust + adjust;
			}
			break;
		}
		break;
	}
}

void CZombie::Collision()
{
	CCollisionManager::Instance()->Collision(&mColBody, COLLISIONRANGE);
}
