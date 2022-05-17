#pragma once
#include "Observer.h"

class Subject
{

public:
	Subject() = default;
	~Subject() = default;
	Subject(const Subject& other) = delete;
	Subject(Subject&& other) noexcept = delete;
	Subject& operator=(const Subject& other) = delete;
	Subject& operator=(Subject&& other) noexcept = delete;

	void AddObserver(Observer* observer);
	void RemoveObserver(Observer* observer);
	void Notify(const dae::GameObject& actor, Event event);

private:
	std::vector<Observer*> m_Observers;

};

