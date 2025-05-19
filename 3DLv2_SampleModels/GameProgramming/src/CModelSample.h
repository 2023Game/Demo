#ifndef CMODELSAMPLE_H
#define CMODELSAMPLE_H
#include "CXCharacter.h"

class CModelSample : public CXCharacter
{
public:
	CModelSample();
	~CModelSample();
	CModelSample(const char* base, const char* model, const CVector& pos, const CVector& rot, const CVector& scale);
	void Update();
	void Collision(CCollider* m, CCollider* o);
	void Collision();
private:
	CModelX mModel;
};

#endif


