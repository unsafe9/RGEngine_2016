
#ifndef _RGGRAPHIC_H_
#define _RGGRAPHIC_H_

// #pragma comment(lib, "d3dx9.lib")
// #pragma comment(lib, "d3d9.lib")
// #pragma comment(lib, "DxErr.lib")

#include <d3dx9.h>
#include <Windows.h>
#include <string>
#include <list>

#include "RGTypes.h"
#include "RGMath.h"

namespace RGEngine
{
	class ResetableComponentInterface
	{
	public:
		virtual void OnLostDevice(void) = 0;
		virtual void OnResetDevice(void) = 0;
	};

	class Graphic
	{
	private:
		enum { MAX_BUF = 512 };
		mutable wchar_t buf[MAX_BUF]; // ¹öÆÛ

		// DirectX
		LPDIRECT3D9 m_pD3D;
		LPDIRECT3DDEVICE9 m_pd3dDevice;
		D3DPRESENT_PARAMETERS m_d3dDeviceProperty;
		D3DCAPS9 m_d3dCaps;
		D3DDISPLAYMODE m_d3dAdapterMode;
		LPD3DXSPRITE m_pdxSprite;
		std::list<ResetableComponentInterface *> m_resets;

		// Window
		HWND m_hWnd;
		MSG m_msg;
		RECT m_savedRect;

	public:
		Graphic(void);
		~Graphic();

	public:
		bool CreateFrame(const wchar_t *title, int width, int height, bool fullscreen);
		bool ChangeResolution(int width, int height);
		void Release(void);

		void PushResetableComponent(ResetableComponentInterface *component);
		void PopResetableComponent(ResetableComponentInterface *component);

		bool Process(void); // dispatch message
		bool BeginScene(Math::Color clear = Math::COLOR_RGB(255, 255, 255)); // begin rendering
		bool EndScene(void); // end rendering

		bool ToggleFullscreen(void);

		bool Validate(void);
		bool IsFullscreen(void) const;

		// Set Properties
		void SetCaption(const wchar_t *title);
		void SetWindowPos(const Types::Point &p);
		void SetWindowPos(int x, int y);
		void SetWindowSize(const Types::Size &s);
		void SetWindowSize(int width, int height);
		void SetMaxmizable(bool flag);

		// Get Properties
		HWND GetWindowHandle(void) const;
		std::wstring GetCaption(void) const;
		int GetWindowWidth(void) const;
		int GetWindowHeight(void) const;
		Types::Size GetWindowSize(void) const;
		int GetScreenWidth(void) const;
		int GetScreenHeight(void) const;
		Types::Size GetScreenSize(void) const;
		int GetWindowX(void) const;
		int GetWindowY(void) const;
		Types::Point GetWindowPos(void) const;
		bool GetMaximizable(void) const;

		LPDIRECT3DDEVICE9 GetDevice(void) const;
		LPD3DXSPRITE GetSprite(void) const;

		// Active
		void MinimizeWindow(void);
		void MaxmizeWindow(void);
		void FocusWindow(void);
		void ForegroundWindow(void);
		void ActiveWindow(void);

		// State
		bool IsMinimizeWindow(void) const;
		bool IsMaximizeWindow(void) const;
		bool IsFocusWindow(void) const;
		bool IsActiveWindow(void) const;

	private:
		void ResetDevice(void);
		static LRESULT WINAPI MsgProc(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam);

	};
}

#endif // _RGGRAPHIC_H_