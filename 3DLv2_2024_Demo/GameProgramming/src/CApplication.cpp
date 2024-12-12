#include "CApplication.h"
//OpenGL
#include "glut.h"
#include "CVector.h"
#include "CTriangle.h"
#include "CMatrix.h"
#include "CTransform.h"

#include "CCollisionManager.h"

#include "CBillBoard.h"
#include "CEnemy3.h"

#include "CCamera.h"

#include "CMap.h"
#include "CZombie.h"

//�N���X��static�ϐ�
CTexture CApplication::mTexture;

//CCamera CApplication::mCamera;

CUi* CApplication::spUi = nullptr;
CApplication::~CApplication()
{
	delete spUi;	//�C���X�^���XUi�̍폜
}
CUi* CApplication::Ui()
{
	return spUi;
}

#define SOUND_BGM "res\\mario.wav" //BGM�����t�@�C��
#define SOUND_OVER "res\\mdai.wav" //�Q�[���I�[�o�[�����t�@�C��
//���f���f�[�^�̎w��
#define MODEL_OBJ "res\\f14.obj", "res\\f14.mtl"
//�G�A���@���f��
#define MODEL_C5 "res\\c5.obj", "res\\c5.mtl"

//�w�i���f���f�[�^�̎w��
#define MODEL_BACKGROUND  "res\\sky.obj", "res\\sky.mtl"


//CTaskManager CApplication::mTaskManager;

//CTaskManager* CApplication::TaskManager()
//{
//	return &mTaskManager;
//}

//CCamera* CApplication::Camera()
//{
//	return &mCamera;
//}

void gRender()
{
	CTaskManager::Instance()->Render();
}


CMatrix CApplication::mModelViewInverse;

const CMatrix& CApplication::ModelViewInverse()
{
	return mModelViewInverse;
}

CTexture* CApplication::Texture()
{
	return &mTexture;
}

void CApplication::Start()
{
	//�J�����̐ݒ�
	mActionCamera.Set(2.5f, -15.0f, 180.0f);

	//mKnight.Load("res\\knight\\knight_low.x");
	//mKnight.SeparateAnimationSet(0, 10, 80, "walk");//1:�ړ�
	//mKnight.SeparateAnimationSet(0, 1530, 1830, "idle1");//2:�ҋ@
	//mKnight.SeparateAnimationSet(0, 10, 80, "walk");//3:�_�~�[
	//mKnight.SeparateAnimationSet(0, 10, 80, "walk");//4:�_�~�[
	//mKnight.SeparateAnimationSet(0, 10, 80, "walk");//5:�_�~�[
	//mKnight.SeparateAnimationSet(0, 10, 80, "walk");//6:�_�~�[
	//mKnight.SeparateAnimationSet(0, 440, 520, "attack1");//7:Attack1
	//mKnight.SeparateAnimationSet(0, 520, 615, "attack2");//8:Attack2
	//mKnight.SeparateAnimationSet(0, 10, 80, "walk");//9:�_�~�[
	//mKnight.SeparateAnimationSet(0, 10, 80, "walk");//10:�_�~�[
	//mKnight.SeparateAnimationSet(0, 1160, 1260, "death1");//11:�_�E��

	//3D���f���t�@�C���̓ǂݍ���
//	mModelX.Load(MODEL_FILE);
	//�L�����N�^�[�Ƀ��f����ݒ�
//	mXPlayer.Init(&mModelX);

	mFont.Load("FontG.png", 1, 4096 / 64);

	//mXEnemy.Init(&mKnight);
	//mXEnemy.Position(CVector(7.0f, 0.0f, 0.0f));
	//mXEnemy.ChangeAnimation(2, true, 200);

	new CMap();

	mpPaladin = new CPaladin(CVector(-1.0f, 0.0f, 0.0f), CVector(0.0f, 0.0f, 0.0f), CVector(1.0f, 1.0f, 1.0f));

	new CZombie(CVector(1.0f, 0.0f, 5.0f), CVector(0.0f, 180.0f, 0.0f), CVector(1.0f, 1.0f, 1.0f));


#define TEXWIDTH  8192  //�e�N�X�`����
#define TEXHEIGHT  6144  //�e�N�X�`������

	float shadowColor[] = { 0.4f, 0.4f, 0.4f, 0.4f };  //�e�̐F
	float lightPos[] = { 0.0f,80.0f,0.0f };  //�����̈ʒu
	mShadowMap.Init(TEXWIDTH, TEXHEIGHT, gRender, shadowColor, lightPos);
}

void CApplication::Update()
{
	CTaskManager::Instance()->Update();

	mActionCamera.Position(mpPaladin->Position()
		+ CVector(0.0f, 2.0f, 0.0f));
	mActionCamera.Update();
	mActionCamera.Render();

	//���f���r���[�s��̎擾
	glGetFloatv(GL_MODELVIEW_MATRIX, mModelViewInverse.M());
	//�t�s��̎擾
	mModelViewInverse = mModelViewInverse.Transpose();
	mModelViewInverse.M(0, 3, 0);
	mModelViewInverse.M(1, 3, 0);
	mModelViewInverse.M(2, 3, 0);

	//�Փˏ���
	CTaskManager::Instance()->Collision();
//	CCollisionManager::Instance()->Collision();

	mShadowMap.Render();
	//CTaskManager::Instance()->Render();

	//�R���C�_�̕`��
	//CCollisionManager::Instance()->Render();

	//2D�`��J�n
	CCamera::Start(0, 800, 0, 600);

	mFont.Draw(20, 20, 10, 12, "3D PROGRAMMING");

	CVector screen;
	//Enemy�̍��W���X�N���[�����W�֕ϊ����܂�
	if (CActionCamera::Instance()->WorldToScreen(&screen, mpPaladin->Position()))
	{
		//�ϊ���̍��W�ɕ�������o�͂���
		mFont.Draw(screen.X(), screen.Y() - 25, 7, 14, "PLAYER");
	}

	//2D�̕`��I��
	CCamera::End();
}
