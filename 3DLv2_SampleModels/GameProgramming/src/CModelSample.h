#ifndef CMODELSAMPLE_H
#define CMODELSAMPLE_H
#include "CXCharacter.h"
#include "CColliderCapsule.h"

class CModelSample : public CXCharacter
{
public:
	CModelSample();
	~CModelSample();
	CModelSample(const char* base, const char* model, const CVector& pos, const CVector& rot, const CVector& scale);
	void Update();
	void Collision(CCollider* m, CCollider* o);
	void Collision();
	//static CModelX* Model() { return &sModel; }
private:
	/*static*/ CModelX sModel;
	CColliderCapsule mColBody;	//‘Ì
};

#define VELOCITY 0.2f

#endif


