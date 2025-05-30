#ifndef CMYSHADER_H
#define CMYSHADER_H

#include "CShader.h"
#include <vector>

class CModelX;
class CMaterial;
class CMesh;
class CMatrix;
class CModel;

class CMyShader : public CShader {
	//マテリアルの設定
	void SetShader(CMaterial* material);
	//描画処理
	void Render(CModelX* model, CMesh* mesh, CMatrix* pCombinedMatrix);
	void Render(const GLuint vertexBufferId, const std::vector<CMaterial*>* materials, const float skinMatrix[], int matrixSize);
public:
	//描画処理
	void Render(const CModel& model, const CMatrix& matrix);
	//描画処理
	void Render(CModelX* model, CMatrix* combinedMatrix);
};

#endif
