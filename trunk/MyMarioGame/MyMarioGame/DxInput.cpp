#include "DxInput.h"

MInput::MInput(){
	dinput = NULL;
	dikeyboard = NULL;
}

MInput::~MInput(){
	KillKeyBoard();
}

int MInput::InitKeyBoard(HWND hWnd){
	HRESULT result;
	//Initialize direct input object
	result = DirectInput8Create(
		GetModuleHandle(NULL),
		DIRECTINPUT_VERSION,
		IID_IDirectInput8,
		(void**)&dinput,
		NULL);
	if(result != DI_OK){
		return 0;
	}

	//Initialize keyboard
	result = dinput->CreateDevice(GUID_SysKeyboard, &dikeyboard, NULL);
	if(result != DI_OK){
		return 0;
	}
	
	//Set data format for keyboard input
	result = dikeyboard->SetDataFormat(&c_dfDIKeyboard);
	if(result != DI_OK){
		return 0;
	}

	//Set the cooporative level
	result = dikeyboard->SetCooperativeLevel(hWnd, DISCL_NONEXCLUSIVE | DISCL_FOREGROUND);
	if(result != DI_OK){
		return 0;
	}

	DIPROPDWORD dipdw;
	dipdw.diph.dwSize = sizeof(DIPROPDWORD);
	dipdw.diph.dwHeaderSize = sizeof(DIPROPHEADER);
	dipdw.diph.dwObj = 0;
	dipdw.diph.dwHow = DIPH_DEVICE;
	dipdw.dwData = KEYBOARD_BUFFER_SIZE;

	result = dikeyboard->SetProperty(DIPROP_BUFFERSIZE, &dipdw.diph);
	if(result != DI_OK){
		return 0;
	}
	
	result = dikeyboard->Acquire();
	if(result != DI_OK){
		return 0;
	}
	//ok

	return 1;
}

void MInput::ProcessKeyBoard(){
	dikeyboard->Poll();
	if(!SUCCEEDED(dikeyboard->GetDeviceState(sizeof(keyStates), keyStates))){
		//Reacquire
		dikeyboard->Acquire();
	}
	// Get all events (also clear them from DirectInput buffer)
	DWORD dwElements = KEYBOARD_BUFFER_SIZE;
	HRESULT result = dikeyboard->GetDeviceData(sizeof(DIDEVICEOBJECTDATA), keyEvents, &dwElements, 0);
	//Scan through all data, check if the key is pressed or released
	for(DWORD i = 0; i < dwElements; i++){
		int keycode = keyEvents[i].dwOfs;
		int keystate = keyEvents[i].dwData;
		
		if(keystate & 0x80 > 0){
			//Key down
			keydown = keycode;
		}else{
			//Key up
			keyup = keycode;
		}
	}
}

int MInput::KeyDown(int keycode){
	return (keyStates[keycode] & 0x80) > 0;
}

int MInput::GetKeyDown(){
	int temp = keydown;
	keydown = 0;
	return temp;
}

int MInput::GetKeyUp(){
	int temp = keyup;
	keyup = 0;
	return temp;
}

void MInput::KillKeyBoard(){
	if(dinput != NULL){
		dinput->Release();
	}
	if(dikeyboard != NULL){
		dikeyboard->Unacquire();
		dikeyboard->Release();
		dikeyboard = NULL;
	}
}