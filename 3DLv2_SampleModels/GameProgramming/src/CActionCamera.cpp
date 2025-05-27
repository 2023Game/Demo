#include "CActionCamera.h"
#include "CCollisionManager.h"
#include "CPaladin.h"
#include "CApplication.h"

#include "glut.h"

#define TURN_V 5.0f	//回転速度
#define TURN_MOUSE_SENSE  0.25f //マウスの回転感度
#define COLLIDER_RADIUS 0.5f //カメラコライダの大きさ

CActionCamera* CActionCamera::spInstance = nullptr;

CActionCamera::CActionCamera()
	: mColSphere(this, nullptr, CVector(), COLLIDER_RADIUS)
{
	spInstance = this;
}

CActionCamera* CActionCamera::Instance()
{
	if (spInstance == nullptr)
	{
		new CActionCamera();
	}
	return spInstance;
}

void CActionCamera::Set(const CVector& pos, float distance, float xaxis, float yaxis)
{
	CTransform::Position(pos);
	Rotation(CVector(xaxis, yaxis, 0.0f));
	Scale(CVector(0.0f, 0.0f, distance));
	mUp = CVector(0.0f, 1.0f, 0.0f);
	spInstance = this;
	int viewport[4];
	/* 現在のビューポートを保存しておく */
	glGetIntegerv(GL_VIEWPORT, viewport);
	mScreenWidth = viewport[2]; //幅を取得
	mScreenHeight = viewport[3]; //高さを取得
	//プロジェクション行列の取得
	glGetFloatv(GL_PROJECTION_MATRIX, mProjection.M());
	mInput.GetMousePos(&mx, &my);
	CTransform::Update();
	Position(pos);
	mEye = mTargetPosition;
}

void CActionCamera::Update2()
{
	//キーボードで上下左右に回転
	int ry = 0, rx = 0;
	if (mInput.Key('J'))
	{
		ry += TURN_V;
	}
	if (mInput.Key('L'))
	{
		ry -= TURN_V;
	}
	if (mInput.Key('I'))
	{
		rx -= TURN_V;
	}
	if (mInput.Key('K'))
	{
		rx += TURN_V;
	}

	//マウスで上下左右に回転
	float x, y;
	mInput.GetMousePos(&x, &y);
	ry += (mx - x) * TURN_MOUSE_SENSE;
	rx += (my - y) * TURN_MOUSE_SENSE;
	mx = x;
	my = y;

	mRotation = mRotation + CVector(0.0f, ry, 0.0f);
	mRotation = mRotation + CVector(rx, 0.0f, 0.0f);
	if (mRotation.X() < -80.0f)
	{
		mRotation.X(-80.0f);
	}
	if (mRotation.X() > 80.0f)
	{
		mRotation.X(80.0f);
	}

	CTransform::Update();

	mCenter = mPosition;
	mEye = mPosition + mMatrixRotate.VectorZ() * mScale.Z();

	//壁を通過しないように調整
	// まず線コライダ
	mAdjust = CVector();
	mColLine.Set(this, nullptr, mCenter, mEye);
	mColLine.Update();
	CCollisionManager::Instance()->Collision(&mColLine, COLLISIONRANGE);
	// 次に球コライダ
	mEye = mEye + mAdjust;
	mColSphere.Position(mEye);
	mColSphere.Update();
	CCollisionManager::Instance()->Collision(&mColSphere, COLLISIONRANGE);

#ifdef _DEBUG
	// Nキーでマウスカーソル消す
	if (mInput.Key('N') || mInput.Key(VK_MBUTTON))
	{
		glfwSetInputMode(mInput.Window(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);
		//		glfwSetInputMode(mInput.Window(), GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
	}
	// Mキーでマウスカーソル表示
	if (mInput.Key('M'))
	{
		glfwSetInputMode(mInput.Window(), GLFW_CURSOR, GLFW_CURSOR_NORMAL);
	}
#else
	glfwSetInputMode(mInput.Window(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);
#endif
}

#include <stdio.h>

void CActionCamera::LookAt()
{
	Update2();

	gluLookAt(mEye.X(), mEye.Y(), mEye.Z(),
		mCenter.X(), mCenter.Y(), mCenter.Z(),
		mUp.X(), mUp.Y(), mUp.Z());
	//モデルビュー行列の取得
	glGetFloatv(GL_MODELVIEW_MATRIX, mModelView.M());
	// 逆行列の作成
	mModelViewInverse = mModelView.Transpose();
	mModelViewInverse.M(0, 3, 0);
	mModelViewInverse.M(1, 3, 0);
	mModelViewInverse.M(2, 3, 0);
}

void CActionCamera::TargetPosition(const CVector& pos)
{
	mPosition = pos;
	mCenter = mPosition;
	mTargetPosition = mPosition + mMatrixRotate.VectorZ() * mScale.Z();
}

void CActionCamera::Collision(CCollider* m, CCollider* o)
{
	//Lineで壁まで移動し、球でさらに壁から離す
	CVector adjust;
	switch (m->Type())
	{
	case CCollider::EType::ELINE:
		switch (o->Type())
		{
		case CCollider::EType::ETRIANGLE:
			if (CCollider::CollisionTriangleLine(o, m, &adjust))
			{
				// 近づく方向へ移動させる
				if (m->V(2).Dot(adjust) < 0)
				{
					//一番近い場所に調整する
					if (mAdjust.Length() < adjust.Length())
					{
						mAdjust = adjust;
					}
				}
			}
			break;
		}
		break;
	case CCollider::EType::ESPHERE:
		switch (o->Type())
		{
		case CCollider::EType::ETRIANGLE:
			if (CCollider::CollisionTriangleSphere(o, m, &adjust))
			{
				//壁ピッタリにはしない
				mEye = mEye + adjust;
			}
			break;
		}
		break;
	}
}

void CActionCamera::Eye(const CVector& pos)
{
	mPosition = pos;
	mCenter = mPosition;
	mEye = mTargetPosition = mPosition + mMatrixRotate.VectorZ() * mScale.Z();
}

bool CActionCamera::WorldToScreen(CVector* screen, const CVector& world)
{
	//座標変換
	CVector modelview_pos = world * mModelView;
	//画面外なのでリターン
	if (modelview_pos.Z() >= 0.0f) {
		return false;
	}

	//座標調整
	CVector screen_pos = modelview_pos * mProjection;
	screen_pos = screen_pos * (1.0f / -modelview_pos.Z());

	//スクリーン変換
	screen->X((1.0f + screen_pos.X()) * mScreenWidth * 0.5f);
	screen->Y((1.0f + screen_pos.Y()) * mScreenHeight * 0.5f);
	screen->Z(screen_pos.Z());

	return true;
}

CVector CActionCamera::VectorX()
{
	return CVector(-mModelView.M(0, 0), -mModelView.M(1, 0), -mModelView.M(2, 0));
}

CVector CActionCamera::VectorZ()
{
	return CVector(-mModelView.M(0, 2), -mModelView.M(1, 2), -mModelView.M(2, 2));
}



// CFloatCamera class

CFloatCamera* CFloatCamera::mspInstance = nullptr;

CFloatCamera::CFloatCamera()
{
}

CFloatCamera* CFloatCamera::Instance()
{
	if (mspInstance == nullptr)
	{
		mspInstance = new CFloatCamera();
	}
	return mspInstance;
}


void CFloatCamera::Collision(CCollider* m, CCollider* o)
{
	//CVector adjust;
	//switch (m->Type())
	//{
	//case CCollider::EType::ELINE:
	//	switch (o->Type())
	//	{
	//	case CCollider::EType::ETRIANGLE:
	//		if (CCollider::CollisionTriangleLine(o, m, &adjust))
	//		{
	//			if (mAdjust.Length() <= 0.0f
	//				|| mAdjust.Length() > adjust.Length())
	//			{
	//				mAdjust = adjust;
	//			}
	//			//mAdjust = mAdjust + adjust;
	//			//mEye = mEye + adjust.Normalize() * (adjust.Length());
	//		}
	//		break;
	//	}
	//	break;
	//case CCollider::EType::ESPHERE:
	//	switch (o->Type())
	//	{
	//	case CCollider::EType::ETRIANGLE:
	//		if (CCollider::CollisionTriangleSphere(o, m, &adjust))
	//		{
	//			//mAdjust = mAdjust + adjust;
	//			mEye = mEye + adjust;
	//		}
	//		break;
	//	}
	//	break;
	//}
}

void CFloatCamera::Collision()
{
	//CCollisionManager::Instance()->Collision(&mColBody, COLLISIONRANGE);
	//CCollisionManager::Instance()->Collision(&mColSword, COLLISIONRANGE);
}

void CFloatCamera::Update2()
{
	int ry = 0, rx = 0;
	if (mInput.Key('J'))
	{
		ry += TURN_V;
	}
	if (mInput.Key('L'))
	{
		ry -= TURN_V;
	}
	if (mInput.Key('I'))
	{
		rx -= TURN_V;
	}
	if (mInput.Key('K'))
	{
		rx += TURN_V;
	}

	float x, y;
	mInput.GetMousePos(&x, &y);
	ry += (mx - x) * TURN_MOUSE_SENSE;
	rx += (my - y) * TURN_MOUSE_SENSE;
	mx = x;
	my = y;

	if (rx < -80.0f)
	{
		rx = (-80.0f);
	}
	if (rx > 80.0f)
	{
		rx = (80.0f);
	}

	mRotation = mRotation + CVector(0.0f, ry, 0.0f);
	mRotation = mRotation + CVector(rx, 0.0f, 0.0f);

	CTransform::Update();

	mCenter = mPosition;
	mTargetPosition = mPosition + mMatrixRotate.VectorZ() * mScale.Z();

	CVector v = mTargetPosition - mEye;

	if (v.Length() > CApplication::mspPaladin->Speed())
	{
		if (v.Length() < mSpeed)
		{
			mSpeed -= 0.005f;
		}
		else if (mSpeed < CApplication::mspPaladin->Speed())
		{
			mSpeed += 0.005f;
		}
		else
		{
			mSpeed = CApplication::mspPaladin->Speed();
		}
		//mSpeed = VELOCITY;
		mVelocity = v.Normalize() * mSpeed;
		mEye = mEye + mVelocity;
	}
	else
	{
		mSpeed = 0.0f;
	}

	mAdjust = CVector();
	mColLine.Set(this, nullptr, mCenter, mEye);
	mColLine.Update();
	CCollisionManager::Instance()->Collision(&mColLine, COLLISIONRANGE);
	mEye = mEye + mAdjust;

	mColSphere.Position(mEye);
	mColSphere.Update();
	CCollisionManager::Instance()->Collision(&mColSphere, COLLISIONRANGE);

	if (mInput.Key('N') || mInput.Key(VK_MBUTTON))
	{
		glfwSetInputMode(mInput.Window(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);
		//		glfwSetInputMode(mInput.Window(), GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
	}
	if (mInput.Key('M'))
	{
		glfwSetInputMode(mInput.Window(), GLFW_CURSOR, GLFW_CURSOR_NORMAL);
	}
}
