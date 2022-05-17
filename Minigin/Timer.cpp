#include "MiniginPCH.h"
#include "Timer.h"

float Timer::GetElapsedSeconds()
{
	return m_ElapsedTime;
}

void Timer::Update()
{
	auto curr = std::chrono::high_resolution_clock::now();

	m_ElapsedTime = std::chrono::duration<float>(curr - m_LastTime).count();
	m_LastTime = curr;
}

void Timer::Start()
{
	m_Start = std::chrono::high_resolution_clock::now();
	m_LastTime = m_Start;
}

void Timer::SetFixedTimeStep(float fixedTimeStep)
{
	m_FixedTimeStep = fixedTimeStep;
}

float Timer::GetFixedTimeStep()
{
	return m_FixedTimeStep;
}
