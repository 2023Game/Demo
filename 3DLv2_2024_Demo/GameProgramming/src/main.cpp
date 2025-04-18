#include <Windows.h>
#include "glew.h"
#include "glut.h"
#include "GLFW/glfw3.h"
#include "main.h"
#include "CApplication.h"
#include "CInput.h"
#include <string>

#define TITLE_NAME "Demo Program "

int gFps = 0;

CApplication gApplication;

/* display関数
1秒間に60回実行される
*/
void display() {
	//各バッファーをクリア
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
	//行列のモードをモデルビューにする
	glMatrixMode(GL_MODELVIEW);
	//モデルビューの行列を単位行列にする
	glLoadIdentity();

	gApplication.Update();

}


/*ウィンドウサイズ変更時の処理
void reshape(int width, int height)
width:画面幅
height:画面高さ
*/
void reshape(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);	//画面の描画エリアの指定
	glMatrixMode(GL_PROJECTION);	//行列をプロジェクションモードへ変更
	glLoadIdentity();				//行列を初期化
#ifndef GAME3D
	gluOrtho2D(0, width, 0, height);	//2Dの画面を設定
#else
	//gluPerspective(75.0, (double)width / (double)height, 1.0, 10000.0);	//3Dの画面を設定
	gluPerspective(30.0, (double)width / (double)height, 1.0, 10000.0);	//3Dの画面を設定
#endif
	glMatrixMode(GL_MODELVIEW);		//行列をモデルビューモードへ変更
	glLoadIdentity();				//行列を初期化
}
//
LARGE_INTEGER last_time;	//前回のカウンタ値
//１秒間に６０回描画するように調節する
void idle() {
	LARGE_INTEGER freq;		//一秒当たりのカウンタ数
	LARGE_INTEGER time;		//今回のカウンタ値
	LONGLONG delta;		//今回のカウンタ値

	//一秒間のカウンタ数を取得
	QueryPerformanceFrequency(&freq);

	if (last_time.QuadPart == 0) {
		QueryPerformanceCounter(&last_time);
	}
	do{
		//現在のシステムのカウント数を取得
		QueryPerformanceCounter(&time);

		delta = time.QuadPart - last_time.QuadPart;
		//今のカウント-前回のカウント < 1秒当たりのカウント数を60で割る(1/60秒当たりのカウント数)
	} while (delta < freq.QuadPart / 60);
	last_time = time;

	gFps = freq.QuadPart / delta;

	//描画する関数を呼ぶ
	display();
}

int main(int argc , char** argv)
{
	//glutInit(&argc, argv);

	GLFWwindow* window;

	/* Initialize the library */
	if (!glfwInit())
		return -1;

	/* Create a windowed mode window and its OpenGL context */
#ifndef FULL_SCREEN
	window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, TITLE_NAME, NULL, NULL);
#else
	//Full Screen
	window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, TITLE_NAME, glfwGetPrimaryMonitor(), NULL);
#endif
	if (!window)
	{
		glfwTerminate();
		return -1;
	}
	CInput::Window(window);
	/* Make the window's context current */
	glfwMakeContextCurrent(window);


	glClearColor(0.7f, 0.7f, 0.7f, 1.0f);

	// GLEW を初期化する
	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK)
	{
		// GLEW の初期化に失敗した
//		std::cerr << "Can't initialize GLEW" << std::endl;
		return 1;
	}
	// 垂直同期のタイミングを待つ  
	//glfwSwapInterval(1); 

	// ウィンドウのサイズ変更時に呼び出す処理の登録
	glfwSetWindowSizeCallback(window, reshape);
	reshape(window, WINDOW_WIDTH, WINDOW_HEIGHT);

#ifdef GAME3D
	glEnable(GL_DEPTH_TEST);	//3D必要 2D不要
	glEnable(GL_CULL_FACE);

	//ライトの設定（3D必要 2D不要）
	//固定シェーダー用
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	float lightPosition[] = {0.0f, 100.0f, 100.0f, 1.0f};
	glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);
	glEnable(GL_NORMALIZE);
#endif

	//初期処理
	gApplication.Start();

	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(window))
	{

		idle();

		std::string newTitle = TITLE_NAME + std::to_string(gFps);
		glfwSetWindowTitle(window, newTitle.c_str());

		/* Swap front and back buffers */
		glfwSwapBuffers(window);

		/* Poll for and process events */
		glfwPollEvents();

		int state = glfwGetKey(window, GLFW_KEY_ESCAPE);
		if (state == GLFW_PRESS) {
			//ESCキーでループ終了
			break;
		}
	}

	glfwTerminate();
	return 0;
}
