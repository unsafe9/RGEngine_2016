#ifndef _RGINPUT_H_
#define _RGINPUT_H_

#include "RGMath.h"
#include "RGTypes.h"

#ifndef DIRECTINPUT_VERSION
#define DIRECTINPUT_VERSION 0x0800
#endif // DIRECTINPUT_VERSION

#include <dinput.h>
// #pragma comment(lib, "dinput8.lib")
// #pragma comment(lib, "dxguid.lib")

namespace RGEngine
{
	// KeyCode : DIK_
	class Input
	{
	private:
		enum { KEY_MAXCOUNT = 256 };

	private:
		LPDIRECTINPUT8W m_pDirectInput;
		LPDIRECTINPUTDEVICE8W m_pKeyboard;
		LPDIRECTINPUTDEVICE8W m_pMouse;

		BYTE m_stateKeyboardL[KEY_MAXCOUNT];
		BYTE m_stateKeyboardR[KEY_MAXCOUNT];
		DIMOUSESTATE m_stateMouse;
		BYTE m_rgbButtonsL[4];

		HWND m_hWnd;

	public:
		Input(HWND hWnd);
		~Input();

		void Update(void);

		bool Trigger(int key) const;
		bool Press(int key) const;
		bool Release(int key) const;

#define DIK_MOUSELBUTTON 0 // 좌클릭
#define DIK_MOUSERBUTTON 1 // 우클릭
#define DIK_MOUSEMBUTTON 2 // 휠클릭
#define DIK_MOUSEXBUTTON 3 // 확장버튼클릭
		bool TriggerMouse(int key) const;
		bool PressMouse(int key) const;
		bool ReleaseMouse(int key) const;

		void GetMouseFromClient(Types::Point &mouse) const;
		void GetMouseFromClient(Types::Point *mouse) const;
		void GetMouseFromClient(Math::Vector &mouse) const;
		void GetMouseFromClient(Math::Vector *mouse) const;
		void GetMouseFromScreen(Types::Point &mouse) const;
		void GetMouseFromScreen(Types::Point *mouse) const;
		void GetMouseFromScreen(Math::Vector &mouse) const;
		void GetMouseFromScreen(Math::Vector *mouse) const;
		long GetMouseDeltaX(void) const;
		long GetMouseDeltaY(void) const;

		// 내릴시( < 0) 음수(-120, -240, -360 ...), 올릴시( > 0) 양수(120, 240, 360 ...)
		int GetMouseWheel(void) const;

	};

}

#endif // _RGINPUT_H_