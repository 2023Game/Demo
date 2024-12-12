#ifndef CMODEL_H
#define CMODEL_H
//vector�̃C���N���[�h
#include <vector>
#include "CTriangle.h"
#include "CMaterial.h"
#include "CVertex.h"
#include "CModelX.h"

/*
���f���N���X
���f���f�[�^�̓��͂�\��
*/
class CModel //: public CMesh 
{
	//�V�F�[�_�[�N���X���t�����h�ɂ���
	friend CMyShader;

public:
	//���_�o�b�t�@���ʎq
	GLuint	  mMyVertexBufferId;

	//std::vector<CTriangle> Triangles() const;
	const std::vector<CTriangle>& Triangles() const;

	//���f���t�@�C���̓���
	//Load(���f���t�@�C����, �}�e���A���t�@�C����)
	void Load(char* obj, char* mtl);
	//�`��
	void Render();
	~CModel();
	//�`��
	//Render(�s��)
	void Render(const CMatrix& m);
	CMatrix mDummySkinningMatrix;
private:
	CMyShader mShader;
	//�}�e���A���|�C���^�̉ϒ��z��
	std::vector<CMaterial*> mpMaterials;
	//�O�p�`�̉ϒ��z��
	std::vector<CTriangle> mTriangles;
	//���_�̔z��
	CVertex* mpVertexes;
	void CreateVertexBuffer();
};

#include "CVertex.h"
#include <vector>

class CModelTest
{
public:
	CModelTest();
	void Render();

	CVertex mVertex[6];
	std::vector<CVertex> mVector;

};

#endif
