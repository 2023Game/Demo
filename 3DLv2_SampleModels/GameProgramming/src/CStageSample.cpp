#include "CStageSample.h"

#include "CPaladin.h"
#include "CZombie.h"
#include "CModelSample.h"

CModel CStageSample::msModel;
bool CStageSample::msLoad = true;

#define POSITION 0.5f, 1.0f,0.0f
#define ROTATION 0.0f,0.0f,0.0f
#define SCALE 1.0f,1.0f,1.0f
#define CMAP_GROUND "res\\sky.obj","res\\sky.mtl"

#define DRAGON_PATH "res\\Character\\DragonIke\\Dragon.x"
#define DRAGON_BASE "Character\\DragonIke\\"
#define DRAGON_ANIM "animation\\DragonAttack.x"

#define GASMASK_PATH "res\\\Character\\Gas mask soldier\\GasMask_Soldier_Model.x"
#define GASMASK_BASE "Character\\Gas mask soldier\\"
#define GASMASK_ANIM "anim\\Right foot kick_121.x"

#define MONSTER_PATH "res\\\monster\\monster-animated-character-X.X"
#define MONSTER_BASE "monster\\"

#define SLIME_PATH "res\\Character\\Slime\\SlimeBlue.x"
#define SLIME_BASE "Character\\Slime\\"
#define SLIME_ANIM "animation\\SlimeAttack.x"

#define VANGU_PATH "res\\Character\\Vanguard\\VanguardModel.x"
#define VANGU_BASE "Character\\Vanguard\\"

#define YUKARI_PATH "res\\Character\\Yukari\\Yukari2.x"
#define YUKARI_BASE "Character\\Yukari\\"
#define YUKARI_ANIM "anim\\Yukari_GunWorlk79.x"

#define BEARD_PATH "res\\Character\\PlayerAwa\\Beardman.x"
#define BEARD_BASE "Character\\PlayerAwa\\"

//C:\Users\Takahashi\Desktop\Git\2023\Demo\3DLv2_SampleModels\GameProgramming\res\Character\Gas mask soldier

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

	new CPaladin(CVector(-1.0f, 1.0f, -5.0f), CVector(0.0f, 0.0f, 0.0f), CVector(1.0f, 1.0f, 1.0f));

	new CZombie(CVector(0.0f, 0.0f, 5.0f), CVector(0.0f, 180.0f, 0.0f), CVector(1.0f, 1.0f, 1.0f));

	new CModelSample(DRAGON_BASE, DRAGON_PATH, DRAGON_ANIM, CVector(10.0f, 3.0f, 5.0f), CVector(0.0f, 180.0f, 0.0f), CVector(1.0f, 1.0f, 1.0f));
	new CModelSample(GASMASK_BASE, GASMASK_PATH, GASMASK_ANIM, CVector(-10.0f, 0.0f, 5.0f), CVector(0.0f, 180.0f, 0.0f), CVector(0.1f, 0.1f, 0.1f));
	new CModelSample(MONSTER_BASE, MONSTER_PATH, CVector(-10.0f, 0.0f, 0.0f), CVector(0.0f, 180.0f, 0.0f), CVector(0.1f, 0.1f, 0.1f));
	new CModelSample(VANGU_BASE, VANGU_PATH, CVector(0.0f, 0.0f, 0.0f), CVector(0.0f, 180.0f, 0.0f), CVector(0.1f, 0.1f, 0.1f));
	new CModelSample(SLIME_BASE, SLIME_PATH, SLIME_ANIM, CVector(10.0f, 0.0f, 0.0f), CVector(0.0f, 180.0f, 0.0f), CVector(1.0f, 1.0f, 1.0f));
	new CModelSample(YUKARI_BASE, YUKARI_PATH, YUKARI_ANIM, CVector(0.0f, 0.0f, 10.0f), CVector(0.0f, 180.0f, 0.0f), CVector(0.1f, 0.1f, 0.1f));
	new CModelSample(BEARD_BASE, BEARD_PATH, CVector(-10.0f, 0.0f, 10.0f), CVector(0.0f, 180.0f, 0.0f), CVector(1.0f, 1.0f, 1.0f));

}
