#pragma once
#include <Windows.h>
#include "GLFW/glfw3.h"

class CInput
{
public:
	static GLFWwindow* Window();
	static void Window(GLFWwindow* pwindow);
	void GetMousePos(float* px, float* py);

	CInput();
	//bool Key(����)
	//�߂�l
	//true:�����̃L�[��������Ă���
	//false:�����̃L�[��������Ă��Ȃ�
	bool Key(char key);
	//bool KeyDown(����)
	//�߂�l
	//true:�����̃L�[�������ꂽ��
	//false:�����̃L�[�������ꂽ���ȊO
	bool KeyDown(char key);
private:
	static GLFWwindow* spWindow;	//�E�B���h�E�̃|�C���^
	bool mPush[256];
};