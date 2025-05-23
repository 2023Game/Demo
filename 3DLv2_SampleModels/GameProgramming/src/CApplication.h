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
	// シャドウマップ
	CShadowMap mShadowMap;

	CMatrix mMatrix;
	CModelX mModelX;

	static CUi* spUi;	//UIクラスのポインタ
	//モデルからコライダを生成
	CColliderMesh mColliderMesh;

	//C5モデル
	CModel mModelC5;

	CModel mBackGround; //背景モデル
	CModel mModel;
	CVector mEye;

	CSound mSoundBgm;	//BGM
	CSound mSoundOver;	//ゲームオーバー

	enum class EState
	{
		ESTART,	//ゲーム開始
		EPLAY,	//ゲーム中
		ECLEAR,	//ゲームクリア
		EOVER,	//ゲームオーバー
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
	static CUi* Ui();	//UIクラスのインスタンスを取得

	static CTexture* Texture();
	//最初に一度だけ実行するプログラム
	void Start();
	//繰り返し実行するプログラム
	void Update();
};