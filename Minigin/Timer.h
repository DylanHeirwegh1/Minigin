#pragma once
#include "Singleton.h"
#include <chrono>

class Timer final : public dae::Singleton<Timer>
{
public:

	float GetElapsedSeconds();
	void Update();
	void Start();
	void SetFixedTimeStep(float fixedTimeStep);
	float GetFixedTimeStep();

private:
	float m_ElapsedTime{ 0.f };
	std::chrono::time_point<std::chrono::steady_clock> m_Start;
	std::chrono::time_point<std::chrono::steady_clock> m_LastTime;
	float m_FixedTimeStep{ 0.2f };
};
