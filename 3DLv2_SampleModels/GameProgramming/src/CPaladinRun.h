#pragma once
#include "CPaladin.h"
#include "CState.h"
#include "CInput.h"

class CPaladinRun : public CState
{
public:
	CPaladinRun(CPaladin* parent);
	void Start();
	void Update();
private:
	CPaladin* mpParent;
	CInput mInput;
};