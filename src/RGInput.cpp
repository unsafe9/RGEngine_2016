#include "RGInput.h"

#pragma comment(lib, "dinput8.lib")
#pragma comment(lib, "dxguid.lib")

namespace RGEngine
{
		Input::Input(HWND hWnd) : m_hWnd(hWnd)
		{
			// Initialize the main direct input interface.
			DirectInput8Create(GetModuleHandleW(NULL), DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&m_pDirectInput, NULL);

			// Initialize the direct input interface for the keyboard.
			m_pDirectInput->CreateDevice(GUID_SysKeyboard, &m_pKeyboard, NULL);

			// Set the data format.  In this case since it is a keyboard we can use the predefined data format.
			m_pKeyboard->SetDataFormat(&c_dfDIKeyboard);

			// Set the cooperative level of the keyboard to not share with other programs.
			m_pKeyboard->SetCooperativeLevel(hWnd, DISCL_FOREGROUND | DISCL_EXCLUSIVE);

			// Now acquire the keyboard.
			m_pKeyboard->Acquire();

			// Initialize the direct input interface for the mouse.
			m_pDirectInput->CreateDevice(GUID_SysMouse, &m_pMouse, NULL);

			// Set the data format for the mouse using the pre-defined mouse data format.
			m_pMouse->SetDataFormat(&c_dfDIMouse);

			// Set the cooperative level of the mouse to share with other programs.
			m_pMouse->SetCooperativeLevel(hWnd, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE);

			// Acquire the mouse.
			m_pMouse->Acquire();
		}
		Input::~Input()
		{
			// Release the mouse.
			if (m_pMouse)
			{
				m_pMouse->Unacquire();
				m_pMouse->Release();
			}

			// Release the keyboard.
			if (m_pKeyboard)
			{
				m_pKeyboard->Unacquire();
				m_pKeyboard->Release();
			}

			// Release the main interface to direct input.
			if (m_pDirectInput)
			{
				m_pDirectInput->Release();
			}
		}

		void Input::Update(void)
		{
			HRESULT result = NULL;
			// Read the current state of the keyboard.

			// Read the keyboard device.
			memcpy_s(m_stateKeyboardL, sizeof(m_stateKeyboardL), m_stateKeyboardR, sizeof(m_stateKeyboardR));
			result = m_pKeyboard->GetDeviceState(sizeof(m_stateKeyboardR), (LPVOID)&m_stateKeyboardR);
			if (FAILED(result))
			{
				// If the keyboard lost focus or was not acquired then try to get control back.
				if ((result == DIERR_INPUTLOST) || (result == DIERR_NOTACQUIRED))
				{
					m_pKeyboard->Acquire();
				}
			}

			// Read the current state of the mouse.

			// Read the mouse device.
			memcpy_s(m_rgbButtonsL, sizeof(m_rgbButtonsL), m_stateMouse.rgbButtons, sizeof(m_stateMouse.rgbButtons));
			result = m_pMouse->GetDeviceState(sizeof(DIMOUSESTATE), (LPVOID)&m_stateMouse);
			if (FAILED(result))
			{
				// If the mouse lost focus or was not acquired then try to get control back.
				if ((result == DIERR_INPUTLOST) || (result == DIERR_NOTACQUIRED))
				{
					m_pMouse->Acquire();
				}
			}
		}

#define LKEY(key) (m_stateKeyboardL[key] & 0x80 ? true : false)
#define RKEY(key) (m_stateKeyboardR[key] & 0x80 ? true : false)

		bool Input::Trigger(int key) const
		{
			return LKEY(key) == false && RKEY(key) == true;
		}
		bool Input::Press(int key) const
		{
			return LKEY(key) == true && RKEY(key) == true;
		}
		bool Input::Release(int key) const
		{
			return LKEY(key) == true && RKEY(key) == false;
		}
#undef LKEY
#undef RKEY

#define LKEY(key) (m_rgbButtonsL[key] & 0x80 ? true : false)
#define RKEY(key) (m_stateMouse.rgbButtons[key] & 0x80 ? true : false)
		bool Input::TriggerMouse(int key) const
		{
			return LKEY(key) == false && RKEY(key) == true;
		}
		bool Input::PressMouse(int key) const
		{
			return LKEY(key) == true && RKEY(key) == true;
		}
		bool Input::ReleaseMouse(int key) const
		{
			return LKEY(key) == true && RKEY(key) == false;
		}
#undef LKEY
#undef RKEY

		void Input::GetMouseFromClient(Types::Point &mouse) const
		{
			GetCursorPos((LPPOINT)&mouse);
			ScreenToClient(m_hWnd, (LPPOINT)&mouse);
		}
		void Input::GetMouseFromClient(Types::Point *mouse) const
		{
			GetCursorPos((LPPOINT)mouse);
			ScreenToClient(m_hWnd, (LPPOINT)mouse);
		}
		void Input::GetMouseFromClient(Math::Vector &mouse) const
		{
			POINT m;
			GetCursorPos(&m);
			ScreenToClient(m_hWnd, &m);
			mouse.SetVector((float)m.x, (float)m.y);
		}
		void Input::GetMouseFromClient(Math::Vector *mouse) const
		{
			POINT m;
			GetCursorPos(&m);
			ScreenToClient(m_hWnd, &m);
			mouse->SetVector((float)m.x, (float)m.y);
		}
		void Input::GetMouseFromScreen(Types::Point &mouse) const
		{
			GetCursorPos((LPPOINT)&mouse);
		}
		void Input::GetMouseFromScreen(Types::Point *mouse) const
		{
			GetCursorPos((LPPOINT)mouse);
		}
		void Input::GetMouseFromScreen(Math::Vector &mouse) const
		{
			POINT m;
			GetCursorPos(&m);
			mouse.SetVector((float)m.x, (float)m.y);
		}
		void Input::GetMouseFromScreen(Math::Vector *mouse) const
		{
			POINT m;
			GetCursorPos(&m);
			mouse->SetVector((float)m.x, (float)m.y);
		}

		long Input::GetMouseDeltaX(void) const
		{
			return m_stateMouse.lX;
		}

		long Input::GetMouseDeltaY(void) const
		{
			return m_stateMouse.lY;
		}

		int Input::GetMouseWheel(void) const
		{
			return (int)m_stateMouse.lZ;
		}

}