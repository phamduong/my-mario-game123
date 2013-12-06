#include "Timer.h"

MTimer::MTimer(){
	GetSecondPerTick();
	frameRate = 0;
	m_deltaTime = 0;
	countFrame = 0;
	t_deltaTime = 0;
}

void MTimer::GetSecondPerTick(){
	QueryPerformanceFrequency((LARGE_INTEGER*)&countPerSec);
	timeScale = 1.0f / countPerSec; //chu kì = 1 / tần số
}

void MTimer::StartCount(){
	QueryPerformanceCounter((LARGE_INTEGER*)&timeStart);
}

void MTimer::EndCount(){
	QueryPerformanceCounter((LARGE_INTEGER*)&timeEnd);
	t_deltaTime = (timeEnd - timeStart) * timeScale;
	if (lockFps > 0.0f)
	{
		while (t_deltaTime < 1.0f / lockFps)
		{
			QueryPerformanceCounter((LARGE_INTEGER*)&timeEnd);
			t_deltaTime = (timeEnd - timeStart) * timeScale;
		}
	}
	timeStart = timeEnd;
	m_deltaTime += t_deltaTime;
	countFrame++;
	if (m_deltaTime >= 1.0f)
	{
		frameRate = countFrame;
		countFrame = 0;
		m_deltaTime = 0.0f;
	}
}

void MTimer::SetMaxFps(float max){
	lockFps = max;
}

float MTimer::GetDeltaTime(){
	return (float)(1.0f / lockFps) * 10;
}

float MTimer::GetTime(){
	return m_deltaTime;
}

MTimer::~MTimer(){

}
