#ifndef CMATERIAL_H
#define CMATERIAL_H
#include "CTexture.h"
#include "CModelX.h"
#include <string>
#include <memory>

#define MATERIAL_NAME_LEN 64 //���O�̒���

/*
�}�e���A���N���X
�}�e���A���̃f�[�^������
*/
class CMaterial : public std::enable_shared_from_this <CMaterial> {
	friend CMyShader;
public:
	void Specular(float r, float g, float b);
	void Emissive(float r, float g, float b);
	void Power(float p);

	CMaterial(CModelX* model);
	~CMaterial();

	//�e�N�X�`���̎擾
	CTexture* Texture();
	//�}�e���A���𖳌��ɂ���
	void Disabled();
	//�f�t�H���g�R���X�g���N�^
	CMaterial();
	//�}�e���A����L���ɂ���
	void Enabled();
	//�}�e���A���̖��O�̎擾
	const char* Name();
	//�}�e���A���̖��O��ݒ肷��
	//Name(�}�e���A���̖��O)
	void Name(char* name);
	//mDiffuse�z��̎擾
	float* Diffuse();
	//���_���̐ݒ�
	//VertexNum(���_��)
	void VertexNum(int num);
	//���_���̎擾
	int VertexNum();
//private:
	float mPower;
	float mSpecular[3];
	float mEmissive[3];
	//�e�N�X�`���t�@�C����
	//char* mpTextureFilename;
	std::string mpTextureFilename;

	//�}�e���A�����̒��_��
	int mVertexNum;
	//�e�N�X�`��
	CTexture mTexture;
	//�}�e���A����
	//char mName[MATERIAL_NAME_LEN + 1];
	std::string mName;
	//�g�U���̐FRGBA
	float mDiffuse[4];
};

#endif

