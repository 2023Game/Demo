#pragma once
#include "CPaladin.h"
#include "CState.h"
#include "CInput.h"

// �ҋ@�N���X
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