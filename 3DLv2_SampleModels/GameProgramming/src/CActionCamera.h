#ifndef CACTIONCAMERA_H
#define CACTIONCAMERA_H

#include "CVector.h"
#include "CCharacter3.h"
#include "CMatrix.h"
#include "CInput.h"

#include "CColliderLine.h"

/*
カメラクラス
*/
class CActionCamera : public CCharacter3 {
public:
	void Eye(const CVector& pos);

	//ワールド座標をスクリーン座標へ変換する
	//WorldToScreen(スクリーン座標, ワールド座標)
	bool WorldToScreen(
		CVector* screen, const CVector& world);

	//カメラのX軸取得
	CVector VectorX();
	//カメラのZ軸取得
	CVector VectorZ();


	//インスタンスの取得
	static CActionCamera* Instance();

	//設定メソッド(距離, X回転,Y回転)
	void Set(const CVector& pos, float distance, float xaxis, float yaxis);
	//カメラ更新
	virtual void Update2();
	//カメラ適用
	void LookAt();
	void Render() {}
	void TargetPosition(const CVector& pos);
	void Collision(CCollider* m, CCollider* o);
	CMatrix& ModelViewInverse() { return mModelViewInverse; }
protected:
	CCollider mColSphere;
	CColliderLine mColLine;

	CActionCamera();

	float mx, my;
	int mScreenWidth; //幅
	int mScreenHeight; //高さ
	CMatrix mProjection; //プロジェクション行列

	//インスタンス
	static CActionCamera* spInstance;
	//視点
	CVector mEye;
	//注視点
	CVector mCenter;
	//上方向
	CVector mUp;
	//モデルビュー行列
	CMatrix mModelView;
	//モデルビュー逆行列
	CMatrix mModelViewInverse;
	//入力クラス
	CInput mInput;
};


class CFloatCamera : public CActionCamera
{
public:
	static CFloatCamera* Instance();
	void Update2();
	void Collision();
	void Collision(CCollider* m, CCollider* o);

private:

	CFloatCamera();
	static CFloatCamera *mspInstance;
	CVector mEyeTarget;
	CVector mEyeCurrent;

};

#endif

