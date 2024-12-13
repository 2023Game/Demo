#include "CActionCamera.h"
#include "CCollisionManager.h"
#include "CPaladin.h"

#include "glut.h"

#define TURN_V 5.0f	//��]���x
#define TURN_MOUSE_SENSE  0.5f //�}�E�X�̉�]���x

CActionCamera* CActionCamera::spInstance = nullptr;

CActionCamera::CActionCamera()
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
	/* ���݂̃r���[�|�[�g��ۑ����Ă��� */
	glGetIntegerv(GL_VIEWPORT, viewport);
	mScreenWidth = viewport[2]; //�����擾
	mScreenHeight = viewport[3]; //�������擾
	//�v���W�F�N�V�����s��̎擾
	glGetFloatv(GL_PROJECTION_MATRIX, mProjection.M());
	mInput.GetMousePos(&mx, &my);
	CTransform::Update();
	Position(pos);
	mEye = mTargetPosition;
}

void CActionCamera::Update2()
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
	ry += (mx - x);
	rx += (my - y);
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

	//if (y != 0)
	//{
	//	mRotation = mRotation + CVector(0.0f, TURN_V, 0.0f);
	//}
	//if (y < 0)
	//{
	//	mRotation = mRotation - CVector(0.0f, TURN_V, 0.0f);
	//}
	//if (x < 0)
	//{
	//	mRotation = mRotation + CVector(x, 0.0f, 0.0f);
	//	if (mRotation.X() < -80.0f)
	//	{
	//		mRotation.X(-80.0f);
	//	}
	//}
	//if (x > 0)
	//{
	//	mRotation = mRotation + CVector(x, 0.0f, 0.0f);
	//	if (mRotation.X() > 80.0f)
	//	{
	//		mRotation.X(80.0f);
	//	}
	//}

	CTransform::Update();

	mCenter = mPosition;
	mEye = mPosition + mMatrixRotate.VectorZ() * mScale.Z();

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

#include <stdio.h>

void CActionCamera::LookAt()
{
	Update2();

	gluLookAt(mEye.X(), mEye.Y(), mEye.Z(),
		mCenter.X(), mCenter.Y(), mCenter.Z(),
		mUp.X(), mUp.Y(), mUp.Z());
	//���f���r���[�s��̎擾
	glGetFloatv(GL_MODELVIEW_MATRIX, mModelView.M());

	//float x, y;
	//mInput.GetMousePos(&x, &y);
	//printf("%f,%f\n", x, y);
}

void CActionCamera::Position(const CVector& pos)
{
	mPosition = pos;
	mCenter = mPosition;
	mTargetPosition = mPosition + mMatrixRotate.VectorZ() * mScale.Z();
}

bool CActionCamera::WorldToScreen(CVector* screen, const CVector& world)
{
	//���W�ϊ�
	CVector modelview_pos = world * mModelView;
	//��ʊO�Ȃ̂Ń��^�[��
	if (modelview_pos.Z() >= 0.0f) {
		return false;
	}

	//���W����
	CVector screen_pos = modelview_pos * mProjection;
	screen_pos = screen_pos * (1.0f / -modelview_pos.Z());

	//�X�N���[���ϊ�
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

	if (v.Length() > 0.09f)
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
		mEye = mEye + mVelocity;
	}
	else
	{
		mSpeed = 0.0f;
	}

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
