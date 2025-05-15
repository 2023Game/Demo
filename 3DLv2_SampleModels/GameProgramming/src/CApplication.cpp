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

//クラスのstatic変数
CTexture CApplication::mTexture;
CPaladin* CApplication::mspPaladin = nullptr;

CUi* CApplication::spUi = nullptr;
CApplication::~CApplication()
{
	delete spUi;	//インスタンスUiの削除
}
CUi* CApplication::Ui()
{
	return spUi;
}

#define SOUND_BGM "res\\mario.wav" //BGM音声ファイル
#define SOUND_OVER "res\\mdai.wav" //ゲームオーバー音声ファイル
//モデルデータの指定
#define MODEL_OBJ "res\\f14.obj", "res\\f14.mtl"
//敵輸送機モデル
#define MODEL_C5 "res\\c5.obj", "res\\c5.mtl"

//背景モデルデータの指定
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
	//カメラの設定
	CCamera::Instance()->Set(CVector(-1.0f, 2.0f, 0.0f), 7.5f, -10.0f, 180.0f);

	mFont.Load("FontG.png", 1, 4096 / 64);

	mpStageSample = std::make_unique<CStageSample>();

	// シャドウマップ
#define TEXWIDTH  8192  //テクスチャ幅
#define TEXHEIGHT  6144  //テクスチャ高さ
	float shadowColor[] = { 0.4f, 0.4f, 0.4f, 0.4f };  //影の色
	float lightPos[] = { 0.0f,80.0f,0.0f };  //光源の位置
	mShadowMap.Init(TEXWIDTH, TEXHEIGHT, gRender, shadowColor, lightPos);
}

void CApplication::Update()
{
	CTaskManager::Instance()->Update();

	CCamera::Instance()->LookAt();

	//衝突処理
	CTaskManager::Instance()->Collision();

	//CCollisionManager::Instance()->Delete();
	CTaskManager::Instance()->Delete();

	//シャドウマップの描画
	mShadowMap.Render();
	//gRender(); //シャドウマップ使わない

#ifdef _DEBUG
	//コライダの描画
	CCollisionManager::Instance()->Render();
#endif

	//2D描画開始
	CCamera::Start(0, WINDOW_WIDTH, 0, WINDOW_HEIGHT);

	mFont.Draw(20, 20, 10, 12, "3D PROGRAMMING");

	//CVector screen;
	////Enemyの座標をスクリーン座標へ変換します
	//if (CActionCamera::Instance()->WorldToScreen(&screen, mspPaladin->Position()))
	//{
	//	//変換先の座標に文字列を出力する
	//	mFont.Draw(screen.X(), screen.Y() - 25, 7, 14, "PLAYER");
	//}

	//2Dの描画終了
	CCamera::End();
}
