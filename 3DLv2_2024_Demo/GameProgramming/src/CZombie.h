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
	void Hit();
	void Death();
	void Collision();
	static CModelX* Model() { return &sModel; }
private:
	CColliderCapsule mColBody;	//‘Ì
	static CModelX sModel;
	int mCntNoDame;
	CState* mpState;
	//CState* mpIdle;
	CState* mpWalk;
	CState* mpHit;
};

#define VELOCITY 0.015f

#endif

