#ifndef _DXINPUT_H_
#define _DXINPUT_H_

#include <dinput.h>
#define BUTTON_DOWN(obj, button) (obj.rgbButtons[button] & 0x80)
#define KEYBOARD_BUFFER_SIZE 1024

class MInput
{
private:
	LPDIRECTINPUT8 dinput;								//Direct input object
	LPDIRECTINPUTDEVICE8 dikeyboard;					//Keyboard device
	BYTE keyStates[256];								//Direct input keyboard state buffer
	DIDEVICEOBJECTDATA keyEvents[KEYBOARD_BUFFER_SIZE];	//Buffer keyboard data
	int keydown, keyup;									//On keydown or on keyup
public:
	MInput();
	~MInput();

	int InitKeyBoard(HWND);
	void ProcessKeyBoard();
	int KeyDown(int);
	int GetKeyDown();
	int GetKeyUp();
	void KillKeyBoard();
};

#endif