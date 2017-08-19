#include <Window\Window.h>
#include <Direct3D\Direct3D.h>

#define SCREEN_X 1280
#define SCREEN_Y 720

int  __stdcall WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nCmdShow)
{
	//ウィンドウを作成
	HF::Window::GetInstance()->Create("†Mawaruyatu†", SCREEN_X, SCREEN_Y);

	//デバイス作成
	HF::Direct3D::Instance().InitDirect3D(
		HF::Window::GetInstance()->GetHandle(),
		HF::Window::GetInstance()->m_ScreenWidth,
		HF::Window::GetInstance()->m_ScreenHeight
		);

	while (HF::Window::MessageHandling())
	{

	}
	return 0;
}
