#include "Game.h"
#include <time.h>

MarioGame::MarioGame(){
}

MarioGame::~MarioGame(){
}

int MarioGame::GameInit(HWND hWnd){
	dxgraphic = new MGraphics();
	dxinput = new MInput();
	HRESULT result;
	//Set random number seed
	srand(time(NULL));

	//Init input
	if(!dxinput->InitKeyBoard(hWnd)){
		MessageBoxA(hWnd, "Error when initialize direct input", "Error", MB_OK);
		return 0;
	};

	//Init graphic
	if(!dxgraphic->InitDirect3D(hWnd, SCREEN_WIDTH, SCREEN_HEIGHT, FULLSCREEN)){
		MessageBoxA(hWnd, "Error when initialize direct 3d", "Error", MB_OK);
		return 0;
	};

	MResource::GetInstance()->InitResource(dxgraphic->GetD3DDevice());

	result = D3DXCreateSprite(dxgraphic->GetD3DDevice(), &spriteHandler);
	if(result != D3D_OK){
		return 0;
	}

	mario = new Mario();
	timer = new MTimer();
	timer->SetMaxFps(60.0f);
	camera = new MCamera();
	return 1;
}


int MarioGame::GameRun(HWND hWnd, MSG msg){
	timer->StartCount();
	int done = 0;
	while (!done){
		if(PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)){
			if(msg.message == WM_QUIT){
				done = 1;
			}
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}else{
			if(timer->GetTime() < 1.0f){
				timer->EndCount();
				dxinput->ProcessKeyBoard();
				UpdateWorld(timer->GetDeltaTime());
				DrawWorld();
				
			}
		}
	}
	return (int)msg.wParam;
}

void MarioGame::UpdateWorld(float time){
	mario->Update(dxinput, time, camera);
}

void MarioGame::DrawWorld(){
	dxgraphic->BeginRender();
	spriteHandler->Begin(D3DXSPRITE_ALPHABLEND);
	mario->Draw(spriteHandler, camera);
	spriteHandler->End();
	dxgraphic->EndRender();
}

void MarioGame::GameEnd(){
	if(camera != NULL){
		delete camera;
	}
	if(dxgraphic != NULL){
		delete dxgraphic;
	}
	if(dxinput != NULL){
		delete dxinput;
	}
	if(timer != NULL){
		delete timer;
	}
	if(mario != NULL){
		delete mario;
	}
}