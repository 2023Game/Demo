#pragma once
#include "CTexture.h"
#include "CCharacter3.h"
#include "CBullet.h"
#include "CEnemy.h"
#include "CPlayer.h"
#include "CInput.h"
#include "CFont.h"
#include <vector>

#include "CSound.h"

#include "CVector.h"
#include "CModel.h"

#include "CTaskManager.h"

#include "CColliderTriangle.h"

#include "CColliderMesh.h"

#include "CUi.h"

#include "CModelX.h"

#include "CXPlayer.h"
#include "CXEnemy.h"

#include "CPaladin.h"

#include "CActionCamera.h"

#include "CShadowMap.h"

#include "CStageSample.h"

#include <memory>

class CApplication
{
private:
	std::unique_ptr<CStageSample> mpStageSample;
	// �V���h�E�}�b�v
	CShadowMap mShadowMap;

	CMatrix mMatrix;
	CModelX mModelX;

	static CUi* spUi;	//UI�N���X�̃|�C���^
	//���f������R���C�_�𐶐�
	CColliderMesh mColliderMesh;

	//C5���f��
	CModel mModelC5;

	CModel mBackGround; //�w�i���f��
	CModel mModel;
	CVector mEye;

	CSound mSoundBgm;	//BGM
	CSound mSoundOver;	//�Q�[���I�[�o�[

	enum class EState
	{
		ESTART,	//�Q�[���J�n
		EPLAY,	//�Q�[����
		ECLEAR,	//�Q�[���N���A
		EOVER,	//�Q�[���I�[�o�[
	};
	EState mState;
	CPlayer* mpPlayer;
	static CTexture mTexture;
	CEnemy* mpEnemy;
	CInput mInput;
	CFont mFont;

public:
	static CPaladin* mspPaladin;
	~CApplication();
	static CUi* Ui();	//UI�N���X�̃C���X�^���X���擾

	static CTexture* Texture();
	//�ŏ��Ɉ�x�������s����v���O����
	void Start();
	//�J��Ԃ����s����v���O����
	void Update();
};