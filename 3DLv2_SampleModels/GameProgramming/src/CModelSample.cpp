#include "CModelSample.h"
#include "CActionCamera.h"
#include "CCollisionManager.h"
#include "CCamera.h"

CModelSample::CModelSample()
	: CXCharacter(CCharacter3::ETag::EENEMY)
{
}

CModelSample::~CModelSample()
{
}

CModelSample::CModelSample(const char* base, const char* model, const CVector& pos, const CVector& rot, const CVector& scale)
	: CModelSample()
{
	if (mModel.IsLoaded() == false)
	{
		mModel.BaseDir(base);
		mModel.Load(model);
	}
	Init(&mModel);
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

}

void CModelSample::Collision()
{

}

