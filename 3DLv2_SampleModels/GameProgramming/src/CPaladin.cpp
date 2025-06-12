#include "CPaladin.h"
#include "CActionCamera.h"
#include "CCollisionManager.h"
#include "CPaladinIdle.h"
#include "CPaladinWalk.h"
#include "CPaladinAttack.h"
#include "CPaladinJump.h"
#include "CPaladinRun.h"
#include "CPaladinDamage.h"
#include "CCamera.h"

#define PALADIN_MODEL_PATH "res\\paladin\\paladin.x"

//追加のアニメーションセット
//#define ANIMATION_ATTACKSP1 "res\\paladin\\SwordAndShieldAttack.x"

CModelX CPaladin::sModel;

CPaladin::CPaladin()
	: CXCharacter(CCharacter3::ETag::EPLAYER)
	, mColBody(
		this,
		nullptr,
		CVector(0.0f, 10.0f, 0.0f),
		CVector(0.0f, 135.0f, 0.0f),
		0.2f)
	, mColSword(
		this,
		nullptr,
		CVector(10.0f, 15.0f, 5.0f),
		CVector(80.0f, 25.0f, 10.0f),
		0.1f,
		CCollider::ETag::ESWORD)
{
	if (sModel.IsLoaded() == false)
	{
		sModel.Load(PALADIN_MODEL_PATH);
	}
	Init(&sModel);
	mColBody.Matrix(CombinedMatrix("Armature"));//Armature
	mColSword.Matrix(CombinedMatrix("Armature_mixamorig_RightHandIndex1"));//"Paladin_J_Nordstrom_Sword"
//	mColBody.Matrix(&mpCombinedMatrix[2]);//Armature
//	mColSword.Matrix(&mpCombinedMatrix[50]);//"Paladin_J_Nordstrom_Sword"
	// 初期状態設定
	mpState = mpIdle = new CPaladinIdle(this);
	mpState->Start();
	mState = mpState->State();
	// 状態追加
	mpWalk = new CPaladinWalk(this);
	mpAttack = new CPaladinAttack(this);
	mpJump = new CPaladinJump(this);
	mpRun = new CPaladinRun(this);
	mpDamage = new CPaladinDamage(this);
}

CPaladin::~CPaladin()
{
	delete mpIdle;
	delete mpWalk;
	delete mpAttack;
	delete mpJump;
	delete mpRun;
	delete mpDamage;
}

CPaladin::CPaladin(const CVector& pos, const CVector& rot, const CVector& scale)
	: CPaladin()
{
	Position(pos);
	Rotation(rot);
	Scale(scale);
}

void CPaladin::Update()
{
	mTargetPosition = mPosition + mAdjust;
	// 状態が変わればインスタンスを切替える
	if (mState != mpState->State())
	{
		mState = mpState->State();
		switch (mState)
		{
		case EState::EDAMAGE:
			mpState = mpDamage;
			break;
		case EState::ERUN:
			mpState = mpRun;
			break;
		case EState::EJUMP:
			mpState = mpJump;
			break;
		case EState::EIDLE:
			mpState = mpIdle;
			break;
		case EState::EATTACK:
			mpState = mpAttack;
			break;
		case EState::EWALK:
			mpState = mpWalk;
			break;
		}
		mpState->Start();
	}
	mpState->Update();

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
	mColSword.Update();

	mGrounded = false;
	mAdjust = CVector();

	//CFloatCamera::Instance()->TargetPosition(Position() + CVector(0.0f, 2.0f, 0.0f));
	CCamera::Instance()->TargetPosition(Position() + CVector(0.0f, 1.5f, 0.0f));
}

void CPaladin::Collision(CCollider* m, CCollider* o)
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
			case CCharacter3::ETag::EENEMY:
					if (CCollider::CollisionCapsuleCapsule(m, o, &adjust))
					{
						mAdjust = mAdjust + adjust;
					}
			}
			break;
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

void CPaladin::Collision()
{
	CCollisionManager::Instance()->Collision(&mColBody, COLLISIONRANGE);
	CCollisionManager::Instance()->Collision(&mColSword, COLLISIONRANGE);
}

