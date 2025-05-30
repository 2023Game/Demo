#pragma once
#include "CPaladin.h"
#include "CState.h"
#include "CInput.h"

// 待機クラス
class CPaladinIdle : public CState
{
public:
	CPaladinIdle(CPaladin* parent);
	void Start();
	void Update();
private:
	CPaladin* mpParent;
	CInput mInput;
};