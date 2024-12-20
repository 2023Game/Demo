#ifndef CZOMBIE_H
#define CZOMBIE_H

#include "CXCharacter.h"
#include "CColliderCapsule.h"
#include "CState.h"

class CZombie : public CXCharacter
{
public:
	CZombie();
	~CZombie();
	CZombie(const CVector& pos, const CVector& rot, const CVector& scale );
	void Update();
	void Collision(CCollider* m, CCollider* o);
	void Collision();
	static CModelX* Model() { return &sModel; }
	CCharacter3* Target()
	{
		return mpTarget;
	}
	void Target(CCharacter3* target)
	{
		mpTarget = target;
	}
private:
	CCharacter3* mpTarget;
	CColliderCapsule mColBody;	//‘Ì
	static CModelX sModel;
	// Status
	//CState* mpState;
	CState* mpWalk;
	CState* mpHit;
	CState* mpDeath;
	CState* mpAttack;
};

#define VELOCITY 0.015f

#endif

