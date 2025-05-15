#pragma once
#include "CPaladin.h"
#include "CState.h"
#include "CInput.h"

class CPaladinJump : public CState
{
public:
	CPaladinJump(CPaladin* parent);

	void Start();
	void Update();
	//void Collision(CCollider* m, CCollider* o);
	//void Render();
private:
	CVector mVelocity;
	CPaladin* mpParent;
	CInput mInput;
};