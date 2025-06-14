#include "CXCharacter.h"

CMatrix* CXCharacter::CombinedMatrix(const std::string& name)
{

	for (size_t i = 0; i < mpModel->Frames().size(); i++)
	{
		if (name == mpModel->Frames()[i]->Name())
		{
			return &mpCombinedMatrix[i];
		}
	}
	return nullptr;
}

void CXCharacter::AnimationFrame(float per)
{
	mAnimationFrame = mAnimationFrameSize * per;
}

float CXCharacter::AnimationFrame()
{
	return mAnimationFrame / mAnimationFrameSize;
}

CXCharacter::CXCharacter()
	: mpCombinedMatrix(nullptr)
{
	mScale = CVector(1.0f, 1.0f, 1.0f);
}

CXCharacter::CXCharacter(CCharacter3::ETag tag)
	: CCharacter3(tag)
	, mpCombinedMatrix(nullptr)
{
	mScale = CVector(1.0f, 1.0f, 1.0f);
}

void CXCharacter::Update()
{
	//�ϊ��s��̍X�V
	CTransform::Update();
	//�A�j���[�V�������X�V����
	Update(mMatrix);
}

/*
 Init
 ����������
*/
void CXCharacter::Init(CModelX* model) {
	mpModel = model;
	// �����s��ޔ��G���A�̊m��
	mpCombinedMatrix = new CMatrix[model->Frames().size()];
	mAnimationFrameSize = 0;

	if (model->AnimationSets().size() <= 0) return;
	//�ŏ��̃A�j���[�V�����ɂ���
	mAnimationIndex = 0;
	//�J��Ԃ��Đ�����
	mAnimationLoopFlg = true;
	//1�A�j���[�V�����ڂ̍ő�t���[����
	mAnimationFrameSize =
		model->AnimationSets()[0]->MaxTime();
	//�A�j���[�V�����̃t���[�����ŏ��ɂ���
	mAnimationFrame = 0.0f;
	mpModel->AnimationSets()[mAnimationIndex]->
		Time(mAnimationFrame);
	//�A�j���[�V�����̏d�݂�1.0�i100%)�ɂ���
	mpModel->AnimationSets()[mAnimationIndex]->Weight(1.0f);
}

/*
 ChangeAnimation
 �A�j���[�V������؂�ւ���
 index:�A�j���[�V�����̔ԍ�
 loop:true �J��Ԃ�
 framesize�F�Ō�܂ōĐ�����̂Ɏg�p�����t���[����
*/
void CXCharacter::ChangeAnimation(int index, bool loop, float framesize) {
	//�����ꍇ�͐؂�ւ��Ȃ�
	if (mAnimationIndex == index) return;
	//���̃A�j���[�V�����̏d�݂�0.0�i0%)�ɂ���
	mpModel->AnimationSets()[mAnimationIndex]->Weight(0.0f);
	//�ԍ��A�J��Ԃ��A�t���[������ݒ�
	mAnimationIndex = index % mpModel->AnimationSets().size();
	mAnimationLoopFlg = loop;
	mAnimationFrameSize = framesize;
	//�A�j���[�V�����̃t���[�����ŏ��ɂ���
	mAnimationFrame = 0.0f;
	mpModel->AnimationSets()[mAnimationIndex]->Time(mAnimationFrame);
	//�A�j���[�V�����̏d�݂�1.0�i100%)�ɂ���
	mpModel->AnimationSets()[mAnimationIndex]->Weight(1.0f);
}

/*
 Update
 �X�V����
 matrix�F�ړ��A��]�A�g��k���̍s��
*/
void CXCharacter::Update(CMatrix& matrix) {
	if (mpModel->AnimationSets().size() <= 0) return;

	for (size_t i = 0; i < mpModel->AnimationSets().size(); ++i)
	{
		mpModel->AnimationSets()[i]->Weight(0.0f);
	}
	mpModel->AnimationSets()[mAnimationIndex]->Weight(1.0f);

	//�Ō�܂ōĐ�����
	if (mAnimationFrame <= mAnimationFrameSize) {
		//�A�j���[�V�����̎��Ԃ��v�Z
		mpModel->AnimationSets()[mAnimationIndex]->Time(
			mpModel->AnimationSets()[mAnimationIndex]->MaxTime() *
			mAnimationFrame / mAnimationFrameSize);
		//�t���[����i�߂�
		mAnimationFrame++;
	}
	else {
		//�J��Ԃ��̏ꍇ�́A�t���[����0�ɖ߂�
		if (mAnimationLoopFlg) {
			//�A�j���[�V�����̃t���[�����ŏ��ɂ���
			mAnimationFrame = 0.0f;
			mpModel->AnimationSets()[mAnimationIndex]->
				Time(mAnimationFrame);
		}
		else {
			mpModel->AnimationSets()[mAnimationIndex]->
				Time(mpModel->AnimationSets()[mAnimationIndex]->
					MaxTime());
		}
	}
	//�t���[���̕ϊ��s����A�j���[�V�����ōX�V����
	mpModel->AnimateFrame();
	//�t���[���̍����s����v�Z����
	mpModel->Frames()[0]->AnimateCombined(&matrix);
	// �����s��̑ޔ�
	for (size_t i = 0; i < mpModel->Frames().size(); i++) {
		mpCombinedMatrix[i] =
			mpModel->Frames()[i]->CombinedMatrix();
	}

	//���_�ɃA�j���[�V������K�p����
	//mpModel->AnimateVertex();
}

void CXCharacter::Render()
{
	mpModel->RenderShader(mpCombinedMatrix);
}

bool CXCharacter::IsAnimationFinished()
{
	return mAnimationFrame >=
		mAnimationFrameSize;
}

int CXCharacter::AnimationIndex()
{
	return mAnimationIndex;
}

