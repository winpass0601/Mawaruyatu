#pragma once
#include <Windows.h>
#include <tchar.h>

// デバッグ用
#define _CRTDBG_MAP_ALLOC
#if defined(_DEBUG) && defined(_CRTDBG_MAP_ALLOC) && !defined(NEW)
#define NEW  ::new(_NORMAL_BLOCK, __FILE__, __LINE__)
#else
#define NEW  new
#endif

#define SAFE_RELEASE(x) if( x != nullptr ){ x->Release(); x = nullptr; }
#define SAFE_DELETE(x)  if( x != nullptr ){ delete x;  x = nullptr; }

class Exception
{
public:
	TCHAR m_pErrorStr[1024];

	Exception(HRESULT hr, TCHAR* pMsg)
	{
		_stprintf_s(m_pErrorStr, _T("■□■HRESULT：0x%x [ %s ]\n"), hr, pMsg);

#if defined(DEBUG) || defined(_DEBUG)
		// エラーをデバッガに出力
		OutputDebugString(m_pErrorStr);
#endif
	}
};