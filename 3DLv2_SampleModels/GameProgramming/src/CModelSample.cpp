#include "CModelSample.h"
#include "CActionCamera.h"
#include "CCollisionManager.h"
#include "CCamera.h"
#include "main.h"

CFont CModelSample::mFont;

CModelSample::CModelSample()
	: CXCharacter(CCharacter3::ETag::EENEMY)
{
	mFont.Load("FontG.png", 1, 4096 / 64);
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

#include <string.h>

void CModelSample::RenderUI()
{
	CVector screen;
	//Enemy�̍��W���X�N���[�����W�֕ϊ����܂�
	if (CActionCamera::Instance()->WorldToScreen(&screen, Position()))
	{
		//�ϊ���̍��W�ɕ�������o�͂���
		mFont.Draw(screen.X(), screen.Y() - 25, 7, 14, mpModel->BaseDir().c_str());
	}
}

