#pragma once
#include "GameObject.h"
#include "Event.h"

class Observer
{
public:

	virtual void Notify(const dae::GameObject& actor, Event event) = 0;
	virtual ~Observer() = default;
};

