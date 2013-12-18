#include <d3d9.h>
#include <d3dx9.h>
#include <time.h>
#include <stdio.h>
#include "DxGraphics.h"
#include "Game.h"

#define APP_TITLE L"Mario"

MarioGame* game = new MarioGame();

//Windows callback
LRESULT WINAPI WinProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam){
	switch (msg)
	{
	case WM_DESTROY:
		game->GameEnd();
		//Tell windows to kill program
		PostQuitMessage(0);
		return 0;
	}
	return DefWindowProc(hwnd, msg, wParam, lParam);
}

//Helper function to set up windows property
ATOM MyRegisterClass(HINSTANCE hInstance){
	//Create windows class structure
	WNDCLASSEX wc;
	wc.cbSize = sizeof(WNDCLASSEX);

	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = (WNDPROC)WinProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = hInstance;
	wc.hIcon = NULL;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	wc.lpszMenuName = NULL;
	wc.lpszClassName = APP_TITLE;
	wc.hIconSm = NULL;

	//Set up windows with the class info
	return RegisterClassEx(&wc);
}

//Entry point for windows program
int WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd ){
	
	HWND hwnd;

	//Register class
	MyRegisterClass(hInstance);

	//Set up the screen in windowed or full screen mode
	DWORD style;
	if(FULLSCREEN){
		style = WS_EX_TOPMOST | WS_VISIBLE | WS_POPUP;
	}else{
		style =WS_OVERLAPPED;
	}

	//Create windows
	hwnd = CreateWindow(
		APP_TITLE,
		APP_TITLE,
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		SCREEN_WIDTH,
		SCREEN_HEIGHT,
		NULL,
		NULL,
		hInstance,
		NULL);

	//If there is an error when creating windows
	if(hwnd == NULL){
		return FALSE;
	}

	//Display windows
	ShowWindow(hwnd, nShowCmd);
	UpdateWindow(hwnd);

	if(!game->GameInit(hwnd)){
		MessageBoxA(hwnd, "Xảy ra lỗi khi khởi tạo game resource", "Lỗi", MB_OK);
		return 0;
	}
	MSG msg;
	ZeroMemory (&msg, sizeof(msg));
	//Main message loop
	game->GameRun(hwnd, msg);
	return 1;
}