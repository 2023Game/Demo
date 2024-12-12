#version 330 core

uniform mat4 Transforms[128];	//�X�L�j���O�s��
//uniform mat4 WorldMatrix;

layout(location = 0) in vec3 aPosition;
layout(location = 1) in vec3 aNormal;
layout(location = 2) in vec2 aTexCoord;
layout(location = 3) in vec4 weights;
layout(location = 4) in vec4 indices;

uniform mat4 MVP; //���f���r���[�~�v���W�F�N�V�����s��
uniform mat4 TextureMatrix1; // �e�N�X�`�����W�ϊ��s��

// �o��
//�t���O�����g�V�F�[�_�[�ɓn���ϐ�
out vec3 N;//�@���x�N�g��
//�t���O�����g�V�F�[�_�ɓn���e�N�X�`�����W
out vec2 TexCoord0;	//�e�N�X�`��
out vec4 TexCoord1;	//�f�v�X�e�N�X�`��

void main(void)
{
    mat4 comb = mat4(0);
	comb += Transforms[int(indices.x)] * weights.x;
	comb += Transforms[int(indices.y)] * weights.y;
	comb += Transforms[int(indices.z)] * weights.z;
	comb += Transforms[int(indices.w)] * weights.w;
		  
	//���W�A�@���A�e�N�X�`�����W�����߂�
	gl_Position = MVP * comb * vec4(aPosition,1);
    N = normalize(mat3(comb) * aNormal);
	TexCoord0 = aTexCoord;

	//�f�v�X�e�N�X�`���̃e�N�X�`�����W�����߂�
	TexCoord1 = TextureMatrix1 * comb * vec4(aPosition,1);
	//TexCoord1 = vec4(TexCoord1.xyz / TexCoord1.w, 1.0);
}