#include "CPaladinWalk.h"
#include "CCamera.h"

// CPaladinWalk class

#define ANIMATION_FILE "res\\paladin\\Paladin WProp J Nordstrom@Sword And Shield Walk.fbx.x"
#define ANIMATION_SIZE 33
#define OMEGA 7.5f

CPaladinWalk::CPaladinWalk(CPaladin* parent)
{
	mpParent = parent;
	if (mpParent->Model()->IsLoaded())
	{
		mAnimNo = mpParent->Model()->AddAnimationSet(ANIMATION_FILE) - 1;
	}
}

void CPaladinWalk::Start()
{
	mpParent->ChangeAnimation(mAnimNo, true, ANIMATION_SIZE);
	mState = CCharacter3::EState::EWALK;
}

void CPaladinWalk::Update()
{
	//カメラの前方
	CVector cameraZ = CCamera::Instance()->VectorZ();
	//カメラの左方向
	CVector cameraX = CCamera::Instance()->VectorX();
	//キャラクタの前方
	CVector charZ = mpParent->MatrixRotate().VectorZ();
	//XZ平面にして正規化
	cameraZ.Y(0.0f); cameraZ = cameraZ.Normalize();
	cameraX.Y(0.0f); cameraX = cameraX.Normalize();
	charZ.Y(0.0f); charZ = charZ.Normalize();
	//移動方向の設定
	CVector move;
	if (mInput.Key('A')) {
		move = move + cameraX;
	}
	if (mInput.Key('D')) {
		move = move - cameraX;
	}
	if (mInput.Key('W')) {
		move = move + cameraZ;
	}
	if (mInput.Key('S')) {
		move = move - cameraZ;
	}

	//移動あり
	if (move.Length() > 0.0f)
	{
		//遊び
		const float MARGIN = 0.06f;
		//正規化
		move = move.Normalize();
		//自分の向きと向かせたい向きで外積
		float cross = charZ.Cross(move).Y();
		//自分の向きと向かせたい向きで内積
		float dot = charZ.Dot(move);
		//外積がプラスは左回転
		if (cross > MARGIN) {
			CVector rot = mpParent->Rotation();
			rot.Y(rot.Y() + OMEGA);
			mpParent->Rotation(rot);
		}
		//外積がマイナスは右回転
		else if (cross < -MARGIN) {
			CVector rot = mpParent->Rotation();
			rot.Y(rot.Y() - OMEGA);
			mpParent->Rotation(rot);
			//mRotation.Y(mRotation.Y() - 5.0f);
		}
		//前後の向きが同じとき内積は1.0
		else if (dot < 1.0f - MARGIN) {
			CVector rot = mpParent->Rotation();
			rot.Y(rot.Y() - OMEGA);
			mpParent->Rotation(rot);
			//mRotation.Y(mRotation.Y() - 5.0f);
		}
		//移動方向へ移動
		mpParent->AddTargetPosition(move * (VELOCITY / 2.0f));
		mState = CCharacter3::EState::EWALK;
	}
	else
	{
		mState = CCharacter3::EState::EIDLE;
	}

	if (mInput.Key(VK_LBUTTON))
	{
		mState = CCharacter3::EState::EATTACK;
	}

	if (mInput.Key(VK_SPACE))
	{
		mState = CCharacter3::EState::EJUMP;
	}

	if (mInput.Key(VK_SHIFT))
	{
		mState = CCharacter3::EState::ERUN;
	}
}