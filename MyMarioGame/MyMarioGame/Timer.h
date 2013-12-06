#ifndef _TIMER_H_
#define _TIMER_H_

#include <Windows.h>
#include <tchar.h>

class MTimer
{
private:
	__int64 countPerSec; //tần số
	float timeScale; //chu kì
	int countFrame;
	int frameRate;
	float m_deltaTime;
	float t_deltaTime; //thời gian chuyển hình
	float lockFps;
public:
	__int64 timeStart;
	__int64 timeEnd;
	MTimer();
	~MTimer();
	void GetSecondPerTick();
	void StartCount();
	void EndCount();
	void SetMaxFps(float);
	float GetDeltaTime();
	float GetTime();
	unsigned int GetNumberDeltaTime(LPSTR lpstrFrameRate = NULL);
};
#endif