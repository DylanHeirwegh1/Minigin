#pragma once
#include "Observer.h"

class Achievements : public Observer
{
public:
	Achievements();
	~Achievements() = default;
	Achievements(const Achievements& other) = delete;
	Achievements(Achievements&& other) noexcept = delete;
	Achievements& operator=(const Achievements& other) = delete;
	Achievements& operator=(Achievements&& other) noexcept = delete;

	void Notify(const dae::GameObject& actor, Event event) override;

private:


};

