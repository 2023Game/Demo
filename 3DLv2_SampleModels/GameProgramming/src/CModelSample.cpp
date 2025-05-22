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

CModelSample::CModelSample(std::string base, std::string model, const CVector& pos, const CVector& rot, const CVector& scale)
	: CModelSample()
{
	if (mModel.IsLoaded() == false)
	{
		mModel.BaseDir(base);
		mModel.Load(model.c_str());
	}
	Init(&mModel);
	Position(pos);
	Rotation(rot);
	Scale(scale);
}

#define RESOURCE_DIR "res\\"

CModelSample::CModelSample(std::string base, std::string model, std::string anim, const CVector& pos, const CVector& rot, const CVector& scale)
	: CModelSample()
{
	if (mModel.IsLoaded() == false)
	{
		mModel.BaseDir(base);
		mModel.Load(model.c_str());
		mModel.AddAnimationSet((RESOURCE_DIR + base + anim).c_str());
	}
	Init(&mModel);
	ChangeAnimation(mModel.AnimationSet().size() - 1, true, 60.0f);
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
	//Enemyの座標をスクリーン座標へ変換します
	if (CActionCamera::Instance()->WorldToScreen(&screen, Position()))
	{
		//変換先の座標に文字列を出力する
		mFont.Draw(screen.X(), screen.Y() - 25, 7, 14, mpModel->BaseDir().c_str());
	}
}

