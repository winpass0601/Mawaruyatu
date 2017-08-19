#include <Direct3D\Direct3D.h>

using namespace HF;

Direct3D::Direct3D()
{
	m_pD3DDevice = nullptr;
	m_pD3DDeviceContext = nullptr;
	m_pSwapChain = nullptr;
	m_pRenderTargetView = nullptr;
}

Direct3D::~Direct3D()
{
	Release();
}

void Direct3D::Release()
{
	SAFE_RELEASE(m_pD3DDevice);
	SAFE_RELEASE(m_pD3DDeviceContext);
	SAFE_RELEASE(m_pSwapChain);
	SAFE_RELEASE(m_pRenderTargetView);
}

HRESULT Direct3D::InitDirect3D(HWND hwnd,UINT width,UINT heiht)
{
	HRESULT hr = S_OK;

	UINT createDeviceFlags = 0;
#ifdef _DEBUG
	createDeviceFlags |= D3D11_CREATE_DEVICE_DEBUG;
#endif // _DEBUG

	D3D_DRIVER_TYPE driverTypes[]
	{
		D3D_DRIVER_TYPE_HARDWARE,
		D3D_DRIVER_TYPE_WARP,
		D3D_DRIVER_TYPE_REFERENCE
	};

	UINT numDriverTypes = ARRAYSIZE(driverTypes);

	D3D_FEATURE_LEVEL featureLevels[]
	{
		D3D_FEATURE_LEVEL_11_0,
		D3D_FEATURE_LEVEL_10_1,
		D3D_FEATURE_LEVEL_9_3
	};

	UINT numFeatureLevels = ARRAYSIZE(featureLevels);

	DXGI_SWAP_CHAIN_DESC swapChainDesc;
	ZeroMemory(&swapChainDesc, sizeof(DXGI_SWAP_CHAIN_DESC));
	swapChainDesc.BufferCount = 1;
	swapChainDesc.BufferDesc.Width = width;
	swapChainDesc.BufferDesc.Height = heiht;
	swapChainDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	swapChainDesc.BufferDesc.RefreshRate.Numerator = 60;
	swapChainDesc.BufferDesc.RefreshRate.Denominator = 1;
	swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	swapChainDesc.OutputWindow = hwnd;
	swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
	swapChainDesc.Windowed = true;
	swapChainDesc.SampleDesc.Count = 1;
	swapChainDesc.SampleDesc.Quality = 0;
	swapChainDesc.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;

	//デバイス作成
	for (int i = 0; i < numDriverTypes; ++i) {
		hr = D3D11CreateDeviceAndSwapChain(
			nullptr,
			driverTypes[i],
			nullptr,
			createDeviceFlags,
			featureLevels,
			numFeatureLevels,
			D3D11_SDK_VERSION,
			&swapChainDesc,
			&m_pSwapChain,
			&m_pD3DDevice,
			&m_featureLevel,
			&m_pD3DDeviceContext
			);
		if (SUCCEEDED(hr)) {
			m_driverType = driverTypes[i];
			break;
		}
	}
	if (FAILED(hr)) {
		return hr;
	}

	//レンダーターゲットビュー作成
	ID3D11Texture2D* m_pBackBufferTex = 0;
	m_pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), reinterpret_cast<void**>(&m_pBackBufferTex));
	
	m_pD3DDevice->CreateRenderTargetView(m_pBackBufferTex, nullptr, &m_pRenderTargetView);

	m_pD3DDeviceContext->OMSetRenderTargets(1, &m_pRenderTargetView, nullptr);

	//ビューポート作成
	m_viewport.Width = static_cast<float>(width);
	m_viewport.Height = static_cast<float>(heiht);
	m_viewport.TopLeftX = 0;
	m_viewport.TopLeftY = 0;
	m_viewport.MinDepth = 0.0f;
	m_viewport.MaxDepth = 1.0f;

	m_pD3DDeviceContext->RSSetViewports(1, &m_viewport);

	SAFE_RELEASE(m_pBackBufferTex);

	return hr;
}