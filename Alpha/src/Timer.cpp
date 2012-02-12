#include "Timer.h"

Kaotic_Alpha::Timer::Timer()
	: m_Paused(false)
{
}

Kaotic_Alpha::Timer::~Timer()
{}

float Kaotic_Alpha::Timer::GetElapsedTime() 
{ 
	return clock() - m_StartTime; 
}

void Kaotic_Alpha::Timer::Start()
{
	m_StartTime = clock();
	m_Paused = false;
}

void Kaotic_Alpha::Timer::Update()
{
}

void Kaotic_Alpha::Timer::Pause()
{
	m_Paused = true;
}