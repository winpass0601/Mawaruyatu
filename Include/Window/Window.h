#pragma once
#include <Windows.h>
#include <string>

//HONDAFRAMEWORK
namespace HF
{
	class Window
	{
		private:
			Window();
			HWND m_Handle;
			MSG m_Message;

			void Show()const;
		public:
			int m_ScreenWidth;
			int m_ScreenHeight;

			~Window();

			//ウィンドウ作成
			static void Create(std::string _name, int _width, int _height);
		
			HWND GetHandle()const;

			static bool MessageHandling();

			static Window* GetInstance();

			static LRESULT _stdcall MessageProcedure(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
	};
}