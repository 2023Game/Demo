#include "CDragon.h"
#include "CActionCamera.h"
#include "CCollisionManager.h"
#include "CCamera.h"

#define PALADIN_MODEL_PATH "res\\Character\\DragonIke\\Dragon.x"

//追加のアニメーションセット
//#define ANIMATION_ATTACKSP1 "res\\paladin\\SwordAndShieldAttack.x"

CModelX CDragon::sModel;

CDragon::CDragon()
	: CXCharacter(CCharacter3::ETag::EENEMY)
	, mColBody(
		this,
		nullptr,
		CVector(0.0f, -75.0f, 0.0f),
		CVector(0.0f, 60.0f, 0.0f),
		0.2f)
{
	if (sModel.IsLoaded() == false)
	{
		sModel.Load(PALADIN_MODEL_PATH);
	}
	Init(&sModel);
	mColBody.Matrix(&mpCombinedMatrix[3]);

}

CDragon::~CDragon()
{
}

CDragon::CDragon(const CVector& pos, const CVector& rot, const CVector& scale)
	: CDragon()
{
	Position(pos);
	Rotation(rot);
	Scale(scale);
}

void CDragon::Update()
{
	CXCharacter::Update();
}

void CDragon::Collision(CCollider* m, CCollider* o)
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

void CDragon::Collision()
{
	//CCollisionManager::Instance()->Collision(&mColBody, COLLISIONRANGE);
}

