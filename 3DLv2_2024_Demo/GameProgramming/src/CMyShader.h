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
	//�}�e���A���̐ݒ�
	void SetShader(CMaterial* material);
	//�`�揈��
	void Render(CModelX* model, CMesh* mesh, CMatrix* pCombinedMatrix);
	void Render(const GLuint vertexBufferId, const std::vector<CMaterial*>* materials, const float skinMatrix[], int matrixSize);
public:
	//�`�揈��
	void Render(const CModel& model, const CMatrix& matrix);
	//�`�揈��
	void Render(CModelX* model, CMatrix* combinedMatrix);
};

#endif
