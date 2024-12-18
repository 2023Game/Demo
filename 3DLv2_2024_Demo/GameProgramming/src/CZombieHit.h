#pragma once
#include "CZombie.h"
#include "CState.h"
#include "CInput.h"

class CZombieHit : public CState
{
public:
	CZombieHit(CZombie* parent);

	void Start();
	void Update();
	void Collision(CCollider* m, CCollider* o);
	//void Render();
private:
	CZombie* mpParent;
	CInput mInput;
};