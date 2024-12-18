#pragma once
#include "CPaladin.h"
#include "CState.h"
#include "CInput.h"

class CPaladinWalk : public CState
{
public:
	CPaladinWalk(CPaladin* parent);
	void Start();
	void Update();
private:
	CPaladin* mpParent;
	CInput mInput;
};