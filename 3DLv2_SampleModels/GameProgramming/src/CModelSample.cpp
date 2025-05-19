#include "CModelSample.h"
#include "CActionCamera.h"
#include "CCollisionManager.h"
#include "CCamera.h"

#define DRAGON_PATH "res\\Character\\DragonIke\\Dragon.x"
#define DRAGON_BASE "Character\\DragonIke\\"

//追加のアニメーションセット
//#define ANIMATION_ATTACKSP1 "res\\paladin\\SwordAndShieldAttack.x"

//CModelX CModelSample::sModel;

CModelSample::CModelSample()
	: CXCharacter(CCharacter3::ETag::EENEMY)
	, mColBody(
		this,
		nullptr,
		CVector(0.0f, -75.0f, 0.0f),
		CVector(0.0f, 60.0f, 0.0f),
		0.2f)
{
}

CModelSample::~CModelSample()
{
}

CModelSample::CModelSample(const char* base, const char* model, const CVector& pos, const CVector& rot, const CVector& scale)
	: CModelSample()
{
	if (sModel.IsLoaded() == false)
	{
		sModel.BaseDir(base);
		sModel.Load(model);
	}
	Init(&sModel);
	mColBody.Matrix(&mpCombinedMatrix[3]);
	Position(pos);
	Rotation(rot);
	Scale(scale);
}

void CModelSample::Update()
{
	CXCharacter::Update();
}

void CModelSample::Collision(CCollider* m, CCollider* o)
{
	CVector adjust;
	switch (m->Type())
	{
	case CCollider::EType::ECAPSULE:
		switch (o->Type())
		{
			// 地面、壁などの衝突判定
		case CCollider::EType::ETRIANGLE:
			if (CCollider::CollisionCapsuleTriangle(m, o, &adjust))
			{
				mVelocityG = 0.0f;
				mGrounded = true;
				mAdjust = mAdjust + adjust;
			}
			break;
		case CCollider::EType::ECAPSULE:
			if (CCollider::CollisionCapsuleCapsule(m, o, &adjust))
			{
				mAdjust = mAdjust + adjust;
			}
			break;
		}
		break;
	}
}

void CModelSample::Collision()
{
	//CCollisionManager::Instance()->Collision(&mColBody, COLLISIONRANGE);
}

