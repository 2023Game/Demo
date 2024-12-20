#pragma once
#include "CPaladin.h"
#include "CState.h"
#include "CInput.h"

// �ҋ@�N���X
class CPaladinDamage : public CState
{
public:
	CPaladinDamage(CPaladin* parent);
	void Start();
	void Update();
private:
	CPaladin* mpParent;
	CInput mInput;
};