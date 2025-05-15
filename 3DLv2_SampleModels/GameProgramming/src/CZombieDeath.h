#pragma once
#include "CZombie.h"
#include "CState.h"
#include "CInput.h"

class CZombieDeath : public CState
{
public:
	CZombieDeath(CZombie* parent);

	void Start();
	void Update();
	//void Collision(CCollider* m, CCollider* o);
	//void Render();
private:
	CZombie* mpParent;
	CInput mInput;
};