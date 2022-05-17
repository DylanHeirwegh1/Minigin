#pragma once
#include "BaseComponent.h"
#include "Timer.h"
#include "Font.h"
#include "Texture2D.h"
#include "GameObject.h"
class FPSComponent : public BaseComponent
{
public:

	void Render() override;
	void Update() override;
	void SetSecondsPerUpdate(float SecondsPerUpdate);


private:
	float m_SecondsPerUpdate{ .5f };
	float m_ElapsedTime{ 0.f };
};

