#ifndef CMODELSAMPLE_H
#define CMODELSAMPLE_H
#include "CXCharacter.h"
#include "CFont.h"

class CModelSample : public CXCharacter
{
public:
	CModelSample();
	~CModelSample();
	CModelSample(std::string base, std::string model, const CVector& pos, const CVector& rot, const CVector& scale);
	CModelSample(std::string base, std::string model, std::string anim, const CVector& pos, const CVector& rot, const CVector& scale);
	void Update();
	void Collision(CCollider* m, CCollider* o);
	void Collision();
	void RenderUI();
private:
	static CFont mFont;
	CModelX mModel;
};

#endif


