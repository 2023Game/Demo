#ifndef CACTIONCAMERA_H
#define CACTIONCAMERA_H

#include "CVector.h"
#include "CCharacter3.h"
#include "CMatrix.h"
#include "CInput.h"
/*
�J�����N���X
*/
class CActionCamera : public CCharacter3 {
public:
	void Eye(const CVector& pos);

	//���[���h���W���X�N���[�����W�֕ϊ�����
	//WorldToScreen(�X�N���[�����W, ���[���h���W)
	bool WorldToScreen(
		CVector* screen, const CVector& world);

	//�J������X���擾
	CVector VectorX();
	//�J������Z���擾
	CVector VectorZ();


	//�C���X�^���X�̎擾
	static CActionCamera* Instance();

	//�ݒ胁�\�b�h(����, X��],Y��])
	void Set(const CVector& pos, float distance, float xaxis, float yaxis);
	//�J�����X�V
	virtual void Update2();
	//�J�����K�p
	void LookAt();
	void Render() {}
	void TargetPosition(const CVector& pos);
protected:
	CActionCamera();

	float mx, my;
	int mScreenWidth; //��
	int mScreenHeight; //����
	CMatrix mProjection; //�v���W�F�N�V�����s��

	//�C���X�^���X
	static CActionCamera* spInstance;
	//���_
	CVector mEye;
	//�����_
	CVector mCenter;
	//�����
	CVector mUp;
	//���f���r���[�s��
	CMatrix mModelView;
	//���̓N���X
	CInput mInput;
};


#include "CColliderLine.h"

class CFloatCamera : public CActionCamera
{
public:
	static CFloatCamera* Instance();
	void Update2();
	void Collision();
	void Collision(CCollider* m, CCollider* o);

private:
	CCollider mColSphere;
	CFloatCamera();
	static CFloatCamera *mspInstance;
	CColliderLine mColLine;
	CVector mEyeTarget;
	CVector mEyeCurrent;

};

#endif

