#pragma once
#include "CPaladin.h"
#include "CState.h"
#include "CInput.h"

// 待機クラス
class CPaladinDamage : public CState
{
public:
	CPaladinDamage(CPaladin* parent);
	void Start();
	void Update();
private:
	CPaladin* mpParent;
	CInput mInput;
	int mCount;
};