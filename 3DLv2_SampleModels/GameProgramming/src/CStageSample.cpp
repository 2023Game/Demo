#include "CStageSample.h"

#include "CPaladin.h"
#include "CZombie.h"
#include "CDragon.h"

CModel CStageSample::msModel;
bool CStageSample::msLoad = true;

#define POSITION 0.5f, -1.0f,0.0f
#define ROTATION 0.0f,0.0f,0.0f
#define SCALE 1.0f,1.0f,1.0f
#define CMAP_GROUND "res\\sky.obj","res\\sky.mtl"

CStageSample::CStageSample()
{
	if (msLoad)
	{
		msLoad = false;
		msModel.Load(CMAP_GROUND);
	}
	Model(&msModel);
	Position(CVector(POSITION));
	Rotation(CVector(ROTATION));
	Scale(CVector(SCALE));
	CTransform::Update();
	mColMesh.Set(this, &mMatrix, &msModel);

	new CPaladin(CVector(-1.0f, 1.0f, 0.0f), CVector(0.0f, 0.0f, 0.0f), CVector(1.0f, 1.0f, 1.0f));

	new CZombie(CVector(0.0f, 0.0f, 5.0f), CVector(0.0f, 180.0f, 0.0f), CVector(1.0f, 1.0f, 1.0f));

	new CDragon(CVector(10.0f, 1.0f, 5.0f), CVector(0.0f, 180.0f, 0.0f), CVector(1.0f, 1.0f, 1.0f));

}
