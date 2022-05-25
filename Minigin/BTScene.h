#pragma once
#include "Observer.h"
#include "FPSComponent.h"
#include "ImageComponent.h"
#include "InputManager.h"
#include "SceneManager.h"
class BTScene
{
public:

	BTScene();
	~BTScene() = default;
	BTScene(const BTScene& other) = delete;
	BTScene(BTScene&& other) noexcept = delete;
	BTScene& operator=(const BTScene& other) = delete;
	BTScene& operator=(BTScene&& other) noexcept = delete;
};
