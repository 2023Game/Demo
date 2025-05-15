#pragma once
#include "CCharacter3.h"
#include "CColliderMesh.h"

class CStageSample : public CCharacter3
{
public:
	CStageSample();
	void Update() {}
private:
	static CModel msModel;
	static bool msLoad;
	CColliderMesh mColMesh;
};