#pragma once
// 状態クラスの基本クラス
class CState
{
public:
	// 最初に1回実行する処理
	virtual void Start() = 0;
	// １フレーム分繰り返し実行する処理
	virtual void Update() = 0;
	//　任意の衝突処理
	virtual void Collision(CCollider* m, CCollider* o) {}
	// 任意の描画処理
	virtual void Render() {}
	// 状態の設定
	void State(const CCharacter3::EState& state) { mState = state; }
	// 状態の取得
	const CCharacter3::EState& State() const { return mState; }
protected:
	CCharacter3::EState mState; //状態の保存
	int mAnimNo; //アニメーションの番号
};