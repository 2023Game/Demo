#include "glew.h"
#include "CMyShader.h"
//#include "CLight.h"
#include "CModelX.h"
#include "CMatrix.h"
#include "CModel.h"
#include "CVertex.h"
#include "CShadowMap.h"

void CMyShader::Render(CModelX* model, CMatrix* pCombinedMatrix) {
	for (size_t i = 0; i < model->mFrame.size(); i++) {
		if (model->mFrame[i]->mpMesh != nullptr) {
			//�ʂ̂��郁�b�V���͕`�悷��
			Render(model, model->mFrame[i]->mpMesh, pCombinedMatrix);
		}
	}
}
/*
���b�V���̕`��
*/
void CMyShader::Render(CModelX* model, CMesh* mesh, CMatrix* pCombinedMatrix)
{
	//�X�L���}�g���b�N�X����
	for (size_t i = 0; i < mesh->mSkinWeights.size(); i++) {
		//�X�L�����b�V���̍s��z���ݒ肷��
		model->mpSkinningMatrix[mesh->mSkinWeights[i]->mFrameIndex]
			= mesh->mSkinWeights[i]->mOffset * pCombinedMatrix[mesh->mSkinWeights[i]->mFrameIndex];
	}

	Render(mesh->mMyVertexBufferId,
		&(mesh->mMaterial),
		model->mpSkinningMatrix[0].M(),
		model->mFrame.size());
		//mesh->mSkinWeights.size());

	return;
}


/*
���b�V���̕`��
*/
void CMyShader::Render(const CModel& model, const CMatrix& matrix)
{
	Render(model.mMyVertexBufferId, &(model.mpMaterials),  matrix.M(), 1);
	return;
}

void CMyShader::Render(const GLuint vertexBufferId, const std::vector<CMaterial*>* materials, const float skinMatrix[], int matrixSize) {
	//�V�F�[�_�[��L���ɂ���
	Enable();

	/*
	���C�g�ݒ�
	*/
	CVector vec(100.0f, 700.0f, -300.0f), ambient(0.9f, 0.9f, 0.9f), diffuse(1.0f, 1.0f, 1.0f);
	//	vec = (CVector() - vec).Normalize();
	vec = vec.Normalize();
	int lightId = glGetUniformLocation(GetProgram(), "lightVec");  //���C�g�̌�����ݒ�
	glUniform3fv(lightId, 1, (float*)&vec);
	glUniform3fv(glGetUniformLocation(GetProgram(), "lightAmbientColor"), 1, (float*)&ambient);
	glUniform3fv(glGetUniformLocation(GetProgram(), "lightDiffuseColor"), 1, (float*)&diffuse);
	//�X�L�����b�V���s��ݒ�
	int MatrixLocation = glGetUniformLocation(GetProgram(), "Transforms");
	glUniformMatrix4fv(MatrixLocation, matrixSize, GL_FALSE, skinMatrix);

	CMatrix modelview, projection;
	glGetFloatv(GL_MODELVIEW_MATRIX, modelview.M());
	/* ���݂̓����ϊ��s���ۑ����Ă��� */
	glGetFloatv(GL_PROJECTION_MATRIX, projection.M());
	MatrixLocation = glGetUniformLocation(GetProgram(), "MVP");
	glUniformMatrix4fv(MatrixLocation, 1, GL_FALSE, (modelview * projection).M());

	MatrixLocation = glGetUniformLocation(GetProgram(), "TextureMatrix1");
	glUniformMatrix4fv(MatrixLocation, 1, GL_FALSE, CShadowMap::msModelviewLight.M());

	/*
	���[���h�g�����X�t�H�[��
	*/
	//	int worldId = glGetUniformLocation(getProgram(), "WorldMatrix");
	//	glUniformMatrix4fv(worldId, 1, GL_FALSE, model->mFrame[0]->mCombinedMatrix.f);

	/* �e�N�X�`�����j�b�g1���w�肷�� */
	glUniform1i(glGetUniformLocation(GetProgram(), "DepthTexture"), 1);

	//���_�o�b�t�@���o�C���h����
	glBindBuffer(GL_ARRAY_BUFFER, vertexBufferId);

	const int POSITION_LOC = 0;
	const int NORMAL_LOC = 1;
	const int TEXCOORD_LOC = 2;
	const int WEIGHT_LOC = 3;
	const int WINDEX_LOC = 4;

	//���_���W�̈ʒu��ݒ�
	int idx = 0;
	glEnableVertexAttribArray(POSITION_LOC);
	glVertexAttribPointer(POSITION_LOC, 3, GL_FLOAT, GL_TRUE, sizeof(CVertex), (void*)idx);

	//�@���x�N�g���̈ʒu��ݒ�
	idx += sizeof(CVector);
	glEnableVertexAttribArray(NORMAL_LOC);
	glVertexAttribPointer(NORMAL_LOC, 3, GL_FLOAT, GL_TRUE, sizeof(CVertex), (void*)idx);

	//�e�N�X�`���}�b�s���O�f�[�^�̈ʒu��ݒ�
	idx += sizeof(CVector);
	glEnableVertexAttribArray(TEXCOORD_LOC);
	glVertexAttribPointer(TEXCOORD_LOC, 2, GL_FLOAT, GL_TRUE, sizeof(CVertex), (void*)idx);

	//�X�L���E�F�C�g�f�[�^�̈ʒu��ݒ�
	idx += sizeof(CVector);
	glEnableVertexAttribArray(WEIGHT_LOC);
	glVertexAttribPointer(WEIGHT_LOC, 4, GL_FLOAT, GL_TRUE, sizeof(CVertex), (void*)idx);
	//�X�L���E�F�C�g�̃C���f�b�N�X�f�[�^�̈ʒu��ݒ�
	idx += sizeof(float) * 4;
	glEnableVertexAttribArray(WINDEX_LOC);
	glVertexAttribPointer(WINDEX_LOC, 4, GL_FLOAT, GL_FALSE, sizeof(CVertex), (void*)idx);

	//�}�e���A�����ɒ��_��`�悵�܂�
	int k = 0;

	for (size_t i = 0; i < (*materials).size(); i++) {
		//�}�e���A���̒l���V�F�[�_�[�ɐݒ�
		SetShader((*materials)[i]);
		//�O�p�`�`��A�J�n���_�ԍ��A�`��Ɏg�p���钸�_��
		glDrawArrays(GL_TRIANGLES, k, (*materials)[i]->mVertexNum);	//DrawArrays:VertexIndex�Ȃ�
		//�J�n�ʒu�v�Z
		k += (*materials)[i]->mVertexNum;
		//�}�e���A���̉���
		(*materials)[i]->Disabled();
	}

	//�����ɂ���
	glDisableVertexAttribArray(WINDEX_LOC);
	glDisableVertexAttribArray(WEIGHT_LOC);
	glDisableVertexAttribArray(TEXCOORD_LOC);
	glDisableVertexAttribArray(NORMAL_LOC);
	glDisableVertexAttribArray(POSITION_LOC);

	//���_�o�b�t�@�̃o�C���h����
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	//�V�F�[�_�[�𖳌��ɂ���
	Disable();
}


/*
�}�e���A���̒l���V�F�[�_�[�ɐݒ肷��
*/
void CMyShader::SetShader(CMaterial* material) {
	//	float mColorRGBA[4] = { 1.0f, 1.0f, 1.0f, 1.0f };
	int AmbientId = glGetUniformLocation(GetProgram(), "Ambient");  //�J���[�ݒ�
	glUniform4fv(AmbientId, 1, (GLfloat*)material->mDiffuse);

	int DiffuseId = glGetUniformLocation(GetProgram(), "Diffuse");  //�J���[�ݒ�
	glUniform4fv(DiffuseId, 1, (GLfloat*)material->mDiffuse);

	//int ColorRGAB_ID = glGetUniformLocation(getProgram(), "ColorRGBA");  //�J���[�ݒ�@�d�˂ăJ���[�̕\��
	//glUniform4fv(ColorRGAB_ID, 1, (GLfloat*)mColorRGBA);

	int PowId = glGetUniformLocation(GetProgram(), "Pow");  //������ݒ�
	glUniform1f(PowId, material->mPower);

	int SpecularId = glGetUniformLocation(GetProgram(), "Specular");  //�J���[�ݒ�
	glUniform3fv(SpecularId, 1, (GLfloat*)material->mSpecular);

	int EmissiveId = glGetUniformLocation(GetProgram(), "Emissive");  //�J���[�ݒ�
	glUniform3fv(EmissiveId, 1, (GLfloat*)material->mEmissive);
	GLint samplerId = glGetUniformLocation(GetProgram(), "Sampler");
	GLint textureFlg = glGetUniformLocation(GetProgram(), "TextureFlg");
	//if (material->mTextureId > 0) {
	if (material->mTexture.Id() > 0) {
		//�e�N�X�`������
		//�e�N�X�`�����g�p�\�ɂ���
		glEnable(GL_TEXTURE_2D);
		//�e�N�X�`�����o�C���h����
		glBindTexture(GL_TEXTURE_2D, material->mTexture.Id());

		glUniform1i(samplerId, 0);//GL_TEXTURE0��K�p
		glUniform1i(textureFlg, 0);//GL_TEXTURE0��K�p
	}
	else
	{
		//�e�N�X�`���Ȃ�
		glUniform1i(textureFlg, -1);//GL_TEXTURE1��K�p
	}
}
