#ifndef CDRAGON_H
#define CDRAGON_H
#include "CXCharacter.h"
#include "CColliderCapsule.h"
#include "CInput.h"
#include "CState.h"

class CDragon : public CXCharacter
{
public:
	CDragon();
	~CDragon();
	CDragon(const CVector& pos, const CVector& rot, const CVector& scale);
	void Update();
	void Collision(CCollider* m, CCollider* o);
	void Collision();
	static CModelX* Model() { return &sModel; }
private:
	static CModelX sModel;
	CColliderCapsule mColBody;	//‘Ì
};

#define VELOCITY 0.2f

#endif


