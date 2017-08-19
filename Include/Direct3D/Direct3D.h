#pragma once
#include <Windows.h>
#include <d3d11.h>
#include <memory>
#include "../Common/Common.h"

namespace HF
{
	class Direct3D
	{
	private:
	public:
		ID3D11Device*			m_pD3DDevice;
		ID3D11DeviceContext*	m_pD3DDeviceContext;
		IDXGISwapChain*         m_pSwapChain;
		ID3D11RenderTargetView* m_pRenderTargetView;
		D3D_DRIVER_TYPE         m_driverType;
		D3D_FEATURE_LEVEL       m_featureLevel;
		D3D11_VIEWPORT          m_viewport;
	protected:
		Direct3D();
	private:
		void Release();
	public:
		virtual ~Direct3D();

		static Direct3D &Instance()
		{
			static Direct3D inst;
			return inst;
		}

		HRESULT InitDirect3D(HWND hwnd, UINT width, UINT heiht);
	};
}