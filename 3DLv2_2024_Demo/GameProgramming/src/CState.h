#pragma once
// ��ԃN���X�̊�{�N���X
class CState
{
public:
	// �ŏ���1����s���鏈��
	virtual void Start() = 0;
	// �P�t���[�����J��Ԃ����s���鏈��
	virtual void Update() = 0;
	//�@�C�ӂ̏Փˏ���
	virtual void Collision(CCollider* m, CCollider* o) {}
	// �C�ӂ̕`�揈��
	virtual void Render() {}
	// ��Ԃ̐ݒ�
	void State(const CCharacter3::EState& state) { mState = state; }
	// ��Ԃ̎擾
	const CCharacter3::EState& State() const { return mState; }
protected:
	CCharacter3::EState mState; //��Ԃ̕ۑ�
	int mAnimNo; //�A�j���[�V�����̔ԍ�
};