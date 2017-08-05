#include <Window\Window.h>
using namespace HF;

Window::Window()
{
}

Window::~Window()
{
   
}

void Window::Create(std::string name, int width, int height)
{

	//ウィンドウクラスの作成
	WNDCLASSEX windowClass = {
		sizeof(WNDCLASSEX),				//構造体のメモリサイズ
		CS_CLASSDC,						//ウインドウクラスのスタイル
		Window::MessageProcedure,		//ウィンドウプロシージャのアドレス
		0L,								//補助メモリ。通常は使わないので0
		0L,								//補助メモリ。通常は使わないので0
		GetModuleHandle(NULL),			//インスタンスハンドル
		NULL,							//使用するアイコンを指定。不要ならNULL
		LoadCursor(NULL,IDC_ARROW),		//使用するマウスカーソルを指定。不要ならNULL
		NULL,							//ウインドウのクライアント領域の背景色を設定。不要ならNULL
		NULL,							//ウィンドウのメニューを設定。不要ならNULL
		"game",							//ウィンドウクラス名
		NULL							//使用アイコンの小アイコンの情報。不要ならNULL
	};

	//独自のアイコンの設定（使わなければ無くてもいい）
	windowClass.hIcon = LoadIcon(GetModuleHandle(NULL), "ICON");

	//レジスターに登録
	RegisterClassEx(&windowClass);

	RECT rectangle;

	//矩形を作成
	SetRect(&rectangle, 0, 0, width, height);

	// 矩形情報によりウィンドウ矩形を計算
	AdjustWindowRect(&rectangle, WS_OVERLAPPEDWINDOW, FALSE);

	Window* instance = GetInstance();
	//ウィンドウの作成
	instance->m_Handle = CreateWindow(
		"game",									//登録されているクラス名
		name.c_str(),									//ウィンドウ名
		WS_OVERLAPPEDWINDOW,					//ウィンドウスタイル
		30,										//ウィンドウの横方向の表示位置
		0,										//ウィンドウの縦方向の表示位置
		rectangle.right - rectangle.left,		//ウィンドウの幅
		rectangle.bottom - rectangle.top,		//ウィンドウの高さ
		GetDesktopWindow(),						//親ウィンドウまたはオーナーウィンドウのハンドル
		NULL,									//メニューハンドルまたは子ウィンドウID
		windowClass.hInstance,					//アプリケーションインスタンスのハンドル
		NULL									//ウィンドウ作成データ
		);

	//ウィンドウの矩形を取得
	GetWindowRect(instance->m_Handle, &rectangle);

	instance->m_ScreenWidth = rectangle.right - rectangle.left;
	instance->m_ScreenHeight = rectangle.bottom - rectangle.top;

	//表示
	instance->Show();

	//ウインドウの更新
	UpdateWindow(instance->m_Handle);
}

bool Window::MessageHandling()
{
	Window* instance = GetInstance();
	//メッセージがあるか確認
	if (PeekMessage(&instance->m_Message, NULL, 0, 0, PM_NOREMOVE))
	{
		//メッセージ取得
		if (!GetMessage(&instance->m_Message, NULL, 0, 0))
			return false;

		//メッセージの読み取り
		TranslateMessage(&instance->m_Message);

		//メッセージ処理
		DispatchMessage(&instance->m_Message);
	}

	return true;
}

Window* Window::GetInstance()
{
	static Window instance;
	return &instance;
}

void Window::Show()const
{
	ShowWindow(m_Handle, SW_SHOW);
}

HWND Window::GetHandle()const
{
	return m_Handle;
}
LRESULT __stdcall Window::MessageProcedure(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_KEYDOWN:
		switch (wParam)
		{
		case VK_ESCAPE:
			SendMessage(hWnd, WM_DESTROY, 0, 0);
			return 0;
		}
		return 0;
	case WM_DESTROY:
		//終了メッセージ送信
		PostQuitMessage(0);

		return 0;
	}

	//デフォルトウィンドウプロシージャ処理
	return DefWindowProc(hWnd, msg, wParam, lParam);
}