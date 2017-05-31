#include "RGGraphic.h"

#include <d3d9.h>
#pragma comment(lib, "d3dx9.lib")
#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "DxErr.lib")

namespace RGEngine
{
	Graphic::Graphic(void) :
		m_pD3D(NULL),
		m_pd3dDevice(NULL),
		m_pdxSprite(NULL),
		m_hWnd(NULL) {}

	Graphic::~Graphic()
	{
		Release();
	}

	bool Graphic::CreateFrame(const wchar_t *title, int width, int height, bool fullscreen)
	{
		// 윈도우 클래스 초기화
		WNDCLASSEXW wndcls;
		ZeroMemory(&wndcls, sizeof(wndcls));
		wndcls.cbSize = sizeof(WNDCLASSEX);
		wndcls.hInstance = GetModuleHandle(NULL);
		wndcls.lpszClassName = title;
		wndcls.style = CS_CLASSDC;
		wndcls.lpfnWndProc = &Graphic::MsgProc;

		// 윈도우 클래스를 운영체제에 등록
		if (!RegisterClassExW(&wndcls))
		{
			return false;
		}

		int wx, wy;
		RECT rcWindow = { 0, };
		DWORD style, exstyle;
		if (fullscreen)
		{
			wx = wy = 0L;
			rcWindow.right = GetSystemMetrics(SM_CXSCREEN);
			rcWindow.bottom = GetSystemMetrics(SM_CYSCREEN);
			style = WS_SYSMENU | WS_POPUP;
			exstyle = WS_EX_TOPMOST;
		}
		else
		{
			wx = (GetSystemMetrics(SM_CXSCREEN) - width) / 2;
			wy = (GetSystemMetrics(SM_CYSCREEN) - height) / 2;
			rcWindow.right = width;
			rcWindow.bottom = height;
			style = WS_MINIMIZEBOX | WS_MAXIMIZEBOX | WS_SYSMENU | WS_CAPTION;
			exstyle = NULL;
		}

		// 가로 세로 크기를 클라이언트 크기 기준으로 맞춤
		AdjustWindowRectEx(&rcWindow, style, FALSE, exstyle);

		// 윈도우를 생성
		m_hWnd = CreateWindowExW(exstyle, title, title, style,
			wx, wy, rcWindow.right - rcWindow.left, rcWindow.bottom - rcWindow.top,
			NULL, NULL, wndcls.hInstance, NULL);
		if (m_hWnd == NULL)
		{
			return false;
		}
		if (!fullscreen)
		{
			GetWindowRect(m_hWnd, &m_savedRect);
		}

		// D3D 버전을 체크하고 디바이스를 생성하는 D3D 객체를 생성
		m_pD3D = Direct3DCreate9(D3D_SDK_VERSION);
		if (m_pD3D == NULL)
		{
			return false;
		}

		// Adapter가 갖는 Display정보 얻기
		if (FAILED(m_pD3D->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &m_d3dAdapterMode)))
		{
			return false;
		}

		// 디바이스 프로퍼티 초기화
		ZeroMemory(&m_d3dDeviceProperty, sizeof(m_d3dDeviceProperty));
		m_d3dDeviceProperty.Windowed = !fullscreen;
		m_d3dDeviceProperty.BackBufferWidth = width;
		m_d3dDeviceProperty.BackBufferHeight = height;
		m_d3dDeviceProperty.BackBufferCount = 1;
		m_d3dDeviceProperty.BackBufferFormat = m_d3dAdapterMode.Format;
		m_d3dDeviceProperty.SwapEffect = D3DSWAPEFFECT_DISCARD; // 그냥 되는데로 화면 갱신
		m_d3dDeviceProperty.hDeviceWindow = m_hWnd;

		// 버텍스 프로세싱 체크
		if (FAILED(m_pD3D->GetDeviceCaps(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, &m_d3dCaps)))
		{
			return false;
		}
		DWORD vp = 0UL;
		if (m_d3dCaps.VertexShaderVersion < D3DVS_VERSION(1, 0))
		{
			vp = D3DCREATE_SOFTWARE_VERTEXPROCESSING;
		}
		else
		{
			vp = D3DCREATE_HARDWARE_VERTEXPROCESSING;
		}

		// 디바이스 생성
		if (FAILED(m_pD3D->CreateDevice(
			D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, m_hWnd, vp,
			&m_d3dDeviceProperty, &m_pd3dDevice)))
		{
			return false;
		}

		m_pd3dDevice->SetRenderState(D3DRS_LIGHTING, FALSE);
		m_pd3dDevice->SetRenderState(D3DRS_ZENABLE, FALSE);
		m_pd3dDevice->SetRenderState(D3DRS_NORMALIZENORMALS, TRUE);

		D3DXMATRIX world, proj;
		D3DXMatrixIdentity(&world);
		m_pd3dDevice->SetTransform(D3DTS_WORLD, &world);
		m_pd3dDevice->SetTransform(D3DTS_VIEW, &world);

		// 왼손 좌표계 정사영 행렬(반전 가능한 행렬) 생성
		D3DXMatrixOrthoOffCenterLH(&proj, 0.0f,
			static_cast<float>(width), static_cast<float>(height),
			0.0f, 0.0f, 1.0f);
		m_pd3dDevice->SetTransform(D3DTS_PROJECTION, &proj);

		// 스프라이트 객체를 초기화
		D3DXCreateSprite(m_pd3dDevice, &m_pdxSprite);

		::ShowWindow(m_hWnd, SW_SHOWNORMAL);

		return true;
	}

	bool Graphic::ChangeResolution(int width, int height)
	{
		if (m_d3dDeviceProperty.Windowed)
		{
			RECT sourceRect = { 0, 0, width, height };
			AdjustWindowRectEx(&sourceRect, WS_MINIMIZEBOX | WS_SYSMENU | WS_CAPTION, FALSE, 0UL);
			::SetWindowPos(m_hWnd, NULL, 0, 0, sourceRect.right - sourceRect.left, sourceRect.bottom - sourceRect.top, SWP_NOZORDER | SWP_NOMOVE);
		}
		else
		{
			m_savedRect.right = m_savedRect.left + width + (m_savedRect.right - m_savedRect.left) - m_d3dDeviceProperty.BackBufferWidth;
			m_savedRect.bottom = m_savedRect.top + height + (m_savedRect.bottom - m_savedRect.top) - m_d3dDeviceProperty.BackBufferHeight;
		}
		m_d3dDeviceProperty.BackBufferWidth = width;
		m_d3dDeviceProperty.BackBufferHeight = height;

		ResetDevice();
		return true;
	}

	void Graphic::Release(void)
	{
		if (m_pdxSprite)
		{
			m_pdxSprite->Release();
			m_pdxSprite = NULL;
		}
		if (m_pd3dDevice)
		{
			m_pd3dDevice->Release();
			m_pd3dDevice = NULL;
		}
		if (m_pD3D)
		{
			m_pD3D->Release();
			m_pD3D = NULL;
		}
		GetClassNameW(m_hWnd, buf, 512);
		DestroyWindow(m_hWnd);
		UnregisterClassW(buf, GetModuleHandleW(NULL));
	}

	void Graphic::ResetDevice(void)
	{
		m_pdxSprite->OnLostDevice();
		for (auto &i : m_resets)
		{
			i->OnLostDevice();
		}
		m_pd3dDevice->Reset(&m_d3dDeviceProperty);
		m_pdxSprite->OnResetDevice();
		for (auto &i : m_resets)
		{
			i->OnResetDevice();
		}
	}

	void Graphic::PushResetableComponent(ResetableComponentInterface *component)
	{
		m_resets.push_back(component);
	}

	void Graphic::PopResetableComponent(ResetableComponentInterface *component)
	{
		m_resets.remove(component);
	}

	bool Graphic::Process(void)
	{
		if (PeekMessageW(&m_msg, NULL, 0U, 0U, PM_REMOVE))
		{
			TranslateMessage(&m_msg);
			DispatchMessageW(&m_msg);
			return false;
		}
		return true;
	}
	bool Graphic::BeginScene(Math::Color clear)
	{
		m_pd3dDevice->Clear(0UL, NULL, D3DCLEAR_TARGET, clear, 1.0f, 0UL);
		if (FAILED(m_pd3dDevice->BeginScene()))
		{
			return false;
		}
		return SUCCEEDED(m_pdxSprite->Begin(D3DXSPRITE_ALPHABLEND | D3DXSPRITE_SORT_TEXTURE));
	}
	bool Graphic::EndScene(void)
	{
		m_pdxSprite->End();
		m_pd3dDevice->EndScene();
		switch(m_pd3dDevice->Present(NULL, NULL, NULL, NULL))
		{
		case D3D_OK:
			return true;

		case D3DERR_DEVICELOST:
			Sleep(100);
			return true;

		case D3DERR_DEVICENOTRESET:
			ResetDevice();
			return true;

		}
		return false;
	}

	bool Graphic::ToggleFullscreen(void)
	{
		if (m_d3dDeviceProperty.Windowed)
		{
			// to fullscreen
			GetWindowRect(m_hWnd, &m_savedRect);
			m_d3dDeviceProperty.Windowed = FALSE;
			SetWindowLongW(m_hWnd, GWL_STYLE, WS_SYSMENU | WS_POPUP);
			::SetWindowPos(m_hWnd, HWND_TOPMOST, 0, 0, ::GetSystemMetrics(SM_CXSCREEN), ::GetSystemMetrics(SM_CYSCREEN), SWP_FRAMECHANGED | SWP_SHOWWINDOW);
		}
		else
		{
			// to windowed
			m_d3dDeviceProperty.Windowed = TRUE;
			SetWindowLongW(m_hWnd, GWL_STYLE, WS_MINIMIZEBOX | WS_MAXIMIZEBOX | WS_SYSMENU | WS_CAPTION);
			::SetWindowPos(m_hWnd, HWND_NOTOPMOST, m_savedRect.left, m_savedRect.top, m_savedRect.right - m_savedRect.left, m_savedRect.bottom - m_savedRect.top, SWP_FRAMECHANGED | SWP_SHOWWINDOW);
		}
		ResetDevice();
		return true;
	}

	bool Graphic::Validate(void)
	{
		return m_msg.message != WM_QUIT;
	}
	bool Graphic::IsFullscreen(void) const
	{
		return m_d3dDeviceProperty.Windowed ? false : true;
	}

	// Set Properties
	void Graphic::SetCaption(const wchar_t *title)
	{
		::SetWindowTextW(m_hWnd, title);
	}
	void Graphic::SetWindowPos(const Types::Point &p)
	{
		::SetWindowPos(m_hWnd, NULL, p.x, p.y, 0, 0, SWP_NOZORDER | SWP_NOSIZE);
	}
	void Graphic::SetWindowPos(int x, int y)
	{
		::SetWindowPos(m_hWnd, NULL, x, y, 0, 0, SWP_NOZORDER | SWP_NOSIZE);
	}
	void Graphic::SetWindowSize(const Types::Size &s)
	{
		::SetWindowPos(m_hWnd, NULL, 0, 0, s.cx, s.cy, SWP_NOZORDER | SWP_NOMOVE);
	}
	void Graphic::SetWindowSize(int width, int height)
	{
		::SetWindowPos(m_hWnd, NULL, 0, 0, width, height, SWP_NOZORDER | SWP_NOMOVE);
	}

	void Graphic::SetMaxmizable(bool flag)
	{
		SetWindowLongW(m_hWnd, GWL_STYLE, flag ?
			GetWindowLongW(m_hWnd, GWL_STYLE) | WS_MAXIMIZEBOX :
			GetWindowLongW(m_hWnd, GWL_STYLE) & ~WS_MAXIMIZEBOX);
	}

	// Get Properties
	HWND Graphic::GetWindowHandle(void) const
	{
		return m_hWnd;
	}
	std::wstring Graphic::GetCaption(void) const
	{
		buf[::GetWindowTextW(m_hWnd, buf, MAX_BUF)] = L'\0';
		return std::wstring(buf);
	}
	int Graphic::GetWindowWidth(void) const
	{
		RECT rc;
		::GetWindowRect(m_hWnd, &rc);
		return (int)rc.right;
	}
	int Graphic::GetWindowHeight(void) const
	{
		RECT rc;
		::GetWindowRect(m_hWnd, &rc);
		return (int)rc.bottom;
	}
	Types::Size Graphic::GetWindowSize(void) const
	{
		RECT rc;
		::GetWindowRect(m_hWnd, &rc);
		return Types::Size((int)rc.right, (int)rc.bottom);
	}
	int Graphic::GetScreenWidth(void) const
	{
		RECT rc;
		::GetClientRect(m_hWnd, &rc);
		return (int)rc.right;
	}
	int Graphic::GetScreenHeight(void) const
	{
		RECT rc;
		::GetClientRect(m_hWnd, &rc);
		return (int)rc.bottom;
	}
	Types::Size Graphic::GetScreenSize(void) const
	{
		RECT rc;
		::GetClientRect(m_hWnd, &rc);
		return Types::Size(rc.right, rc.bottom);
	}
	int Graphic::GetWindowX(void) const
	{
		RECT rc;
		::GetWindowRect(m_hWnd, &rc);
		return (int)rc.left;
	}
	int Graphic::GetWindowY(void) const
	{
		RECT rc;
		::GetWindowRect(m_hWnd, &rc);
		return (int)rc.top;
	}
	Types::Point Graphic::GetWindowPos(void) const
	{
		RECT rc;
		::GetWindowRect(m_hWnd, &rc);
		return Types::Point((int)rc.left, (int)rc.top);
	}

	bool Graphic::GetMaximizable(void) const
	{
		return GetWindowLongW(m_hWnd, GWL_STYLE) & WS_MAXIMIZEBOX ? true : false;
	}

	LPDIRECT3DDEVICE9 Graphic::GetDevice(void) const
	{
		return m_pd3dDevice;
	}

	LPD3DXSPRITE Graphic::GetSprite(void) const
	{
		return m_pdxSprite;
	}

	// Active
	void Graphic::MinimizeWindow(void)
	{
		::ShowWindow(m_hWnd, SW_SHOWMINIMIZED);
	}
	void Graphic::MaxmizeWindow(void)
	{
		::ShowWindow(m_hWnd, SW_SHOWMAXIMIZED);
	}
	void Graphic::FocusWindow(void)
	{
		::SetFocus(m_hWnd);
	}
	void Graphic::ForegroundWindow(void)
	{
		::SetForegroundWindow(m_hWnd);
	}
	void Graphic::ActiveWindow(void)
	{
		::SetActiveWindow(m_hWnd);
	}

	// State
	bool Graphic::IsMinimizeWindow(void) const
	{
		return ::IsIconic(m_hWnd) ? true : false;
	}
	bool Graphic::IsMaximizeWindow(void) const
	{
		return ::IsZoomed(m_hWnd) ? true : false;
	}
	bool Graphic::IsFocusWindow(void) const
	{
		return ::GetFocus() == m_hWnd;
	}
	bool Graphic::IsActiveWindow(void) const
	{
		return ::GetActiveWindow() == m_hWnd;
	}

	// 윈도우 메세지 핸들러
	LRESULT CALLBACK Graphic::MsgProc(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam)
	{
		switch (Msg)
		{
		case WM_DESTROY:
			PostQuitMessage(0);
			return 0;

		}
		return(::DefWindowProcW(hWnd, Msg, wParam, lParam));
	}

}