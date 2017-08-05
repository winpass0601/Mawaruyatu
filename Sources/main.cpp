#include <Window\Window.h>

#define SCREEN_X 1280
#define SCREEN_Y 720

int  __stdcall WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nCmdShow)
{
	//ウィンドウを作成
	HF::Window::GetInstance()->Create("†Mawaruyatu†",SCREEN_X,SCREEN_Y);

	while (HF::Window::MessageHandling())
	{
		
	}
	return 0;
}
