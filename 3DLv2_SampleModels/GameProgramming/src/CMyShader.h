#ifndef CMYSHADER_H
#define CMYSHADER_H

#include "CShader.h"
#include <vector>
#include <memory>
using namespace std;

class CModelX;
class CMaterial;
class CMesh;
class CMatrix;
class CModel;

class CMyShader : public CShader {
	//ƒ}ƒeƒŠƒAƒ‹‚Ìİ’è
	void SetShader(CMaterial* material);
	//•`‰æˆ—
	void Render(CModelX* model, CMesh* mesh, CMatrix* pCombinedMatrix);
	void Render(const GLuint vertexBufferId, const std::vector<CMaterial*>* materials, const float skinMatrix[], int matrixSize);
	void Render(const GLuint vertexBufferId, const std::vector<shared_ptr<CMaterial>>* materials, const float skinMatrix[], int matrixSize);
public:
	//•`‰æˆ—
	void Render(const CModel& model, const CMatrix& matrix);
	//•`‰æˆ—
	void Render(CModelX* model, CMatrix* combinedMatrix);
};

#endif
