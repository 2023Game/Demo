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
#include "main.h"

//�N���X��static�ϐ�
CTexture CApplication::mTexture;
CPaladin* CApplication::mspPaladin = nullptr;

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


void gRender()
{
	CTaskManager::Instance()->Render();
}

CTexture* CApplication::Texture()
{
	return &mTexture;
}

void CApplication::Start()
{
	//�J�����̐ݒ�
	CCamera::Instance()->Set(CVector(-1.0f, 2.0f, 0.0f), 7.5f, -10.0f, 180.0f);

	mFont.Load("FontG.png", 1, 4096 / 64);

	mpStageSample = std::make_unique<CStageSample>();

	// �V���h�E�}�b�v
#define TEXWIDTH  8192  //�e�N�X�`����
#define TEXHEIGHT  6144  //�e�N�X�`������
	float shadowColor[] = { 0.4f, 0.4f, 0.4f, 0.4f };  //�e�̐F
	float lightPos[] = { 0.0f,80.0f,0.0f };  //�����̈ʒu
	mShadowMap.Init(TEXWIDTH, TEXHEIGHT, gRender, shadowColor, lightPos);
}

void CApplication::Update()
{
	CTaskManager::Instance()->Update();

	CCamera::Instance()->LookAt();

	//�Փˏ���
	CTaskManager::Instance()->Collision();

	//CCollisionManager::Instance()->Delete();
	CTaskManager::Instance()->Delete();

	//�V���h�E�}�b�v�̕`��
	mShadowMap.Render();
	//gRender(); //�V���h�E�}�b�v�g��Ȃ�

#ifdef _DEBUG
	//�R���C�_�̕`��
	CCollisionManager::Instance()->Render();
#endif

	//2D�`��J�n
	CCamera::Start(0, WINDOW_WIDTH, 0, WINDOW_HEIGHT);

	mFont.Draw(20, 20, 10, 12, "3D PROGRAMMING");

	//CVector screen;
	////Enemy�̍��W���X�N���[�����W�֕ϊ����܂�
	//if (CActionCamera::Instance()->WorldToScreen(&screen, mspPaladin->Position()))
	//{
	//	//�ϊ���̍��W�ɕ�������o�͂���
	//	mFont.Draw(screen.X(), screen.Y() - 25, 7, 14, "PLAYER");
	//}

	//2D�̕`��I��
	CCamera::End();
}
