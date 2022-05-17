#pragma once
#include "InputManager.h"

class ObserverScene
{

public:
	ObserverScene();
	~ObserverScene();
	ObserverScene(const ObserverScene& other) = delete;
	ObserverScene(ObserverScene&& other) noexcept = delete;
	ObserverScene& operator=(const ObserverScene& other) = delete;
	ObserverScene& operator=(ObserverScene&& other) noexcept = delete;
};

