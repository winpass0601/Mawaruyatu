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

	//�E�B���h�E�N���X�̍쐬
	WNDCLASSEX windowClass = {
		sizeof(WNDCLASSEX),				//�\���̂̃������T�C�Y
		CS_CLASSDC,						//�E�C���h�E�N���X�̃X�^�C��
		Window::MessageProcedure,		//�E�B���h�E�v���V�[�W���̃A�h���X
		0L,								//�⏕�������B�ʏ�͎g��Ȃ��̂�0
		0L,								//�⏕�������B�ʏ�͎g��Ȃ��̂�0
		GetModuleHandle(NULL),			//�C���X�^���X�n���h��
		NULL,							//�g�p����A�C�R�����w��B�s�v�Ȃ�NULL
		LoadCursor(NULL,IDC_ARROW),		//�g�p����}�E�X�J�[�\�����w��B�s�v�Ȃ�NULL
		NULL,							//�E�C���h�E�̃N���C�A���g�̈�̔w�i�F��ݒ�B�s�v�Ȃ�NULL
		NULL,							//�E�B���h�E�̃��j���[��ݒ�B�s�v�Ȃ�NULL
		"game",							//�E�B���h�E�N���X��
		NULL							//�g�p�A�C�R���̏��A�C�R���̏��B�s�v�Ȃ�NULL
	};

	//�Ǝ��̃A�C�R���̐ݒ�i�g��Ȃ���Ζ����Ă������j
	windowClass.hIcon = LoadIcon(GetModuleHandle(NULL), "ICON");

	//���W�X�^�[�ɓo�^
	RegisterClassEx(&windowClass);

	RECT rectangle;

	//��`���쐬
	SetRect(&rectangle, 0, 0, width, height);

	// ��`���ɂ��E�B���h�E��`���v�Z
	AdjustWindowRect(&rectangle, WS_OVERLAPPEDWINDOW, FALSE);

	Window* instance = GetInstance();
	//�E�B���h�E�̍쐬
	instance->m_Handle = CreateWindow(
		"game",									//�o�^����Ă���N���X��
		name.c_str(),									//�E�B���h�E��
		WS_OVERLAPPEDWINDOW,					//�E�B���h�E�X�^�C��
		30,										//�E�B���h�E�̉������̕\���ʒu
		0,										//�E�B���h�E�̏c�����̕\���ʒu
		rectangle.right - rectangle.left,		//�E�B���h�E�̕�
		rectangle.bottom - rectangle.top,		//�E�B���h�E�̍���
		GetDesktopWindow(),						//�e�E�B���h�E�܂��̓I�[�i�[�E�B���h�E�̃n���h��
		NULL,									//���j���[�n���h���܂��͎q�E�B���h�EID
		windowClass.hInstance,					//�A�v���P�[�V�����C���X�^���X�̃n���h��
		NULL									//�E�B���h�E�쐬�f�[�^
		);

	//�E�B���h�E�̋�`���擾
	GetWindowRect(instance->m_Handle, &rectangle);

	instance->m_ScreenWidth = rectangle.right - rectangle.left;
	instance->m_ScreenHeight = rectangle.bottom - rectangle.top;

	//�\��
	instance->Show();

	//�E�C���h�E�̍X�V
	UpdateWindow(instance->m_Handle);
}

bool Window::MessageHandling()
{
	Window* instance = GetInstance();
	//���b�Z�[�W�����邩�m�F
	if (PeekMessage(&instance->m_Message, NULL, 0, 0, PM_NOREMOVE))
	{
		//���b�Z�[�W�擾
		if (!GetMessage(&instance->m_Message, NULL, 0, 0))
			return false;

		//���b�Z�[�W�̓ǂݎ��
		TranslateMessage(&instance->m_Message);

		//���b�Z�[�W����
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
		//�I�����b�Z�[�W���M
		PostQuitMessage(0);

		return 0;
	}

	//�f�t�H���g�E�B���h�E�v���V�[�W������
	return DefWindowProc(hWnd, msg, wParam, lParam);
}